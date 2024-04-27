// ============================ //
// Do not edit this part!!!!    //
// ============================ //
// 0x300001 - CONFIG1H
#pragma config OSC = HSPLL // Oscillator Selection bits (HS oscillator,
                           // PLL enabled (Clock Frequency = 4 x FOSC1))
#pragma config FCMEN = OFF // Fail-Safe Clock Monitor Enable bit
                           // (Fail-Safe Clock Monitor disabled)
#pragma config IESO = OFF  // Internal/External Oscillator Switchover bit
                           // (Oscillator Switchover mode disabled)
// 0x300002 - CONFIG2L
#pragma config PWRT = OFF  // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF // Brown-out Reset Enable bits (Brown-out
                           // Reset disabled in hardware and software)
// 0x300003 - CONFIG1H
#pragma config WDT = OFF // Watchdog Timer Enable bit
                         // (WDT disabled (control is placed on the SWDTEN bit))
// 0x300004 - CONFIG3L
// 0x300005 - CONFIG3H
#pragma config LPT1OSC = OFF // Low-Power Timer1 Oscillator Enable bit
                             // (Timer1 configured for higher power operation)
#pragma config MCLRE = ON    // MCLR Pin Enable bit (MCLR pin enabled;
                             // RE3 input pin disabled)
// 0x300006 - CONFIG4L
#pragma config LVP = OFF   // Single-Supply ICSP Enable bit (Single-Supply
                           // ICSP disabled)
#pragma config XINST = OFF // Extended Instruction Set Enable bit
                           // (Instruction set extension and Indexed
                           // Addressing mode disabled (Legacy mode))

#pragma config DEBUG = OFF // Disable In-Circuit Debugger

#define KHZ 1000UL
#define MHZ (KHZ * KHZ)
#define _XTAL_FREQ (40UL * MHZ)

// ============================ //
//             End              //
// ============================ //

#include <xc.h>

// ============================ //
//        DEFINITIONS           //
// ============================ //

// You can write struct definitions here...

#define T_PRELOAD_LOW 0x6A
#define T_PRELOAD_HIGH 0x67

// ============================ //
//          GLOBALS             //
// ============================ //

typedef enum PieceType
{
    DOT_PIECE,
    SQUARE_PIECE,
    L_PIECE,
} PieceType;

typedef enum MoveType
{
    RIGHT,
    UP,
    DOWN,
    LEFT,
} MoveType;
struct Piece
{
    PieceType type;
    int locs[4][2]; // {{0, 0}, {0, 0}, {0, 0}, {0, 0}}
    int point_size;
};

typedef enum NumberDisplay
{
    zero = 0x3F,
    one = 0x06,
    two = 0x5B,
    three = 0x4F,
    four = 0x66,
    five = 0x6D,
    six = 0x7D,
    seven = 0x07,
    eight = 0x7F,
    nine = 0x6F,
} numbers;

// movement flags
int g0_flag;
int g1_flag;
int g2_flag;
int g3_flag;

unsigned char previousPortGValue = 0; // Previous value of PORTG

struct Piece dot_piece = {DOT_PIECE, {{0, 0}, {0, 0}, {0, 0}, {0, 0}}, 1};
struct Piece square_piece = {SQUARE_PIECE, {{0, 0}, {0, 1}, {1, 0}, {1, 1}}, 4};
struct Piece l_piece = {L_PIECE, {{0, 0}, {0, 1}, {1, 1}, {0, 0}}, 3};
struct Piece currentPiece;

volatile int lPieceType; // 0 -> 0, 1 -> 90, 2 -> 180, 3 -> 270 for L_PIECE
volatile int renderFlag;
volatile unsigned timerCounter;     // 2s falling movement
volatile unsigned char submit_flag; // submit flag
volatile unsigned char rotate_flag;
volatile int submissionCounter;
volatile int keremFlag;
volatile unsigned char pieceCounter;
/*
    0 = empty
    1 = submitted
*/
unsigned char grid[8][4] = {
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0}};

// ============================ //
//      Helper Functions        //
// ============================ //

// deep copy struct
void copyPiece(struct Piece *dest, struct Piece *src)
{
    dest->type = src->type;
    dest->point_size = src->point_size;
    for (int i = 0; i < src->point_size; i++)
    {
        dest->locs[i][0] = src->locs[i][0];
        dest->locs[i][1] = src->locs[i][1];
    }
}

numbers getNumber(int i)
{
    switch (i)
    {
    case 0:
        return zero;
    case 1:
        return one;
    case 2:
        return two;
    case 3:
        return three;
    case 4:
        return four;
    case 5:
        return five;
    case 6:
        return six;
    case 7:
        return seven;
    case 8:
        return eight;
    case 9:
        return nine;
    }
    return zero;
}

int edgeCaseHandler(MoveType move)
{
    for (int i = 0; i < currentPiece.point_size; i++)
    {
        switch (move)
        {
        case RIGHT:
            if (currentPiece.locs[i][1] == 3)
            {
                return 0;
            }
            break;
        case LEFT:
            if (currentPiece.locs[i][1] == 0)
            {
                return 0;
            }
            break;
        case UP:
            if (currentPiece.locs[i][0] == 0)
            {
                return 0;
            }
            break;
        case DOWN:
            if (currentPiece.locs[i][0] == 7)
            {
                return 0;
            }
            break;
        }
    }
    return 1;
}
// ============================ //
//          FUNCTIONS           //
// ============================ //

// You can write function definitions here...
void grid2Board()
{
    // clear ports
    LATC = 0x00;
    LATD = 0x00;
    LATE = 0x00;
    LATF = 0x00;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (grid[i][j] == 1)
            {
                switch (j)
                {
                case 0:
                    LATC += (1 << i);
                    break;
                case 1:
                    LATD += (1 << i);
                    break;
                case 2:
                    LATE += (1 << i);
                    break;
                case 3:
                    LATF += (1 << i);
                    break;
                }
            }
            else
            {
                for (int k = 0; k < currentPiece.point_size; k++)
                {
                    if (currentPiece.locs[k][0] == i && currentPiece.locs[k][1] == j)
                    {
                        switch (j)
                        {
                        case 0:
                            LATC += (1 << i);
                            break;
                        case 1:
                            LATD += (1 << i);
                            break;
                        case 2:
                            LATE += (1 << i);
                            break;
                        case 3:
                            LATF += (1 << i);
                            break;
                        }
                    }
                }
            }
        }
    }
}

void renderPiece()
{
    if (renderFlag)
    {

        switch (pieceCounter)
        {
        case DOT_PIECE:
            copyPiece(&currentPiece, &dot_piece);
            break;
        case SQUARE_PIECE:
            copyPiece(&currentPiece, &square_piece);
            break;
        case L_PIECE:
            copyPiece(&currentPiece, &l_piece);
            break;
        }
        pieceCounter = (pieceCounter + 1) % 3;
        renderFlag = 0;

        timerCounter = 0;
        TMR0H = T_PRELOAD_HIGH;
        TMR0L = T_PRELOAD_LOW;
        grid2Board();
    }
}

void digit0()
{
    LATJ = getNumber(submissionCounter % 10);
    LATH = 0x08;
}
void digit1()
{
    LATJ = getNumber(submissionCounter / 10);
    LATH = 0x04;
}
void digit23()
{
    LATJ = zero;
    LATH = 0x03;
}

void digitUpdate()
{
    switch (keremFlag)
    {
    case 0:
        digit0();
        digit1();
        digit23();
        keremFlag = 1;
        break;
    case 1:
        digit0();
        digit23();
        digit1();
        keremFlag = 2;
        break;
    case 2:
        digit1();
        digit23();
        digit0();
        keremFlag = 3;
        break;
    case 3:
        digit23();
        digit0();
        digit1();
        keremFlag = 4;
        break;
    case 4:
        digit23();
        digit1();
        digit0();
        keremFlag = 5;
        break;
    case 5:
        digit1();
        digit0();
        digit23();
        keremFlag = 0;
        break;
    }
}

void movement_handler()
{
    if (g0_flag)
    {
        // timer disable

        g0_flag = 0;
        if (edgeCaseHandler(RIGHT))
        {

            // move right
            for (int i = 0; i < currentPiece.point_size; i++)
            {
                currentPiece.locs[i][1]++;
            }
            grid2Board();
        }
    }
    if (g1_flag)
    {
        g1_flag = 0;
        if (edgeCaseHandler(UP))
        {
            for (int i = 0; i < currentPiece.point_size; i++)
            {
                currentPiece.locs[i][0]--;
            }
            grid2Board();
        }
    }
    if (g2_flag)
    {
        g2_flag = 0;

        if (edgeCaseHandler(DOWN))
        {
            // move down
            for (int i = 0; i < currentPiece.point_size; i++)
            {
                currentPiece.locs[i][0]++;
            }
            grid2Board();
        }
    }
    if (g3_flag)
    {
        g3_flag = 0;

        if (edgeCaseHandler(LEFT))
        {
            // move left
            for (int i = 0; i < currentPiece.point_size; i++)
            {
                currentPiece.locs[i][1]--;
            }
            grid2Board();
        }
    }
}

void setFlags()
{

    unsigned char currentPortGValue = PORTG & 0xFF; // Mask to get only the first 4 bits
    // LATG = 0;

    // Check if the value of PORTA has changed
    if (currentPortGValue != previousPortGValue)
    {
        // Check each bit of PORTA and set flags accordingly
        g0_flag = (currentPortGValue & 0x01) ? 1 : 0;
        g1_flag = (currentPortGValue & 0x10) ? 1 : 0;
        g2_flag = (currentPortGValue & 0x04) ? 1 : 0;
        g3_flag = (currentPortGValue & 0x08) ? 1 : 0;

        // Update the previous value of PORTA
        previousPortGValue = currentPortGValue;
    }
}

void Init()
{
    ADCON1 = 0x0F;
    // B
    LATB = 0x00;
    PORTB = 0x00;
    TRISB = 0xF0;
    // C
    LATC = 0x00;
    PORTC = 0x00;
    TRISC = 0x00;
    // D
    LATD = 0x00;
    PORTD = 0x00;
    TRISD = 0x00;
    // E
    LATE = 0x00;
    PORTE = 0x00;
    TRISE = 0x00;
    // F
    LATF = 0x00;
    PORTF = 0x00;
    TRISF = 0x00;

    // G
    LATG = 0x00;
    PORTG = 0x00;
    TRISG = 0x1D; // 0b0001 1101

    // H
    LATH = 0x00;
    PORTH = 0x00;
    TRISH = 0x00; // 0b 0000 1100

    // J
    LATJ = 0x00;
    PORTJ = 0x00;
    TRISJ = 0x00;

    pieceCounter = DOT_PIECE; // start as dot piece

    g0_flag = g1_flag = g2_flag = g3_flag = 0; // movement flags

    previousPortGValue = 0;
    submit_flag = rotate_flag = keremFlag = 0;

    lPieceType = 0;        // 0 -> 0, 1 -> 90, 2 -> 180, 3 -> 270 for L_PIECE
    timerCounter = 0;      // 2s falling movement counter
    submissionCounter = 0; // submitted piece counter
    renderFlag = 1;        // enable render function
}

void InitializeTimerAndInterrupts()
{
    T0CON = 0x00;
    T0CONbits.TMR0ON = 1;
    T0CONbits.T0PS2 = 1;
    T0CONbits.T0PS1 = 0;
    T0CONbits.T0PS0 = 1;
    TMR0H = T_PRELOAD_HIGH;
    TMR0L = T_PRELOAD_LOW;

    RCONbits.IPEN = 0;
    INTCON = 0x00;
    INTCONbits.TMR0IE = 1;
    INTCONbits.RBIE = 1;
    INTCONbits.PEIE = 1;
    INTCONbits.GIE = 1;
}

// ============================ //
//   INTERRUPT SERVICE ROUTINE  //
// ============================ //
__interrupt(high_priority) void HandleInterrupt()
{
    if (INTCONbits.TMR0IF)
    {

        INTCONbits.TMR0IF = 0;
        TMR0H = T_PRELOAD_HIGH;
        TMR0L = T_PRELOAD_LOW;

        if (submit_flag)
            submit_flag = 0;
        if (rotate_flag)
            rotate_flag = 0;

        for (size_t i = 0; i < currentPiece.point_size; i++)
        {
            switch (currentPiece.locs[i][1])
            {
            case 0: // PORTC
                // XOR the current bit of PORTC and write it back
                LATC = (1 << currentPiece.locs[i][0]) ^ PORTC;
                break;
            case 1: // PORTD
                LATD = (1 << currentPiece.locs[i][0]) ^ PORTD;
                break;
            case 2: // PORTE
                LATE = (1 << currentPiece.locs[i][0]) ^ PORTE;
                break;
            case 3: // PORTF
                LATF = (1 << currentPiece.locs[i][0]) ^ PORTF;
                break;
            }
        }

        timerCounter++; // 2s falling movement

        if (timerCounter == 8)
        {
            timerCounter = 0;
            if (!edgeCaseHandler(DOWN))
                return;
            // move down
            for (size_t i = 0; i < currentPiece.point_size; i++)
            {
                currentPiece.locs[i][0]++;
            }
            grid2Board();
        }
    }
    if (INTCONbits.RBIF)
    {
        INTCONbits.TMR0IE = 0;
        if (PORTBbits.RB5 && !rotate_flag) // rotate handler
        {
            rotate_flag = 1;
            __delay_us(500);
            if (PORTBbits.RB5)
            {
                if (currentPiece.type == L_PIECE)
                {
                    if (lPieceType == 0)
                    {
                        // {{0, 0}, {0, 1}, {1, 1}, {0, 0}
                        lPieceType = 1;
                        currentPiece.locs[0][0]++;
                    }
                    else if (lPieceType == 1)
                    {
                        // {{1, 0}, {0, 1}, {1, 1}, {0, 0}
                        lPieceType = 2;
                        currentPiece.locs[0][0]--;
                        currentPiece.locs[1][0]++;
                        currentPiece.locs[1][1]--;
                    }
                    else if (lPieceType == 2)
                    {
                        // {{0, 0}, {1,0}, {1, 1}, {0, 0}
                        lPieceType = 3;

                        currentPiece.locs[1][0]--;
                        currentPiece.locs[1][1]++;
                        currentPiece.locs[2][1]--;
                    }
                    else if (lPieceType == 3)
                    {
                        // {{0, 0}, {0, 1}, {1, 0}, {0, 0}
                        lPieceType = 0;
                        currentPiece.locs[2][1]++;
                    }
                    grid2Board();
                }
            }
        }
        if (PORTBbits.RB6 && !submit_flag) // submit handler
        {
            submit_flag = 1;

            __delay_us(1461);
            if (PORTBbits.RB6)
            {
                for (size_t i = 0; i < currentPiece.point_size; i++)
                {
                    if (grid[currentPiece.locs[i][0]][currentPiece.locs[i][1]] == 1)
                    {
                        return;
                    }
                }
                // submit
                for (size_t i = 0; i < currentPiece.point_size; i++)
                {
                    grid[currentPiece.locs[i][0]][currentPiece.locs[i][1]] = 1;
                }

                // add point size to submission counter
                submissionCounter += currentPiece.point_size;

                // render flag enable
                renderFlag = 1;
                grid2Board();
            }
        }
        INTCONbits.RBIF = 0;
        INTCONbits.TMR0IE = 1;
    }
}

void restartGame()
{
    if (submissionCounter == 32)
    {
        Init();
        TMR0H = T_PRELOAD_HIGH;
        TMR0L = T_PRELOAD_LOW;
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                grid[i][j] = 0;
            }
        }
    }
}

// ============================ //
//            MAIN              //
// ============================ //
void main()
{
    Init();
    __delay_ms(1000);
    InitializeTimerAndInterrupts();

    while (31)
    {
        restartGame();
        digitUpdate();
        renderPiece();
        setFlags();
        movement_handler();
    }
}
