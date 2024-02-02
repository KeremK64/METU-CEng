#include <stdio.h>

int main(){

    int n, m;
    scanf(" %d %d" ,&n,&m);

    int arr1[n],arr2[m];
    int result[n-m+1];

    for(int i = 0; i<n;i++){
        int x;
        scanf(" %d",&x);
        arr1[i] = x;
    }

    for(int i = 0; i<m;i++){
        int x;
        scanf(" %d",&x);
        arr2[i] = x;
    }

    for(int i = 0; i < n-m+1; i++){
        int sum = 0;
        for(int j = 0; j < m ; j++){

            sum += arr1[i+j]*arr2[j];
        }
        result[i] = sum;

    }
    for(int i = 0; i < n-m+1 ; i++){
        printf("%d ",result[i]);
    }



    return 0;
}
