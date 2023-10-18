#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tree* treePointer;
typedef struct tree {
    treePointer left;
    int data;
    treePointer right;
}tree;

typedef struct{
    int data;
    int left;
    int right;
} term;


treePointer copy(term* original, int avail, int ptr);
treePointer makeBT (FILE *f);
void printTree(treePointer root, int depth);
void insertNode(treePointer root, int index, char pos, int data);
treePointer makeNode(int data);

int i;
int target, item;
int avail;
char pos;

int main(void) {
    FILE *f = fopen("input.txt", "r");
    if (f == NULL) exit(1);
    treePointer bt = makeBT(f);
    
    insertNode(bt, target, pos, item);
    
    printTree(bt, 0);
}

treePointer copy(term* original, int avail, int ptr) {
    if (ptr <= avail && original[ptr].data) {
        treePointer temp = (treePointer)malloc(sizeof(tree));
        temp->left = copy(original,avail, 2 * ptr);
        temp->right = copy(original,avail, 2 * ptr + 1);
        temp->data = original[ptr].data;

        return temp;
    } else
        return NULL;
}

treePointer makeBT (FILE *f) {
    fscanf(f, "%d\n", &avail);
    avail++;
    term* temp = (term*)malloc(sizeof(term) * avail);

    int ind = 1;
    int data;
    char input[20];

    while(!feof(f)) {
        fscanf(f, "%s ", input);

        if (!strcmp(input, "+")){
            break;
        } 

        data = atoi(input);
        temp[ind].data = data;
        temp[ind].left = 0;
        temp[ind].right = 0;

        if (data) {
            if (ind % 2) temp[ind/2].right = ind;
            else temp[ind/2].left = ind;
        } else {
            avail++;
            temp = (term*)realloc(temp, sizeof(term) * avail);
        }
        ind++;
    }

    fscanf(f, "%d %c %d", &target, &pos, &item);
    fclose(f);

    treePointer bt = copy(temp, avail, 1);

    return bt;
}

void printTree(treePointer root, int depth) {
    if (root == NULL) return;
    
    printTree(root->right, depth+1);
    
    for (int i = 0; i < depth; i++) {
        printf("    ");
    }
    
    printf("%d\n", root->data);
    
    printTree(root->left, depth+1);
}

void findNode(treePointer root, treePointer *target, int index) {
    if (root == NULL) return;

    if (root->data == index) {
        *target = root;
        return;
    }

    findNode(root->left, target, index);
    findNode(root->right, target, index);
}

void insertNode(treePointer root, int index, char pos, int data) {
    treePointer target;
    findNode(root, &target, index);

    if (target == NULL) {
        printf("Node not found!\n");
        return;
    }

    treePointer newNode = makeNode(data);

    if (pos == 'L') {
        newNode->left = target->left;
        target->left = newNode;
    } else if (pos == 'R') {
        newNode->right = target->right;
        target->right = newNode;
    } else {
        printf("Invalid position!\n");
        free(newNode);
    }
}

treePointer makeNode(int data) {
    treePointer newNode = (treePointer)malloc(sizeof(tree));
    newNode->left = NULL;
    newNode->data = data;
    newNode->right = NULL;

    return newNode;
}

