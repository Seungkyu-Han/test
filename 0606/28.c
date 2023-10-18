#include <stdio.h>
#include <stdlib.h>

void merge(int left, int mid, int right);
void mergeSort(int left, int right);


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
    
    mergeSort(0, num - 1);

    for (i = 0; i < num; i++)
        printf("%d ", arr[i]);
}


void merge(int left, int mid, int right) {
    int sorted[100];
    int startL = left, startR = mid + 1, start = 0;

    while(startL <= mid && startR <= right) {
        if (arr[startL] < arr[startR]) sorted[start++] = arr[startL++];
        else sorted[start++] = arr[startR++];
    }

    while(startL <= mid) sorted[start++] = arr[startL++];
    while(startR <= right) sorted[start++] = arr[startR++];

    for (int i = 0; i < start; i++) {
        arr[i + left] = sorted[i];
    }
}

void mergeSort(int left, int right) {
    int mid;
    if (left < right) {
        mid = (left + right) / 2;
        mergeSort(left, mid);
        mergeSort(mid + 1, right);

        merge(left, mid, right);
    }
}