#include <stdio.h>
#include <stdlib.h>
#define MAX 100

typedef struct Node {
    int data;
    struct Node* next;
}node;


node* createNode(int data);
void appedNode (node *head, node *inserted);
void printList(node *head);
void push(node* item);
node* pop();

node* stack[MAX];
int top = -1;

int main() {
    FILE *f1 = fopen("input.txt", "r");
    if (f1 == NULL) exit(1);

    int num;
    fscanf(f1, "%d", &num);
    
    node *head = createNode(num);
    push(head);
    
    node *new;

    while (!feof(f1)) {
        fscanf(f1, "%d", &num);
        new = createNode(num);
        appedNode(head, new);
        push(new);
    }
    fclose(f1);

    FILE *f2 = fopen("output.txt", "w");
    if (f2 == NULL) exit(1);

    node *out;
    while(top >= 0) {
        out = pop();
        fprintf(f2, "%d ", out->data);
    }

    fclose(f2);

    printList(head);
}

node* createNode(int item) {
    node* new = (node*) malloc(sizeof(node));
    new->data = item;
    new-> next = NULL;

    return new;
}


void appedNode (node *head, node *inserted) {
    node *trail = head;

    while(trail->next != NULL)
        trail = trail->next;
    
    trail->next = inserted;
}

void printList(node *head) {
    node *trail = head;
    while (trail != NULL) {
        printf("%d ", trail->data);
        trail = trail->next;
    }
    printf("\n");
}


void push(node* item) {
    if (top >= MAX - 1) {
        printf("it is full\n");
        exit(1);
    } 
    stack[++top] = item;
}

node* pop() {
    if (top < 0) {
        printf("it is empty\n");
        exit(1);
    } else {
        return stack[top--];
    }
}