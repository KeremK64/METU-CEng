#include <stdio.h>
#include <time.h>

int main(){
    clock_t start,end;
    double cpu_time_used;
    start = clock();

    int sizeOfMatrix;
    int limit;
    scanf(" %d %d", &sizeOfMatrix, &limit);
    int matrix[sizeOfMatrix][sizeOfMatrix];

    int sizeOfAvg = 0;
    for(int i = limit;i<=sizeOfMatrix;i++){
        sizeOfAvg += ((sizeOfMatrix-i + 1)*(sizeOfMatrix-i + 1))*4;
    }
    float avg[sizeOfAvg];



    //getting the matrix indexes
    for(int i = 0; i < sizeOfMatrix; i++){
        for(int j = 0; j < sizeOfMatrix; j++){
            scanf(" %d",&matrix[i][j]);
        }
    }

    int index = 0;
    int l = 0;
    float sum;
    while(sizeOfMatrix >= limit){

        for(int i = 0; i < sizeOfMatrix - limit + 1 ; i++){
            for(l = 0; l < sizeOfMatrix - limit + 1; l++){

                sum = 0;
                for(int j = 0;j < limit; j++){
                    for(int k = 0;k < limit; k++){

                        sum += matrix[j+i][k+l];
                    }

                }
                    avg[index] = (sum)/(limit*limit);
                    avg[index + 1] = i;
                    avg[index + 2] = l;
                    avg[index + 3] = limit;

                    index = index + 4;
            }


        }

        limit++;
    }

    /*or(int i = 0;i<sizeOfAvg;i=i+4){
        printf("Avg: %f %f %f %f\n",avg[i],avg[i+1],avg[i+2],avg[i+3]);
    }*/

    float maxAvg = 0;
    for(int i = 0;i<sizeOfAvg;i=i+4){
        if(avg[i] > maxAvg ){
            maxAvg = avg[i];
        }

    }


    int count = 0;
    for(int i = 0; i<sizeOfAvg;i=i+4){
        if(avg[i] == maxAvg){
            count++;
        }
    }
    int j = 0;
    float sizes[3*count];
    for(int i = 0; i<sizeOfAvg;i=i+4){
        if(avg[i] == maxAvg){
            sizes[j] = avg[i+1];
            sizes[j+1] = avg[i+2];
            sizes[j+2] = avg[i+3];
            j = j + 3;
        }
    }



    float largest = 0;
    for(int i = 0 ; i < 3*count ; i = i+3){
        if(sizes[i+2] > largest){
            largest = sizes[i+2];
        }
    }

    int count1 = 0;
    for(int i = 0; i<sizeOfAvg;i=i+4){
        if((avg[i] == maxAvg) && (avg[i+3] == largest)){
            count1++;
        }
    }

    int k = 0;
    float rowCols[2*count1];
    for(int i = 0;i<sizeOfAvg;i = i+4){
        if(avg[i] == maxAvg && avg[i+3] == largest){
            rowCols[k] = avg[i+1];
            rowCols[k+1] = avg[i+2];
            k = k+2;
        }
    }



    float leftmost = 1000000;

    for(int i = 0 ; i < 2*count1 ; i=i+2){
        if(rowCols[i+1] < leftmost){
            leftmost = rowCols[i+1];
        }
    }

    int count2 = 0;
    for(int i = 0;i<sizeOfAvg;i = i+4){
        if((avg[i] == maxAvg) && (avg[i+3] == largest) && (avg[i+2] == leftmost)){
            count2++;
        }
    }

    int a = 0;
    float rows[count2];
    for(int i = 0; i<sizeOfAvg;i=i+4){
        if((avg[i] == maxAvg) && (avg[i+3] == largest) && (avg[i+2] == leftmost)){
            rows[a] = avg[i+1];
            a++;
        }
    }


    float highest = 10000;
    for(int i = 0 ; i < count2;i++){
        if(rows[i] < highest){
            highest = rows[i];
        }
    }

    printf("%d %d %d\n",(int)(highest + 1),(int)(leftmost+1),(int)largest);

    end = clock();

    cpu_time_used = ((double) (end- start)) / CLOCKS_PER_SEC;

    printf("%lf",cpu_time_used);

    /*7 3
5 1 4 5 4 3 5
4 6 3 7 8 2 9
6 2 1 5 7 4 1
2 5 9 1 4 2 8
5 7 5 9 6 4 2
4 6 2 3 4 5 4
4 5 4 4 3 6 2*/
/*6 2
87 62 15 75 35 71
27 24 28 22 35 20
13 79 28 82 25 85
11 11 24 39 37 11
27 88 14 85 11 75
31 26 10 28 19 95
*/

    return 0;
}
