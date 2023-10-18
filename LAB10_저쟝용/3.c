#include <stdio.h>
#include <stdlib.h>

typedef struct node* nodePointer;
typedef struct node {
    int data;
    nodePointer next;
}node;

nodePointer createNode(int item);
void appendNode(int item);
void printData (int data);

nodePointer head, rear;
FILE* f;
int i;

int main(void) {
    f = fopen("input.txt", "r");
    if (f == NULL) exit(1);

    int num;
    fscanf(f, "%d", &num);

    head = createNode(-1);
    rear = head;
    int data;
    
    while(!feof(f)) {
        fscanf(f, "%d", &data);
        appendNode(data);
    }

    fclose(f);

    head = head->next;

    nodePointer temp = head;
    num = 0;

    while(temp) {
        if ((num == 1) || (num == 3) || (num == 7)) {
            puts("");
        }

        data = temp->data;
        printData(data);
        temp = temp->next;
        num++;
    }
}


nodePointer createNode(int item) {
    nodePointer new = (nodePointer)malloc(sizeof(node));
    new->data = item;
    new->next = NULL;

    return new;
}

void appendNode(int item) {
    nodePointer new = createNode(item);
    rear->next = new;
    rear = new;
}

void printData (int data) {
    if (data != -1) {
        printf("%d ", data);
    } else {
        printf("e ");
    }
}