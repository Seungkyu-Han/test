#include <stdio.h>
#include <stdlib.h>

int main(void) {
    FILE *f = fopen("input.txt", "r");
    if (!f) exit(1);

    int num;
    fscanf(f, "%d\n", &num);
    int *bt = (int*)malloc(sizeof(int) * (++num));

    int size = 0, data; 
    while(!feof(f)) {
        fscanf(f, "%d\n", &data);
        bt[++size] = data;
        if (data == -1) bt = (int*)realloc(bt, sizeof(int) * (++num));
    }

    fclose(f);

    for (int i = 1; i <= size; i++) {
        printf("%d ", bt[i]);
    }
}