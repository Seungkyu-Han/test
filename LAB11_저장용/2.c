#include <stdio.h>
#include <stdlib.h>

void inorder(int ptr);
void preorder(int ptr);
void postorder(int ptr);

typedef struct{
    char data;
    int left;
    int right;
} node;

node tree[20];
FILE *f;

int main(void) {
    f = fopen("input.txt", "r");
    if (f == NULL) exit(1);

    int num;
    fscanf(f, "%d\n", &num);

    for (int i = 0; i < 20; i++) {
        tree[i].left = -1;
        tree[i].right = -1;
    }
    
    int ind = 1;
    char data;
    while(!feof(f)) {
        fscanf(f, "%c ", &data);
        tree[ind].data = data;

        if (data != 'N') {
            if (ind % 2) tree[ind/2].right = ind;
            else tree[ind/2].left = ind;
        }
        ind += 1;
    }

    fclose(f);

    f = fopen("output.txt", "w");
    if (f == NULL)exit(1);

    fprintf(f, "inorder traversal: ");
    inorder(1);
    fprintf(f, "\n");

    fprintf(f, "preorder traversal: ");
    preorder(1);
    fprintf(f, "\n");

    fprintf(f, "postorder traversal: ");
    postorder(1);    
    fprintf(f, "\n");

    fclose(f);
}

void inorder(int ptr) {
    if  (ptr != -1) {
        inorder(tree[ptr].left);
        fprintf(f, "%c", tree[ptr].data);
        inorder(tree[ptr].right);
    }
}

void preorder(int ptr) {
    if  (ptr != -1) {
        fprintf(f, "%c", tree[ptr].data);
        preorder(tree[ptr].left);
        preorder(tree[ptr].right);
    }
}

void postorder(int ptr) {
    if  (ptr != -1) {
        postorder(tree[ptr].left);
        postorder(tree[ptr].right);
        fprintf(f, "%c", tree[ptr].data);
    }
}

