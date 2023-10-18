#include <stdio.h>
#include <stdlib.h>
#define SWAP(x,y,t) ((t = x), (x = y), (y = t))


void push(int item);
void adjsut(int root, int n);
void heapSort();

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

    heapSort();

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


void adjsut(int root, int n) {
    int  temp = heap[root];
    int child = root * 2;

    while(child <= n) {
        if (child < n && heap[child] > heap[child + 1]) child++;
        if (temp  <= heap[child]) break;

        heap[child / 2] = heap[child];
        child *= 2;
    }

    heap[child / 2] = temp;
}


void heapSort() {
    int t;
    for (int i = size - 1; i > 0; i--) {
        SWAP(heap[1], heap[i + 1], t);
        adjsut(1, i);
    }
}