#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int n,m, i, j;

    FILE * f1 = fopen("input.txt", "r");
    if(f1 == NULL) exit(1);

    fscanf(f1, "%d %d", &n, &m);


    int **arr1, **arr2;
    arr1 = (int **) malloc(n * sizeof(int*));
    arr2 = (int **) malloc(n * sizeof(int*));

    for (i = 0; i < m; i++) {
        arr1[i] = malloc(sizeof(int) * m);
        arr2[i] = malloc(sizeof(int) * m);
    }


    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            fscanf(f1, "%d", &arr1[i][j]);
        }
    }

    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            fscanf(f1, "%d", &arr2[i][j]);
        }
    }
    
    fclose(f1);

    FILE * f2 = fopen("output.txt", "w");
    if(f2 == NULL) exit(1);

    for(i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            fprintf(f2, "%d ", arr1[i][j] + arr2[i][j]);
        }
        fprintf(f2, "\n");
    }

    fclose(f2);
}