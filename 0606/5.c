#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char data;
    int left, right;
}node;


void inorder(node *bt, int idx);
void preorder(node *bt, int idx);
void postorder(node *bt, int idx);


int size = 0;


int main(void) {
    FILE *f = fopen("input.txt", "r");
    if (!f) exit(1);

    int num;
    fscanf(f, "%d\n", &num);
    node *bt = (node*)malloc(sizeof(node) * (++num));

    char data;
    while(!feof(f)) {
        fscanf(f, "%c ", &data);
        bt[++size].data = data;
        bt[size].left = -1;
        bt[size].right = -1;

        if (data == 'N') bt = (node*)realloc(bt, sizeof(node) * (++num));
        else {
            if (size % 2) bt[size / 2].right = size;
            else bt[size / 2].left = size;
        }
    }
    
    fclose(f);


    printf("inorder traversal: ");
    inorder(bt, 1);
    puts("");

    printf("preorder traversal: ");
    preorder(bt, 1);
    puts("");

    printf("postorder traversal: ");
    postorder(bt, 1);
    puts("");  
}


void inorder(node *bt, int idx) {
    if (idx != -1) {
        inorder(bt, bt[idx].left);
        printf("%c", bt[idx].data);
        inorder(bt, bt[idx].right);
    }
}


void preorder(node *bt, int idx) {
    if (idx != -1) {
        printf("%c", bt[idx].data);
        preorder(bt, bt[idx].left);
        preorder(bt, bt[idx].right);
    }
}


void postorder(node *bt, int idx) {
    if (idx != -1) {
        postorder(bt, bt[idx].left);
        postorder(bt, bt[idx].right);
        printf("%c", bt[idx].data);
    }
}