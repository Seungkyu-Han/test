#include <stdio.h>
#include <stdlib.h>


void merge(int left, int mid, int right);
void ImergeSort(int size);


int *arr;


int main(void) {
    FILE *f = fopen("input.txt", "r");
    if(!f) exit(1);

    int num;
    fscanf(f, "%d ", &num);
    arr = (int*)malloc(sizeof(int) * num);

    int i;
    for (i = 0; i < num; i++) {
        fscanf(f, "%d ", &arr[i]);
    }

    fclose(f);

    ImergeSort(num);

    for (i = 0; i < num; i++)
        printf("%d ", arr[i]);
}


void merge(int left, int mid, int right) {
    int sorted[100];
    int start = 0, startL = left, startR = mid + 1;

    while(startL <= mid && startR <= right) {
        if (arr[startL] < arr[startR]) sorted[start++] = arr[startL++];
        else sorted[start++] = arr[startR++];
    }

    while(startL <= mid) sorted[start++] = arr[startL++];
    while(startR <= right)  sorted[start++] = arr[startR++];

    for (int i = 0; i < start; i++) {
        arr[left + i] = sorted[i];
    }
}


void ImergeSort(int size) {
    int i, j, mid, right;
    for (i = 1; i <= size; i *= 2) {
        for (j = 0; j < size - 1; j += 2 * i) {
            mid = j + i - 1;
            right = (j + 2*i - 1 > size - 1) ? size - 1 : j + 2*i - 1;

            merge(j, mid, right);
        }
    }
}
