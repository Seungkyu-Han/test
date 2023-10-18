#include <stdio.h>
#include <stdlib.h>

typedef struct tree* treePointer;
typedef struct tree{
    int data;
    treePointer left; treePointer right;
}tree;


void push(treePointer *stack, int *top, treePointer item);
treePointer pop(treePointer *stack, int *top);
void inorder(treePointer bt, int avail);
void postorder(treePointer bt);
void enqueue(treePointer *queue, int *rear, treePointer item);
treePointer dequeue(treePointer *queue, int *front, int *rear);
void levelorder(treePointer bt, int avail);
treePointer createNode(char item);
treePointer copy(char* original, int idx);
int equal (treePointer bt1, treePointer bt2);

char arr[21];
treePointer bt;


int main(void) {
    for (int i = 0; i < 21; i++)
        arr[i] = 'N';

    FILE *f = fopen("input.txt", "r");
    if (f == NULL) exit(1);

    int avail;
    fscanf(f, "%d\n", &avail);

    int idx = 1;
    char data;
    while(!feof(f)) {
        fscanf(f, "%c ", &data);
        if(data != 'N') arr[idx] = data;
        idx++;
    }

    fclose(f);

    treePointer bt1 = copy(arr, 1);



    treePointer bt2 = copy(arr, 1);

    if (equal(bt1, bt2)) printf("equal\n");
    else printf("not equal\n");


}




void push(treePointer *stack, int *top, treePointer item) {
    stack[++(*top)] = item;
}


treePointer pop(treePointer *stack, int *top) {
    if (*top == -1) {
        return NULL;
        printf("it is emoty\n");
    }
    else return (stack[(*top)--]);
}


void inorder(treePointer bt, int avail) {
    treePointer stack[100], temp = bt;
    int top = -1;

    while(1) {
        for (; temp; temp = temp->left)
            push(stack, &top, temp);
        temp = pop(stack, &top);
        if (temp) {
            printf("%c ", temp->data);
            temp = temp->right;
        } else break;
    }
}

void enqueue(treePointer *queue, int *rear, treePointer item) {
    if (*rear >= 99) return;
    queue[++(*rear)] = item;
}

treePointer dequeue(treePointer *queue, int *front, int *rear) {
    if (*front == *rear) return NULL;
    return queue[++(*front)];
}

void levelorder(treePointer bt, int avail) {
    treePointer queue[100];
    int rear = -1, front = -1;

    enqueue(queue, &rear, bt);

    while(bt) {
        bt = dequeue(queue, &front, &rear);
        if (bt) {
            printf("%c ", bt->data);
            if (bt->left) enqueue(queue, &rear, bt->left);
            if (bt->right) enqueue(queue, &rear, bt->right);
        } 
    }
}

void postorder(treePointer bt) {
    treePointer stack[100], temp = bt;
    int top = -1;

    printf("%c ", temp->data);
}   

treePointer createNode(char item) {
    treePointer new = (treePointer)malloc(sizeof(tree));
    new->data = item;
    new->left = NULL;
    new->right = NULL;

    return new;
}

treePointer copy(char* original, int idx) {
    if (idx <= 20 && original[idx] != 'N') {
        treePointer new = createNode(original[idx]);
        new->left = copy(original, idx * 2);
        new->right = copy(original, idx * 2 + 1);
        return new;
    } else return NULL;

}

int equal (treePointer bt1, treePointer bt2) {
    return ((!bt1 && !bt2) || (bt1 && bt2 && (bt1->data == bt2->data) && equal(bt1->left, bt2->left) && equal(bt1->right, bt2->right)));
}