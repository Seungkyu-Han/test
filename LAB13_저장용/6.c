#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int left;
    int data;
    int right;
} node;


node *arr;
int avail;

FILE *f;

int main(void) {
    f = fopen("input3.txt", "r");
    if (f == NULL) exit(1);

    fscanf(f, "%d\n", &avail);
    arr = (node*)malloc(sizeof(node) * avail);

    int data, ind = 1;
    while(!feof(f)) {
        fscanf(f, "%d ", &data);
        arr[ind].data = data;
        arr[ind].left = -1;
        arr[ind].right = -1;

        if (data != -1) {
            if (ind % 2)arr[ind/2].right = ind;
            else arr[ind/2].left = ind;
        } else {
            avail++;
            arr = (node*)realloc(arr, sizeof(node) * avail);
        }
        ind++;
    }

    fclose(f);

    printf("%d\n", arr[1].data);
    printf("%d %d\n", arr[arr[1].left].data,arr[arr[1].right].data);
}