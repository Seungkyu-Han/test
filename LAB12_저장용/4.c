#include <stdio.h>
#include <stdlib.h>

typedef struct tree* treePointer;
typedef struct tree{
    char data;
    treePointer left;
    treePointer right;
}tree;

typedef struct{
    char data;
    int left;
    int right;
} term;


treePointer copy(term* original, int ptr);
void push(treePointer* stack, int *top, treePointer item);
treePointer pop(treePointer *stack, int *top);
void Ipreorder(treePointer ptr);

FILE *f;
int avail;

int main(void) {
    f = fopen("input.txt", "r");
    if (f == NULL) exit(1);

    fscanf(f, "%d\n", &avail);
    term* temp = (term*)malloc(sizeof(term) * avail);

    int ind = 1;
    char data;
    while(!feof(f)) {
        fscanf(f, "%c ", &data);
        temp[ind].data = data;
        temp[ind].left = -1;
        temp[ind].right = -1;

        if (data != 'N') {
            if (ind % 2) temp[ind/2].right = ind;
            else temp[ind/2].left = ind;
        } else {
            avail++;
            temp = (term*)realloc(temp, sizeof(term) * avail);
        }
        ind++;
    }

    fclose(f);

    treePointer tree = copy(temp, 1);

    f = fopen("output.txt", "w");
    if (f == NULL)exit(1);

    fprintf(f, "iterative implementation of preorder traversal : ");
    Ipreorder(tree);

    fclose(f);
    free(temp);
    free(tree);
}

treePointer copy(term* original, int ptr) {
    if (ptr <= avail && original[ptr].data != 'N') {
        treePointer temp = (treePointer)malloc(sizeof(tree));
        temp->left = copy(original, 2 * ptr);
        temp->right = copy(original, 2 * ptr + 1);
        temp->data = original[ptr].data;

        return temp;
    } else
        return NULL;
}

void inorder(treePointer ptr) {
    if  (ptr) {
        inorder(ptr->left);
        fprintf(f, "%c", ptr->data);
        inorder(ptr->right);
    }
}





void push(treePointer* stack, int *top, treePointer item) {
    if (*top >= 19) {
        printf("stack is full\n");
        exit(1);
    } else {
        stack[++(*top)] = item;
    }
}

treePointer pop(treePointer *stack, int *top) {
    if (*top < 0) {
        return 0;
    } else {
        return stack[(*top)--];
    }
}


void Ipreorder(treePointer ptr) {
    treePointer stack[20];
    int top = -1;

    push(stack, &top, ptr);

    while (top > -1) {
        ptr = pop(stack, &top);
        fprintf(f, "%c", ptr->data);

        if (ptr->right) push(stack, &top, ptr->right);
        if (ptr->left) push(stack, &top, ptr->left);
    }
}

