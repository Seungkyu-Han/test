#include <stdio.h>
#include <stdlib.h>

void push(int item);

int *heap;
int size = 0;
FILE *f;

int main(void) {
    f = fopen("input.txt", "r");
    if (f == NULL) exit(1);

    int total;  //입력되는 수의 개수
    fscanf(f, "%d\n", &total);

    heap = (int*)malloc(sizeof(int) * total);

    int data; 
    for (int i = 0; i < total; i++) {
        fscanf(f, "%d ", &data);
        push(data);
    }

    fclose(f);

    for (int i = 1; i <= size; i++) {
        printf("%d ", heap[i]);
    }
    puts("");
}

void push(int item) {
    int i = ++size;
    while((i != 1) && (item > heap[i/2])) {
        heap[i] = heap[i/2];
        i /= 2;
    }
    heap[i] = item;
}