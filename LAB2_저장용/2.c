#include <stdio.h>
#include <stdlib.h>

int main(void) {
    FILE * f1 = fopen("input.txt", "r");
    if(f1 == NULL) exit(1);

    int n, i;
    fscanf(f1, "%d", &n);

    float *arr;
    arr = (float *) malloc(sizeof(float) * n);

    for (i = 0; i < n; i++) 
        fscanf(f1, "%f", &arr[i]);

    fclose(f1);

    FILE * f2 = fopen("output.txt", "w");
    if(f2 == NULL) exit(1);

    for (i = 0; i < n; i++) {
        if (arr[i] - (int)arr[i])
            fprintf(f2, "%.1f ", arr[i]);
    }
    
    fclose(f2);
}