PROCESSOR 18F8722

#include <xc.inc>

; CONFIGURATION (DO NOT EDIT)
; CONFIG1H
CONFIG OSC = HSPLL      ; Oscillator Selection bits (HS oscillator, PLL enabled (Clock Frequency = 4 x FOSC1))
CONFIG FCMEN = OFF      ; Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
CONFIG IESO = OFF       ; Internal/External Oscillator Switchover bit (Oscillator Switchover mode disabled)
; CONFIG2L
CONFIG PWRT = OFF       ; Power-up Timer Enable bit (PWRT disabled)
CONFIG BOREN = OFF      ; Brown-out Reset Enable bits (Brown-out Reset disabled in hardware and software)
; CONFIG2H
CONFIG WDT = OFF        ; Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
; CONFIG3H
CONFIG LPT1OSC = OFF    ; Low-Power Timer1 Oscillator Enable bit (Timer1 configured for higher power operation)
CONFIG MCLRE = ON       ; MCLR Pin Enable bit (MCLR pin enabled; RE3 input pin disabled)
; CONFIG4L
CONFIG LVP = OFF        ; Single-Supply ICSP Enable bit (Single-Supply ICSP disabled)
CONFIG XINST = OFF      ; Extended Instruction Set Enable bit (Instruction set extension and Indexed Addressing mode disabled (Legacy mode))
CONFIG DEBUG = OFF      ; Disable In-Circuit Debugger



GLOBAL result
GLOBAL lcounter1
GLOBAL lcounter2
GLOBAL lcounter3
GLOBAL counter1
GLOBAL counter2
GLOBAL toggle_flag
GLOBAL toggle_flag1
GLOBAL timer_flag
GLOBAL portB_state
GLOBAL portC_state
GLOBAL flag
GLOBAL click_reg
GLOBAL click_reg1

; Define space for the variables in RAM
PSECT udata_acs
lcounter1:
    DS 1 ; Allocate 1 byte for var1
lcounter2:
    DS 1
lcounter3:
    DS 1  
counter1:
    DS 1
counter2:
    DS 1
result: 
    DS 1
toggle_flag:
    DS 1
toggle_flag1:
    DS 1
timer_flag:
    DS 1
portB_state:
    DS 1
portC_state:
    DS 1
flag:
    DS 1
click_reg:
    DS 1
click_reg1:
    DS 1

PSECT resetVec,class=CODE,reloc=2
resetVec:
    goto       main

PSECT CODE
main:
  	
    clrf result ; result = 0
    setf lcounter1
    clrf counter1
    clrf counter2
    clrf toggle_flag
    clrf timer_flag
    clrf portB_state
    clrf portC_state
    
    movlw 214
    movwf counter1
    movlw 216
    movwf counter2
    
    
    
    movlw 1
    movwf portB_state
    movlw 8
    movwf portC_state
    
    ; PORTB
    ; LATB
    ; TRISB determines whether the port is input/output
    ; set output ports
    clrf TRISB
    clrf TRISC
    clrf TRISD
    setf TRISE ; PORTE is input
    
    setf LATB
    setf LATC ; light up all pins in PORTC
    setf LATD
    
    busy_wait:
	movlw 00000101B
	movwf lcounter3
	outer_loop:	
	    setf lcounter2
	    inner_loop:
		loop:
		    decf lcounter1
		    bnz loop 
		decf lcounter2
		bnz inner_loop
	    decf lcounter3
	    bnz outer_loop
    
    clrf LATB
    clrf LATC 
    clrf LATD

main_loop:
    call check_buttons
    call check_buttons1
    call update_display_portD
    
    movf timer_flag, 0
    andwf click_reg, 0
    movwf flag
    btfsc flag, 0
    call update_display_portC
    
    movf timer_flag, 0
    andwf click_reg1, 0
    movwf flag
    btfsc flag, 0
    call update_display_portB
    
    bra main_loop

    
re0_pressed:
    ;call clear_latB
    movlw 0xFF
    xorwf toggle_flag,1
    return
check_buttons:
    btfsc PORTE, 0; check RE0, skip if 0
    rcall re0_pressed
    btfss PORTE, 0
    rcall click_register
    return
click_register:
    movlw 0xFF
    andwf toggle_flag,0
    movwf click_reg
    return
    
re1_pressed:
    ;call clear_latC
    movlw 0xFF
    xorwf toggle_flag1,1
    return
check_buttons1:
    btfsc PORTE, 1; check RE1, skip if 0
    rcall re1_pressed
    btfss PORTE, 1
    rcall click_register1
    return
click_register1:
    movlw 0xFF
    andwf toggle_flag1,0
    movwf click_reg1
    return
    
update_display_portC:
    btfsc LATC, 0
    bra clear_latC
    movlw 128
    rrncf LATC, 1
    addwf LATC
    return
    clear_latC:
	clrf LATC
	return
update_display_portB:
    movlw 1
    rlncf LATB, 1
    addwf LATB
    return

update_display_portD:
    clrf timer_flag
    incfsz counter1
    return
    counter1_overflowed:
	movlw 214
	movwf counter1
	incfsz counter2
	return
	counter2_overflowed:
	    movlw 0x01H
	    xorwf PORTD
	    setf timer_flag
	    return
    
end resetVec