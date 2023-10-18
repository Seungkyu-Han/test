#include <stdio.h>
#include <stdlib.h>



void push(int item);


int *heap, size = 0;


int main(void) {
    FILE *f = fopen("input.txt", "r");
    if (!f) exit(1);

    int num;
    fscanf(f, "%d\n", &num);
    heap = (int*)malloc(sizeof(int) * (++num));

    int i, data;
    for (i = 0; i < num - 1; i++) {
        fscanf(f, "%d ", &data);
        push(data);
    }

    fclose(f);

    for (i = 1; i <= size; i++)
        printf("%d ", heap[i]);
}

void push(int item) {
    int idx = ++size;

    while(idx != 1 && item < heap[idx / 2]) {
        heap[idx] = heap[idx / 2];
        idx /= 2;
    }

    heap[idx] = item;
}