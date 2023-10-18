#include <stdio.h>
#include <stdlib.h>
#define SWAP(x,y,temp) (temp = *x, *x = *y, *y = temp)

int min(int x, int y) { return (x<y)? x :y;}
void printArr(int *arr, int size);
void merge(int arr[], int left, int mid, int right);
void iterativeMergeSort(int arr[], int n);
int min(int x, int y);


int main(void) {
    FILE *f = fopen("input.txt", "r");
    if (!f) exit(1);

    int size;
    fscanf(f, "%d\n", &size);
    int arr[20];

    int i;
    for(i = 0; i < size; i++)
        fscanf(f, "%d ", &arr[i]);
    
    fclose(f);

    iterativeMergeSort(arr, size);

    printArr(arr, size);
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


void iterativeMergeSort(int arr[], int size) {
   int i,j;
   for (i = 1; i <= size - 1; i = 2 * i) {
       for (j = 0; j < size - 1; j += 2 * i) {
           merge(arr, j, min(j + i - 1, size - 1), min(j + 2 * i - 1, size - 1));
       }
   }
}

