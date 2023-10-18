#include <stdio.h>
#include <stdlib.h>


typedef struct node* nodePointer;
typedef struct node {
    int data;
    nodePointer left, right;
}node;


nodePointer copy(int *bt, int idx, int size);
void inorder(nodePointer root);
int equality (nodePointer bt1, nodePointer bt2);


int main(void) {
    FILE *f = fopen("input1.txt", "r");
    if (!f) exit(1);

    int num;
    fscanf(f, "%d\n", &num);
    int *bt1 = (int*)malloc(sizeof(int) * (++num));

    int data, size1 = 0;
    while(!feof(f)) {
        fscanf(f, "%d ", &data);
        bt1[++size1] = data;
        if (data == -1) bt1 = (int*)realloc(bt1, sizeof(int) * (++num));
    }

    fclose(f);


    f = fopen("input2.txt", "r");
    if (!f) exit(1);

    fscanf(f, "%d\n", &num);
    int *bt2 = (int*)malloc(sizeof(int) * (++num));

    int size2 = 0;
    while(!feof(f)) {
        fscanf(f, "%d ", &data);
        bt2[++size2] = data;
        if (data == -1) bt2 = (int*)realloc(bt2, sizeof(int) * (++num));
    }

    fclose(f);

    nodePointer lbt1 = copy(bt1, 1, size1);
    nodePointer lbt2 = copy(bt2, 1, size2);

    if (equality(lbt1, lbt2)) {
        printf("equals\n");
    } else printf("not eqauls\n");
}


nodePointer copy(int *bt, int idx, int size) {
    nodePointer new = NULL;
    if (idx <= size && bt[idx] != -1) {
        new = (nodePointer)malloc(sizeof(node));
        new->left = copy(bt, idx * 2, size);
        new->right = copy(bt, idx * 2 + 1, size);
        new->data = bt[idx];
    }

    return new;
}


void inorder(nodePointer root) {
    if (root) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

int equality (nodePointer bt1, nodePointer bt2) {
    return ((!bt1 && !bt2) || (bt1 && bt2 && (bt1->data == bt2->data) && equality(bt1->left, bt2->left) && equality(bt1->right, bt2->right)));
}