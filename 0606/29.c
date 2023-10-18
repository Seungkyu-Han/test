#include <stdio.h>
#include <stdlib.h>

void merge (int *arr, int left, int mid, int right);
void naturalMergeSort(int *arr, int n);


int main(void) {
    FILE *f = fopen("input.txt", "r");
    if(!f) exit(1);

    int num;
    fscanf(f, "%d ", &num);
    int *arr = (int*)malloc(sizeof(int) * num);

    int i;
    for (i = 0; i < num; i++) {
        fscanf(f, "%d ", &arr[i]);
    }

    fclose(f);

    naturalMergeSort(arr, num);

    for (i = 0; i < num; i++)
        printf("%d ", arr[i]);
}

void merge (int *arr, int left, int mid, int right) {
    int sorted[100];

    int startL = left;
    int startR = mid + 1;
    int start = left;

    while(startL <= mid && startR <= right) {
        if (arr[startL] < arr[startR]) sorted[start++] = arr[startL++];
        else sorted[start++] = arr[startR++];
    }

    while(startL <= mid) sorted[start++] = arr[startL++];
    while(startR <= right) sorted[start++] = arr[startR++];

    for (int i = left; i <= right; i++)
        arr[i] = sorted[i];
}


void naturalMergeSort(int *arr, int n) {
    int left, mid, right, check;

    while(1) {
        left = 0;
        check = 1;

        while(left < n) {
            mid = left;
            for (; mid < n - 1 && arr[mid] <= arr[mid + 1]; mid++);

            right = mid + 1;
            if (right == n) break;

            for (; right < n - 1 && arr[right] <= arr[right + 1]; right++);

            merge(arr, left, mid, right);
            check = 0;
            left = right + 1;
        }
        if (check) break;
    }
}

