#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
}node;

node* createNode(int data);
node *find (node *head, int cnt);
void insertFirst(node **head, node *inserted);
void insert(node* target, node* inserted);
void appedNode (node *head, node *inserted);
void deleteNode (node *head, node *target);
void printList(node *head);


int main() {
    FILE *f1 = fopen("input.txt", "r");
    if (f1 == NULL) exit(1);

    int num;
    fscanf(f1, "%d", &num);
    node *head = createNode(num);

    while (!feof(f1)) {
        fscanf(f1, "%d", &num);
        appedNode(head, createNode(num));
    }

    fclose(f1);

    printf("+----------------+\n");
    printf("1. insert\n");
    printf("2. delete\n");
    printf("3. length \n");
    printf("4. exit\n");
    printf("+----------------+\n\n");

    int input = 1;

    while(input != 4) {
        printf("Menu: ");
        scanf("%d", &input);

        switch(input) {
            node *target;
            int cnt, counter;

            case 1:
                printf("insert: ");

                int data;
                scanf("%d %d", &cnt, &data);
                target = find(head, cnt - 1);

                insert(target, createNode(data));

                printf("result: ");
                printList(head);
                break;
            case 2:
                printf("delete: ");
                scanf("%d", &cnt);

                target = find(head, cnt - 1);
                deleteNode(head, target);

                printf("result: ");
                printList(head);
                break;
            case 3:
                counter = 1;
                target = head;
                while(target->next != NULL) {
                    target = target->next;
                    counter += 1;
                }

                printf("length: %d\n", counter);
                break;
            case 4:
                printf("exit");
        }

        puts("");
    } 
}

node* createNode(int item) {
    node* new = (node*) malloc(sizeof(node));
    new->data = item;
    new-> next = NULL;

    return new;
}

node *find (node *head, int cnt) {
    node * trail = head;

    for (int i = 0; i < cnt; i++) {
        trail = trail->next;
    }

    return trail;
}

void insert(node* target, node* inserted) {
    inserted->next = target->next;
    target->next = inserted;
}

void insertFirst(node **head, node *inserted) {
    if (*head != NULL) 
        inserted->next = *head;

    *head = inserted;
}

void appedNode (node *head, node *inserted) {
    node *trail = head;

    while(trail->next != NULL)
        trail = trail->next;
    
    trail->next = inserted;
}

void deleteNode (node *head, node *target) {
    node *trail = head;
    int check = 0;

    while (trail != NULL) {
        if (trail->next == target) {
            check = 1;
            break;
        }
        trail = trail->next;
    }

    if (check) {
        trail->next = target->next;
        free(target);
    } else {
        printf("it is not exist\n");
    }
}

void printList(node *head) {
    node *trail = head;
    while (trail != NULL) {
        printf("%d ", trail->data);
        trail = trail->next;
    }
    printf("\n");
}
