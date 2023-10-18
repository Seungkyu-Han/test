#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int size, *arr, i;

    FILE *f1 = fopen("input.txt", "r");
    if (f1 == NULL) exit(1);

    fscanf(f1, "%d", &size);
    
    arr = malloc(sizeof(int) * size);

    for (i = 0; i < size; i++) {
        fscanf(f1, "%d", &arr[i]);
    }

    fclose(f1);

    int sum = 0;

    for (i = 0; i < size; i++) sum += arr[i];

    free(arr);

    FILE *f2 = fopen("output.txt", "w");
    if (f2 == NULL) exit(1);

    fprintf(f2, "%d", sum);

    fclose(f2);
}