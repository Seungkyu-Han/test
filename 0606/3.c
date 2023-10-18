#include <stdio.h>
#include <stdlib.h>


typedef struct node* nodePointer;
typedef struct node {
    int data;
    nodePointer left, right;
}node;


nodePointer createNode(int item);
nodePointer copy(int * bt, int idx);
void inorder(nodePointer bt);


int size = 0;


int main(void) {
    FILE *f = fopen("input.txt", "r");
    if (!f) exit(1);

    int num;
    fscanf(f, "%d\n", &num);
    int *bt = (int*)malloc(sizeof(int) * (++num));

    while(!feof(f)) {
        fscanf(f, "%d ", &bt[++size]);
        if (bt[size] == -1) bt = (int*)realloc(bt, sizeof(int) * (++num));
    }

    fclose(f);

    nodePointer linked_bt = copy(bt, 1);

    inorder(linked_bt);
    puts("");
}




nodePointer createNode(int item) {
    nodePointer new = (nodePointer)malloc(sizeof(node));
    new->data = item;
    new->left = NULL; new->right = NULL;

    return new;
}

nodePointer copy(int * bt, int idx) {
    nodePointer new = NULL;
    if (idx <= size && bt[idx] != -1) {
        new =  createNode(bt[idx]);
        new->left = copy(bt, idx * 2);
        new->right = copy(bt, idx * 2 + 1);
    }

    return new;
}


void inorder(nodePointer bt) {
    if (bt) {
        inorder(bt->left);
        printf("%d ", bt->data);
        inorder(bt->right);
    }
}
