#include <stdio.h>
#include <stdlib.h>

void printData (int data);

int bTree[15];
FILE *f;

int main(void) {
    for (int i = 0; i < 15; i++)
        bTree[i] = -1;

    f = fopen("input.txt", "r");
    if (f == NULL) exit(1);

    int num;
    fscanf(f, "%d", &num);

    int ind = 0, data;

    while(!feof(f)) {
        fscanf(f, "%d", &data);
        bTree[ind] = data;
        
        ind++;
    }

    fclose(f);

    for (int i = 0; i < 15; i++) {
        if ((i == 1) || (i == 3) || (i == 7)) {
            puts("");
        }
        printData(bTree[i]);
    }
}


void printData (int data) {
    if (data != -1) {
        printf("%d ", data);
    } else {
        printf("e ");
    }
}