#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0


typedef struct node* nodePointer;
typedef struct node {
    int data;
    nodePointer left, right;
    int leftThread, rightThread;
}node;


nodePointer makeBT(int* bt, int idx);
nodePointer succesor(nodePointer bt);
void insertRight(nodePointer target, nodePointer new);
void inserLeft(nodePointer target, nodePointer new);


int size = 0;


int main(void) {
    FILE *f = fopen("input.txt", "r");
    if (!f) exit(1);

    int num;
    fscanf(f, "%d\n", &num);
    int *abt = (int*)malloc(sizeof(int) * (++num));

    char input[100]; int data;
    while(!feof(f)) {
        fscanf(f, "%s ", input);
        if (input[0] == '+') break;

        data = atoi(input);
        abt[++size] = data;
        if (!data) abt = (int*)realloc(abt, sizeof(int) * (++num));
    }

    int target, new; char pos;
    fscanf(f, "%d %c %d", &target, &pos, &new);

    fclose(f);

    nodePointer bt = makeBT(abt, 1);

}


nodePointer makeBT(int* bt, int idx) {
    nodePointer new = NULL;
    if (idx <= size && bt[idx]) {
        new = (nodePointer)malloc(sizeof(node));
        inserLeft(new, makeBT(bt, idx * 2));
        insertRight(new, makeBT(bt, idx * 2 + 1));
        new->data = bt[idx];
    }

    return new;
}


nodePointer succesor(nodePointer bt) { 
    nodePointer temp = bt->right;
    if (!temp->rightThread) {
        while(!temp->leftThread)
            temp = temp->left;
    }
    
    return temp;
}


void insertRight(nodePointer target, nodePointer new) {
    new->right = target->right;
    new->rightThread = target->rightThread;
    new->left = target;
    new->leftThread = TRUE;

    target->right = new;
    target->rightThread = FALSE;

    nodePointer temp;
    if (!new->rightThread) {
        temp = succesor(target);
        if (temp)
            temp->left = new;
    }
}

void inserLeft(nodePointer target, nodePointer new) {
    new->left = target->left;
    new->leftThread = target->leftThread;
    new->right = target;
    new->rightThread = TRUE;

    target->left = new;
    target->leftThread = FALSE;

    nodePointer temp;
    if (!new->leftThread) {
        temp = succesor(target);
        if (temp) temp->right = new;
    }
}                                                       