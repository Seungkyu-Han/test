#include <stdio.h>
#include <stdlib.h>
#define SWAP(x,y,temp) (temp = *x, *x = *y, *y = temp)


void printArr(int *arr, int size);
void merge(int arr[], int left, int mid, int right);
void naturalMergeSort(int arr[], int size);


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
    
    naturalMergeSort(arr, size);

    printArr(arr, size);

    free(arr);
    return 0;
}

void printArr(int *arr, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}


void merge(int arr[], int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    i = 0;
    j = 0;
    k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) arr[k] = L[i++];
        else arr[k] = R[j++];
        k++;
    }

    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

void naturalMergeSort(int arr[], int size) {
    int temp[size];
    int left, mid, right;
    int i, j, k;
    int sorted = 0;

    while (!sorted) {
        sorted = 1;
        left = 0;

        while (left < size) {
            for (mid = left; mid < size - 1; mid++) {
                if (arr[mid] > arr[mid + 1]) {
                    sorted = 0;
                    break;
                }
            }
            if (mid == size - 1)
                break;

            right = mid + 1;
            while (right < size - 1 && arr[right] <= arr[right + 1])
                right++;

            merge(arr, left, mid, right);

            left = right + 1;
        }
    }
}
