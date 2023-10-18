#include <stdio.h>
#include <stdlib.h>
#define SWAP(x,y,temp)((temp = *x), (*x = *y), (*y = temp))

void printTree();
void push(int item);
void adjust(int size);


int *heap;
int size = 0;
int max_size;


int main(void) {
    FILE *f = fopen("input.txt", "r");
    if (!f) exit(1);

    fscanf(f, "%d\n", &max_size);
    heap = (int*)malloc(sizeof(int) * (max_size + 1));

    int data;
    for (int i = 0; i < max_size; i++) {
        fscanf(f, "%d ", &data);
        push(data);
    }

    fclose(f);

    int temp;
    for (int i = max_size - 1; i > 0; i--) {
        SWAP(&heap[1], &heap[i + 1], temp);
        adjust(i);
    }

    printTree();
}



void printTree() {
    for (int i = 1; i <= size; i++) {
        printf("%d ", heap[i]);
    }
    puts("");
}


void push(int item) {
    int idx = ++size;
    while((idx > 1) && (item < heap[idx/2])) {
        heap[idx] = heap[idx/2];
        idx /= 2;
    }
    heap[idx] = item;
}


void adjust(int size) {
    if (!size) {
        printf("the heap is empty now\n");
        exit(1);
    }

    int temp = heap[1];
    int parent = 1, child = 2;

    while((child <= size)) {
        if ((child < size) && (heap[child] > heap[child + 1]))
            child++;
        if (temp <= heap[child]) break;

        heap[parent] = heap[child];
        parent = child;
        child *= 2;
    }
    heap[parent] = temp;
}