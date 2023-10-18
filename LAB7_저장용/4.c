#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
}node;

typedef struct Stack {
    node* top;
} Stack;

node* createNode(int data);
void appedNode (node *head, node *inserted);
void printList(node *head);
void push(Stack* stack, int data);
int pop(Stack* stack);


int main() {
    Stack stack = {NULL};

    FILE *f1 = fopen("input.txt", "r");
    if (f1 == NULL) exit(1);

    int num;
    fscanf(f1, "%d", &num);
    node *head = createNode(num);
    push(&stack, head->data);
    
    node *new;
    int cnt = 0;

    while (!feof(f1)) {
        fscanf(f1, "%d", &num);
        appedNode(head, createNode(num));
        push(&stack, num);
        cnt++;
    }
    fclose(f1);

    FILE *f2 = fopen("output.txt", "w");
    if (f2 == NULL) exit(1);

    for (int i = 0; i <= cnt; i++) {
        fprintf(f2, "%d ", pop(&stack));
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



void push(Stack* stack, int data) {
    node* newNode = (node*) malloc(sizeof(node));
    newNode->data = data;
    newNode->next = stack->top;
    stack->top = newNode;
}

int pop(Stack* stack) {
    if (stack->top == NULL) {
        printf("Error: Stack is empty!\n");
        exit(1);
    }
    node* temp = stack->top;
    int data = temp->data;
    stack->top = temp->next;
    free(temp);
    return data;
}
