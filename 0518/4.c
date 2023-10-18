#include <stdio.h>
#include <stdlib.h>


typedef struct {
    int data;
    int left, right;
    short int leftthread, rightthread;
}tree;

int main(void) {
    FILE *f = fopen("input.txt", "r");
    if (!f) exit(1);

    int avail;
    fscanf(f, "%d\n", &avail);

    tree *arr = (tree*)malloc(sizeof(tree) * avail);

    int i = 1, data;
    while(fscanf(f, "%d ", &data)) {
        arr[i].data = data;
        arr[i].leftthread = 0; arr[i].rightthread = 0;
        if (data) {
            if (i % 2) arr[i/2].right = i;
            else arr[i/2].left = i;
        } else arr = (tree*)realloc(arr, sizeof(tree) * (++avail));

        if (i * 2 + 1 > avail) {
            arr[i].leftthread = 1; arr[i].rightthread = 1;
            arr[i].left = 
        }
    }

    int target, item;
    char pos;
    fscanf(f, "+ %d %c %d", &target, &pos, &item);

    fclose(f);


}

