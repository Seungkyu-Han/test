#include <stdio.h>
#include <stdlib.h>


void inorder(char *bt, int idx);
void preorder(char *bt, int idx);
void postorder(char *bt, int idx);


int size = 0;


int main(void) {
    FILE *f = fopen("input.txt", "r");
    if (!f) exit(1);

    int num;
    fscanf(f, "%d\n", &num);
    char *bt = (char*)malloc(sizeof(char) * (++num));

    char data;
    while(!feof(f)) {
        fscanf(f, "%c ", &data);
        bt[++size] = data;
        if (data == 'N') bt = (char*) realloc(bt, sizeof(char) * (++num));
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


void inorder(char *bt, int idx) {
    if (idx <= size && bt[idx] != 'N') {
        inorder(bt, idx * 2);
        printf("%c", bt[idx]);
        inorder(bt, idx * 2 + 1);
    }
}


void preorder(char *bt, int idx) {
    if (idx <= size && bt[idx] != 'N') {
        printf("%c", bt[idx]);
        preorder(bt, idx * 2);
        preorder(bt, idx * 2 + 1);
    }
}

void postorder(char *bt, int idx) {
    if (idx <= size && bt[idx] != 'N') {
        postorder(bt, idx * 2);
        postorder(bt, idx * 2 + 1);
        printf("%c", bt[idx]);
    }
}