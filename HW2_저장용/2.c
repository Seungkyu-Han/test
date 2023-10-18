#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
    int nums[10], divide[5] = {0}, corr[10], sum[5] = {0};
    int i, j;

    time_t t = time(NULL);
    srand(t);

    for (i = 0; i < 10; i++) {
        nums[i] = rand() % 25;
        divide[nums[i] / 5] += 1;
        corr[i] = nums[i]  / 5;
    }

    int **ptr = (int**)malloc(sizeof(int*) * 5);
    for (i = 0; i < 5; i++) {
        if (divide[i] != 0) {
            ptr[i] = (int*)malloc(sizeof(int));
            ptr[i][0] = -1;
        } else 
            ptr[i] = (int*)malloc(sizeof(int) * divide[i]);
    }


    for (i = 0; i < 10; i++) {
        int index = corr[i];
        sum[index] += nums[i];
        if (ptr[index][0] != -1) {
            ptr[index][sum[index] - 1] = nums[i];
        }
    }


    for (i = 0; i < 5; i++)
        printf("%d\n", sum[i]);

}