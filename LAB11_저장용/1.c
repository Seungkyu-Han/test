#include <stdio.h>
#include <stdlib.h>

void inorder(int ptr);
void preorder(int ptr);
void postorder(int ptr);

char tree[20];
FILE *f;

int main(void) {
    f = fopen("input.txt", "r");
    if (f == NULL) exit(1);

    int num;
    fscanf(f, "%d\n", &num);

    for (int i = 0; i < 20; i++)
        tree[i] = 'N';
    
    int ind = 1;
    char data;
    while(!feof(f)) {
        fscanf(f, "%c ", &data);
        tree[ind++] = data;
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
    if  (ptr < 20 && tree[ptr] != 'N') {
        inorder(ptr*2);
        fprintf(f, "%c", tree[ptr]);
        inorder(ptr*2 + 1);
    }
}

void preorder(int ptr) {
    if  (ptr < 20 && tree[ptr] != 'N') {
        fprintf(f, "%c", tree[ptr]);
        preorder(ptr*2);
        preorder(ptr*2 + 1);
    }
}

void postorder(int ptr) {
    if  (ptr < 20 && tree[ptr] != 'N') {
        postorder(ptr*2);
        postorder(ptr*2 + 1);
        fprintf(f, "%c", tree[ptr]);
    }
}

