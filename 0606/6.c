#include <stdio.h>
#include <stdlib.h>


typedef struct node* nodePointer;
typedef struct node {
    char data;
    nodePointer left, right;
}node;


nodePointer createNode(char item);
nodePointer copy(char *bt, int idx);
void inorder(nodePointer bt);
void preorder(nodePointer bt);
void postorder(nodePointer bt);


int size = 0;


int main(void) {
    FILE *f = fopen("input.txt", "r");
    if (!f) exit(1);

    int num;
    fscanf(f, "%d\n", &num);
    char *bt1 = (char*)malloc(sizeof(char) * (++num));

    char data;
    while(!feof(f)) {
        fscanf(f, "%c ", &data);
        bt1[++size] = data;
        if (data == 'N') bt1 = (char*)realloc(bt1, sizeof(char) * (++num));
    }

    fclose(f);

    nodePointer bt2 = copy(bt1, 1);

    printf("inorder traversal: ");
    inorder(bt2);
    puts("");

    printf("preorder traversal: ");
    preorder(bt2);
    puts("");

    printf("postorder traversal: ");
    postorder(bt2);
    puts("");      
}


nodePointer createNode(char item) {
    nodePointer new = (nodePointer)malloc(sizeof(node));
    new->data = item;
    new->left = NULL;
    new->right = NULL;

    return new;
}


nodePointer copy(char *bt, int idx) {
    nodePointer new = NULL;

    if (idx <= size && bt[idx] != 'N') {
        new = createNode(bt[idx]);
        new->left = copy(bt, idx * 2);
        new->right = copy(bt, idx * 2 + 1);
    }

    return new;
}

void inorder(nodePointer bt) {
    if (bt) {
        inorder(bt->left);
        printf("%c", bt->data);
        inorder(bt->right);
    }
}

void preorder(nodePointer bt) {
    if (bt) {
        printf("%c", bt->data);
        preorder(bt->left);
        preorder(bt->right);
    }
}

void postorder(nodePointer bt) {
    if (bt) {
        postorder(bt->left);
        postorder(bt->right);
        printf("%c", bt->data);
    }
}