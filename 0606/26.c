#include <stdio.h>
#include <stdlib.h>
#define SWAP(x,y,t) ((t = x), (x = y), (y = t))


void quickSort (int left, int right);


int *arr;


int main(void) {
    FILE *f = fopen("input.txt", "r");
    if (!f) exit(1);

    int num;
    fscanf(f, "%d\n", &num);
    arr = (int*)malloc(sizeof(int) * (num + 1));

    int i;
    for (i = 0; i < num; i++) 
        fscanf(f, "%d ", &arr[i]);
    
    fclose(f);


    quickSort(0, num - 1);

    for (i = 0; i < num; i++) 
        printf("%d ", arr[i]);
}

void quickSort (int left, int right) {
    int i, j, pivot, t;
    if (left < right) {
        pivot = arr[left];
        i = left; j = right + 1;

        do {
            do i++; while(i <= j && arr[i] <= pivot);
            do j--; while(i <= j && arr[j] >= pivot);
            if (i < j) SWAP(arr[i], arr[j], t);
        }while(i < j);

        SWAP(arr[left], arr[j], t);
        quickSort(left, j - 1);
        quickSort(j + 1, right);
    }
}

