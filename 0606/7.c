#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 100

typedef struct node* nodePointer;
typedef struct node {
    char data;
    nodePointer left, right;
}node;


nodePointer copy(char *bt, int idx);
void push(nodePointer *stack, int *top, nodePointer item);
nodePointer pop(nodePointer *stack, int *top);
void inorder(nodePointer bt);


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

    printf("iterative implementation of inorder traversal : ");
    inorder(bt2);
    puts("");    
}


nodePointer copy(char *bt, int idx) {
    nodePointer new = NULL;

    if (idx <= size && bt[idx] != 'N') {
        new = (nodePointer)malloc(sizeof(node));
        new->left = copy(bt, idx * 2);
        new->right = copy(bt, idx * 2 + 1);
        new->data = bt[idx];
    }

    return new;
}


void push(nodePointer *stack, int *top, nodePointer item) {
    if (*top >= MAX_SIZE - 1) {
        printf("hahahaha it's full\n");
        exit(1);
    }
    stack[++(*top)] = item;
}


nodePointer pop(nodePointer *stack, int *top) {
    if (*top < 0) {
        return NULL;
    }
    return stack[(*top)--];
}

void inorder(nodePointer bt) {
    nodePointer stack[MAX_SIZE];
    int top = -1;

    nodePointer temp = bt;
    if (bt) {
        while(1) {
            for (; temp; temp = temp->left)
                push(stack, &top, temp);
        
            temp = pop(stack, &top);
            if (!temp) break;

            printf("%c", temp->data);
            temp = temp->right;
        }
    }
}
