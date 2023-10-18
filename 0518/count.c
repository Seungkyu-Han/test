#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


typedef struct tree* treePointer;
typedef struct tree{
    char data;
    treePointer left, right;
}tree;


treePointer createNode(char item);
int findIdx(int start, int end, char v);
treePointer makeBT(int start, int end);
void getResult (treePointer node, int *result, int idx);


char ps[100], is[100];
int idxForPS = 0, result[100];


int main(void) {
    FILE *f = fopen("input3.txt", "r");
    if (!f) exit(1);

    fscanf(f, "preorder sequence : %s\n", ps);
    fscanf(f, "inorder sequence : %s", is);

    fclose(f);

    int len = strlen(ps);

    treePointer bt = makeBT(0, len - 1);

    int result[100];

    int i;
    for(i = 0; i < 100; i++)
        result[i] = 0;

    getResult(bt, result, 1);

    for(i = 0; i < 100; i++) {
        if (result[i])
            printf("%d ", i);
    }
}


treePointer createNode(char item) {
    treePointer new = (treePointer)malloc(sizeof(tree));
    new->data = item;
    new->left = NULL; new->right = NULL;

    return new;
}


int findIdx(int start, int end, char v) {
    for (int i = start; i <= end; i++) {
        if (v == is[i]) return i;
    }
    return -1;
}


treePointer makeBT(int start, int end) {
    treePointer new = NULL;
    int vIdx;

    if (start <= end) {
        new = createNode(ps[idxForPS++]);
        vIdx = findIdx(start, end, new->data);
        new->left = makeBT(start, vIdx - 1);
        new->right = makeBT(vIdx + 1, end);
    }

    return new;
}

void getResult (treePointer node, int *result, int idx) {
    if (node) {
        result[idx] = 1;
        getResult(node->left, result, idx*2);
        getResult(node->right, result, idx*2 + 1);
    }
}
