#include <stdio.h>
#include <stdlib.h>
#define SWAP(x,y,t) ((t) = (x), (x) = (y), (y) = (t))

void push(int item);
void heapSort(int arr[]);
void adjust (int arr[], int root, int size);

int * minHeap;
int size = 0;
FILE *f;

int main(void) {
    f = fopen("input.txt", "r");
    if (f == NULL) exit(1);

    int total;  //입력되는 수의 개수
    fscanf(f, "%d\n", &total);

    minHeap = (int*)malloc(sizeof(int) * total);

    int data; 
    for (int i = 0; i < total; i++) {
        fscanf(f, "%d ", &data);
        push(data);
    }

    fclose(f);

    heapSort(minHeap);

    for (int i = 1; i <= size; i++) {
        printf("%d ", minHeap[i]);
    }
    puts("");
}

void push(int item) {
    int i = ++size;
    while((i != 1) && (item < minHeap[i/2])) {
        minHeap[i] = minHeap[i/2];
        i /= 2;
    }
    minHeap[i] = item;
}

void heapSort(int arr[]) {
    int i, j, temp;

    for (i = size/2; i > 0; i--)
        adjust(arr, i, size);
    for(i = size - 1; i > 0; i--) {
        SWAP(arr[1], arr[i + 1], temp);
        adjust(arr, 1, i);
    }
}

void adjust (int arr[], int root, int size) {
    int child = 2 * root, temp = arr[root];
    while(child <= size) {
        if ((child < size) && (arr[child] > arr[child + 1]))
            child++;
        if (temp < arr[child]) break;
        else {
            arr[child/2] = arr[child];
            child *= 2;
        }
    }
    arr[child/2] = temp;
}