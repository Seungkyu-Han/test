#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    int data;
    struct Node* next;
}node;

node* createNode(int data);
void appendNode (node *head, node *inserted);
void printList(node *head);

FILE *f2;

int main() {
    FILE *f1 = fopen("input.txt", "r");
    if (f1 == NULL) exit(1);

    char str1[101], str2[101];

    fgets(str1, 100, f1);
    fgets(str2, 100, f1);

    char* token = strtok(str1, " ");
    int num = atoi(token);

    node* head1 = createNode(num);
    token = strtok(NULL, " ");

    while (token != NULL) {
        num = atoi(token);
        appendNode(head1, createNode(num));
        token = strtok(NULL, " ");
    }

    token = strtok(str2, " ");
    num = atoi(token);

    node* head2 = createNode(num);
    token = strtok(NULL, " ");

    while (token != NULL) {
        num = atoi(token);
        appendNode(head2, createNode(num));
        token = strtok(NULL, " ");
    }

    fclose(f1);


    f2 = fopen("output.txt", "w");
    if (f2 == NULL) exit(1);

    printList(head1);
    printList(head2);

    fclose(f2);
}

node* createNode(int item) {
    node* new = (node*) malloc(sizeof(node));
    new->data = item;
    new-> next = NULL;

    return new;
}


void appendNode (node *head, node *inserted) {
    node *trail = head;

    while(trail->next != NULL)
        trail = trail->next;
    
    trail->next = inserted;
}



void printList(node *head) {
    node *trail = head;
    while (trail != NULL) {
        fprintf(f2, "%d ", trail->data);
        trail = trail->next;
    }
}
