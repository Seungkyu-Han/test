#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {not, and, or, true, false} logical;

typedef struct tree* treePointer;
typedef struct tree {
    treePointer left;
    logical data;
    short int value;
    treePointer right;
}tree;

typedef struct{
    int left;
    logical data;
    short int value;
    int right;
} term;

treePointer copy(term* original, int avail, int ptr);
treePointer makeBT (FILE *f);
void printTree(treePointer root, int depth);
void evaluate (treePointer node);

int i;

int main(void) {
    FILE *f = fopen("input.txt", "r");
    if (f == NULL) exit(1);
    treePointer bt = makeBT(f);

    printTree(bt, 0);

    evaluate(bt);

    // if (bt->data == or) printf("true\n");
    // else printf("false\n");
}

treePointer copy(term* original, int avail, int ptr) {
    if (ptr <= avail && original[ptr].data != 5) {
        treePointer temp = (treePointer)malloc(sizeof(tree));
        temp->left = copy(original,avail, 2 * ptr);
        temp->right = copy(original,avail, 2 * ptr + 1);
        temp->data = original[ptr].data;

        return temp;
    } else
        return NULL;
}

treePointer makeBT (FILE *f) {
    int num;
    fscanf(f, "%d", &num);
    logical* tvalue = (logical*)malloc(sizeof(logical) * num);

    int data;
    char str[20];
    for (int i = 0; i < num; i++) {
        fscanf(f, "%s", str);
        if (strcmp(str, "true,") && strcmp(str, "true")) tvalue[i] = false;
        else tvalue[i] = true;
    }

    term* temp = (term*)malloc(sizeof(term) * num);
    int ind = 1; 

    while(!feof(f)) {
        fscanf(f, "%s ", str);

        if (!strcmp(str, "empty")) {
            temp[ind].left = -1;
            temp[ind].right = -1;
            temp[ind].data = 5;

            num++;
            temp = (term*)realloc(temp, sizeof(term) * num);
        } else {

            if (!strcmp(str, "not")) {
                temp[ind].data = not;
            }
            else if (!strcmp(str, "and")) {
                temp[ind].data = and;
            }
            else if (!strcmp(str, "or")) {

                temp[ind].data = or;
            }
            else {
                int order = str[1] - '0' - 1;
                temp[ind].data  = tvalue[order];
            }

            if (ind % 2) temp[ind/2].right = ind;
            else temp[ind/2].left = ind;
        }
        ind++;
    }

    fclose(f);

    treePointer bt = copy(temp, num, 1);

    return bt;

}

void printTree(treePointer root, int depth) {
    if (root == NULL) return;
    
    printTree(root->right, depth+1);
    
    for (int i = 0; i < depth; i++) {
        printf("    ");
    }
    if (root->data == not) printf("%4s\n", "not");
    else if (root->data == and) printf("%4s\n", "and");
    else if (root->data == or) printf("%4s\n", "or");
    else if (root->data == true) printf("%4s\n", "true");
    else if (root->data == false) printf("%4s\n", "false");
    
    printTree(root->left, depth+1);
}

void evaluate (treePointer node) {
    if (node) {
        evaluate(node->left);
        evaluate(node->right);
        switch(node->data) {
            case not:
                node->value = !(node->right->value);
                break;
            case and:
                node->value = (node->right->value && node->left->value);
                break;
            case or:
                node->value = (node->right->value || node->left->value);
                break;                
            case true:
                node->value = true;
                break;
            case false:
                node->value = false;
        }
    }
}   


