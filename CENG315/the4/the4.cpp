
#include <iostream>

using namespace std;


int max(int a, int b){
    return a > b ? a : b;
}

int divide_land(int X, int Y, bool **possible_plots)
{

    int dpTable[X + 1][Y + 1];

    for(int i = 0; i <= X; i++){
        for(int j = 0; j <= Y; j++){
            dpTable[i][j] = 0;
        }
    }

    for (int i = 1; i <= X; i++)
    {
        for (int j = 1; j <= Y; j++)
        {

            int option1 = possible_plots[i][j] ? i * j : 0;

            int option2 = -1000000;
            int option3 = -1000000;

            for (int k = 1; k <= i; k++){
                option2 = max(dpTable[k][j] + dpTable[i - k][j], option2);
            }

            for (int l = 1; l <= j; l++){
                option3 = max(dpTable[i][j-l] + dpTable[i][l], option3);
            }

            dpTable[i][j] = max(max(option1, option2), option3);
        }
    }

    return X * Y - dpTable[X][Y];
}


int main()
{
    bool** zort;

    for(int i = 0; i <= 11; i++){
        for(int j = 0; j <= 7; j++){
            zort[i][j] = false;
        }
    }

    zort[4][5] = true;
    zort[6][7] = true;

    int X = 11;
    int Y = 7;

    int result = divide_land(X, Y, zort);

    return 0;
}
