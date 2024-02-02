#include <iostream>
using namespace std;
#include <string>

int findMaxLength(string* arr, int size) {
    int maxLen = 0;
    for (int i = 0; i < size; i++) {
        int len = 0;
        while (arr[i][len] != '\0') {
            len++;
        }
        if (len > maxLen) {
            maxLen = len;
        }
    }
    return maxLen;
}

int counting_sort(string* arr, int size, int maxSize, bool ascending) {
    int iterations = 0;

    int* count = new int[27];
    for(int i = 0; i < 27; i++){
        count[i] = 0;
    }

    for(int j = 0; j < size; j++){
        if(arr[j].size() > maxSize){
            if(ascending){
                count[arr[j][maxSize] - 'A' + 1]++;
            }
            else {
                count['Z' - arr[j][maxSize]]++;
            }
        }
        else{
            if(ascending)
                count[0]++;
            else
                count[26]++;
        }
        iterations++;
    }

    for(int i = 1; i < 27; i++){
        count[i] = count[i] + count[i-1];

        iterations++;
    }

    string* output = new string[size];

    int index = 0;
    for(int j = size - 1; j >= 0; j--){
        if(arr[j].size() > maxSize){
            index = (ascending) ? (arr[j][maxSize] - 'A' + 1) : ('Z' - arr[j][maxSize]);
        }
        else{
            if(ascending)
                index = 0;
            else
                index = 26;
        }
        output[count[index]-1] = arr[j];
        count[index]--;
        iterations++;
    }

    for(int i = 0; i < size; i++){
        arr[i] = output[i];
        iterations++;
    }

    delete[] output;

    return iterations;
}

int radix_string_sort(string* arr, int size, bool ascending) {

    int max_length = findMaxLength(arr, size);

    int iterations = 0;

    for (int maxSize = max_length-1; maxSize >= 0; maxSize--) {
        iterations += counting_sort(arr, size, maxSize, ascending);
    }

    return iterations;
}

int main() {

    std::string arr1[] = {"GAUSS", "EULER", "TAO", "CANTOR", "NEWTON", "POINCARE", "LAGRANGE", "CAUCHY",
                          "FOURIER", "LAPLACE", "LEIBNIZ", "FERMAT"};

    int a = radix_string_sort(arr1, 12, 0);

    for(int i = 0; i < 12; i++){
        cout << arr1[i] << " ";
    }
    cout << a << "\n";
    return 0;
}
