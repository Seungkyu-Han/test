#include <stdio.h>
#include <stdlib.h>


void insertionSort(int n);
void insert(int item, int end);


int *arr;


int main(void) {
    FILE *f = fopen("input.txt", "r");
    if (!f) exit(1);

    int num;
    fscanf(f, "%d\n", &num);
    arr = (int*)malloc(sizeof(int) * (num + 1));

    int i;
    for (i = 1; i <= num; i++) 
        fscanf(f, "%d ", &arr[i]);
    
    fclose(f);

    insertionSort(num);

    for (i = 1; i <= num; i++) 
        printf("%d ", arr[i]);
}

void insertionSort(int n) {
    for (int i = 2; i <= n; i++) {
        insert(arr[i], i - 1);
    }
}

void insert(int item, int n) {
    arr[0] = item;

    while(item < arr[n]) {
        arr[n + 1] = arr[n];
        n--;
    }

    arr[n + 1] = item;
}