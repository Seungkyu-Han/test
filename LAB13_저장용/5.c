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


treePointer createNode(logical item);
treePointer makeBT (logical *arr, int index);
void printTree(treePointer root, int depth);
void evaluate (treePointer node);


logical arr[1000];
int avail;

int main(void) {
    FILE *f = fopen("input.txt", "r");
    if (f == NULL) exit(1);

    fscanf(f, "%d", &avail);
    logical* tvalue = (logical*)malloc(sizeof(logical) * avail);

    char str[20];
    for (int i = 0; i < avail; i++) {
        fscanf(f, "%s", str);
        if (strcmp(str, "true,") && strcmp(str, "true")) tvalue[i] = false;
        else tvalue[i] = true;
    }

    int ind = 1;
    while(!feof(f)) {
        fscanf(f, "%s ", str);
        
        if (!strcmp(str, "not")) {
            arr[ind] = not;
        } else if (!strcmp(str, "and")) {
            arr[ind] = and;
        } else if (!strcmp(str, "or")) {
            arr[ind] = or;
        } else if (!strcmp(str, "true")) {
            arr[ind] = true;
        } else if (!strcmp(str, "false")) {
            arr[ind] = false;
        } else {
            arr[ind] = 5;
        }
        ind++;
    }

    avail = ind - 1;

    fclose(f);

    treePointer root = makeBT(arr, 1);

    
    evaluate(root);

    if (root->data == or) printf("true\n");
    else printf("false\n");
}


treePointer createNode(logical item) {
    treePointer new = (treePointer)malloc(sizeof(tree));
    new->data = item;
    new->value = 0;
    new->left = NULL;
    new->right = NULL;

    return new;
}

treePointer makeBT (logical *arr, int index) {
    treePointer temp = NULL;

    if (index <= avail) {
        temp = createNode(arr[index]);

        if (arr[index] == or || arr[index] == and || arr[index] == not || arr[index] == true || arr[index] == false) {
            temp->left = makeBT(arr, 2 * index);
            temp->right = makeBT(arr, 2 * index + 1);
        } 
    }

    return temp;
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
                node->value = 1;
                break;
            case false:
                node->value = 0;
        }
    }
}   


