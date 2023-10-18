#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int row;
    int col;
    int value;
}term;

term result2[401];
int cnt = 1;


void multiply(int a[][20], int b[][20], int result[][20], int n);

int main(void) {
    FILE *f1 = fopen("input1.txt", "r");
    if (f1 == NULL) exit(1);

    int n, i,j;
    fscanf(f1, "%d", &n);

    int arr1[20][20] = {0};
    int arr2[20][20] = {0};
    int result[20][20] = {0};

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            int temp;
            fscanf(f1, "%d" , &temp);
            if (temp) 
                arr1[i][j] = temp;
        }
    }

    fclose(f1);

    FILE *f2 = fopen("input1.txt", "r");
    if (f2 == NULL) exit(1);

    int n2;
    fscanf(f2, "%d", &n2);


    for (i = 0; i < n2; i++) {
        for (j = 0; j < n2; j++) {
            int temp;
            fscanf(f2, "%d" , &temp);
            if (temp) 
                arr2[i][j] = temp;
        }
    }

    fclose(f2);

    multiply(arr1, arr2, result, n);


    FILE *f3 = fopen("output.txt", "w");
    if (f3 == NULL) exit(1);

    for (i = 1; i <= cnt; i++)
        fprintf(f3, "%d %d %d\n", result2[i].row, result2[i].col, result2[i].value);

    fclose(f3);
}   

void multiply(int a[][20], int b[][20], int result[][20], int n) {
    int i, j, k;

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            result[i][j] = 0;
            for (k = 0; k < n; k++) {
                result[i][j] += a[i][k] * b[k][j];
            }
        }
    }


    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            int temp = result[i][j];
            if (temp) {
                result2[cnt].col = j;
                result2[cnt].row = i;
                result2[cnt++].value = temp;
            }
        }
    }

    result2[0].row = n;
    result2[0].col = n;
    cnt -= 1;
    result2[0].value = cnt;
}