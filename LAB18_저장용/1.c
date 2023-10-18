#include <stdio.h>
#include <stdlib.h>
#define SWAP(x,y,temp) (temp = *x, *x = *y, *y = temp)


void printArr(int *arr, int size);
int partition(int arr[], int low, int high);
void quickSort(int arr[], int left, int right);

int main(void) {
    FILE *f = fopen("input.txt", "r");
    if (!f) exit(1);

    int size;
    fscanf(f, "%d\n", &size);
    int *arr = (int*)malloc(sizeof(int) * size);

    int i;
    for(i = 0; i < size; i++)
        fscanf(f, "%d ", &arr[i]);
    
    fclose(f);
    
    quickSort(arr, 0, size - 1);
    printArr(arr, size);

}


void printArr(int *arr, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}


int partition(int arr[], int left, int right) {
    int pivot = left;
    int i = left + 1, j = right;
    int temp;

    while(i <= j) {
        while(i <= j && arr[i] <= arr[pivot]) i++;
        while(i <= j && arr[j] >= arr[pivot]) j--;
        if (i < j) SWAP(&arr[i], &arr[j], temp);
    }

    SWAP(&arr[left], &arr[j], temp);
    return j;
}

void quickSort(int arr[], int left, int right) {
    if (left < right) {
        int pivot = partition(arr, left, right);
        quickSort(arr, left, pivot - 1);
        quickSort(arr, pivot + 1, right);
    }
}