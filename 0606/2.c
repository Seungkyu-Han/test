#include <stdio.h>
#include <stdlib.h>


typedef struct {
    int data;
    int left, right;
} node;


int main(void) {
    FILE *f = fopen("input.txt", "r");
    if (!f) exit(1);

    int num;
    fscanf(f, "%d\n", &num);
    node *bt = (node*)malloc(sizeof(node) * (++num));

    int data, size = 0;
    while(!feof(f)) {
        fscanf(f, "%d ", &data);
        bt[++size].data = data;
        if (data != -1) {
            if (size % 2) bt[size / 2].right = size;
            else bt[size / 2].left = size;
        } else {
            bt = (node*)realloc(bt, sizeof(node) * (++num));
        }
    }

    fclose(f);

    printf("%d\n", bt[1].data);
    printf("%d\n", bt[bt[1].right].data);
}