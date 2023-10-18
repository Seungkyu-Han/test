#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 15

void printData (int data);

int field[MAX_SIZE];
int* link[MAX_SIZE];
FILE* f;
int i;

int main(void) {
    f = fopen("input.txt", "r");
    if (f == NULL) exit(1);

    int num;
    fscanf(f, "%d", &num);

    for (int i = 0; i < num; i++)
        field[i] = -1;
    
    link[0] = NULL;
    i = 0;
    int data;
    
    while(!feof(f)) {
        fscanf(f, "%d", &data);
        field[i] = data;
        if (i > 0) link[i - 1] = &field[i];
        i++;
    }

    fclose(f);

    printData(field[0]);
    i = 1;
    int* temp = link[1];

    while(temp) {
        if ((i == 1) || (i == 3) || (i == 7)) {
            puts("");
        }
        printData(field[i]);
        i++;
        temp = link[i];
    }
    printData(field[i]);
}


void printData (int data) {
    if (data != -1) {
        printf("%d ", data);
    } else {
        printf("e ");
    }
}