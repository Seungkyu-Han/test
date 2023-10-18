#include <stdio.h>
#include <stdlib.h>

void matrixMultiplication(int[][5], int[][5], int[][5], int);

int main(void) {
    FILE *f1 = fopen("input.txt", "r");
    if (f1 == NULL) exit(1);

    int n, arr[5][5], arr2[5][5], arr3[5][5], i, j;

    fscanf(f1, "%d", &n);

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            fscanf(f1, "%d", &arr[i][j]);
        }
    }

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            fscanf(f1, "%d", &arr2[i][j]);
        }
    }  
    fclose(f1);

    matrixMultiplication(arr, arr2, arr3, n);

    FILE *f2 = fopen("output.txt", "w");
    if(f2 == NULL) exit(1);

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            fprintf(f2, "%d ", arr3[i][j]);
        }
        fprintf(f2, "\n");
    }    

    fclose(f2);
}


void matrixMultiplication(int arr[][5], int arr2[][5], int arr3[][5], int n) {
    int i, j, k;

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            int sum = 0;
            for (k = 0; k < n; k++) {
                sum += arr[i][k] * arr2[k][j];
            } 
            arr3[i][j] = sum;
        }
    }
}