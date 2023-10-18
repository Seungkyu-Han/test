#include <stdio.h>
#include <stdlib.h>
#define COMPARE(x, y) ((x > y) ? 1 : ((x == y) ? 0 : -1))

int search(int arr[], int target, int left, int right);

int main(void) {
    FILE *f1 = fopen("input.txt", "r");
    if (f1 == NULL) exit(1);

    int n, m, i, arr[10];
    fscanf(f1, "%d %d", &n, &m);

    for (i = 0; i < n; i++) fscanf(f1, "%d", &arr[i]);

    fclose(f1);


    FILE *f2 = fopen("output.txt", "w");
    if(f2 == NULL) exit(1);

    fprintf(f2, "%d", search(arr, m, 0, n-1));
    fclose(f2);
}


int search(int arr[], int target, int left, int right) {
    int middle;

    while (left <= right) {

        middle = (left + right) / 2;

        switch(COMPARE(arr[middle], target)) {
            case 1 :
                right = middle - 1;
                break;
            case -1 :
                left = middle + 1;
                break;
            case 0 :
                return middle;
        }
    }

    return -1;
}