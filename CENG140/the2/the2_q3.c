#include <stdio.h>

int main(void){
    int n,m,numberOfCircles,isStat,x,y,radius,depth;
    char letter;

    scanf(" %d %d %d %d",&n,&m,&numberOfCircles,&isStat);

    char grid[m][n];
    for(int i = 0 ;i<m;i++){
        for(int j = 0; j<n;j++){
            grid[i][j] = '-';
        }
    }


    char letters[numberOfCircles];
    int depths[numberOfCircles];
    int letterCounts[numberOfCircles];
    int hiddenOnes[numberOfCircles];
    int allPossibleOnes[numberOfCircles];

    for(int i = 0;i<numberOfCircles;i++){
        allPossibleOnes[i] = 0;
    }


    for(int i = 0;i<numberOfCircles;i++){
        hiddenOnes[i] = 0;
    }

    for(int i = 0;i<numberOfCircles;i++){
        letterCounts[i] = 0;
    }
    for(int i = 0; i < numberOfCircles; i++){
        scanf(" %c %d %d %d %d",&letter,&x,&y,&radius,&depth);

            for(int u = -1000; u < 1000; u++){
                for(int z = -1000; z < 1000 ; z++){
                    if((x-z)*(x-z) + (y-u)*(y-u) <= radius*radius){
                        allPossibleOnes[i]++;
                }
            }
        }

        letters[i] = letter;
        depths[i] = depth;
        for(int j = m; j > 0; j--){
            for(int k = n; k > 0; k--){
                if((y-j)*(y-j) + (x-k)*(x-k) <= radius*radius){
                    if(grid[m-j][k-1] == '-'){
                        grid[m-j][k-1] = letter;
                        letterCounts[i]++;
                    }
                    else{
                        for(int a = 0; a < numberOfCircles; a++){
                            if(grid[m-j][k-1] == letters[a]){
                                if(depths[a] > depth){
                                    grid[m-j][k-1] = letter;
                                    letterCounts[i]++;
                                    letterCounts[a]--;
                                    hiddenOnes[a]++;
                                    hiddenOnes[i]--;
                                }
                                else{
                                    hiddenOnes[i]++;
                                }
                            }

                        }
                    }
                }
            }
        }
    }

    for(int i = 0;i<m;i++){
        printf("\n");
        for(int j = 0;j<n;j++){
            printf("%c%c",grid[i][j],grid[i][j]);
        }
    }
    printf("\n");




    if(isStat){
        for(int i = 0 ; i < numberOfCircles; i++){
            printf("%d %d %d\n",letterCounts[i],hiddenOnes[i],allPossibleOnes[i]-letterCounts[i]-hiddenOnes[i]);
        }
    }


    /*30 20 4 1
C 10 9 8 700
E 12 10 4 200
N 16 14 7 400
G 25 20 8 900*/

    return 0;
}
