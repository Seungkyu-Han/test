#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
#define MAX_NUM 24

typedef struct Node{
    int data;
    struct Node * next;
} node;

node* createNode(int item);
void appendNode (int item, int element);
void appendNode2(int data);
void push(node *new, node **stack);
void categorize();

FILE *f1, *f2;

node **seq;
node *classes[MAX_NUM];

int *out;
int cnt = 0;

int i, j;

int main(void) {
    f1 = fopen("input.txt", "r");
    if (f1 == NULL) exit(1);

    int pairs;
    fscanf(f1, "%d", &pairs);
    
    seq = (node**)malloc(sizeof(node*) * MAX_NUM);
    out = (int*)malloc(sizeof(int) * MAX_NUM);

    for (i = 0; i < MAX_NUM; i++) seq[i] = NULL;

    int first, second;

    for (i = 0; i < pairs; i++) {
        fscanf(f1, "%d = %d", &first, &second);

        out[first] = TRUE;
        out[second] = TRUE;

        appendNode(second, first);
        appendNode(first, second);
    }

    fclose(f1);

    categorize();

    f2 = fopen("output.txt", "w");
    if (f2 == NULL) exit(1);

    fprintf(f2, "%d\n", cnt);

    node *delete;

    for (i = 0; i < cnt; i++) {
        fprintf(f2, "{");
        while(classes[i] != NULL) {
            if (classes[i]->next == NULL) fprintf(f2, "%d}", classes[i]->data);
            else fprintf(f2, "%d, ", classes[i]->data);

            delete = classes[i];
            classes[i] = classes[i]->next;
            free(delete);
        }
        if (i < cnt - 1) fprintf(f2, ", ");
    }
}

node* createNode(int item) {
    node* new = (node*) malloc(sizeof(node));
    new->data = item;
    new-> next = NULL;

    return new;
}

void appendNode (int item, int element) {
        node *temp = createNode(item);
        temp->next = seq[element];
        seq[element] = temp;    
}

void appendNode2(int data) {
    node *new = createNode(data);
    
    node *temp = classes[cnt];
    while(temp->next != NULL) temp = temp->next;

    temp->next = new;
}

void push(node *new, node **stack) {
    node *memory;
    memory = new;
    new->next = *stack;
    *stack = new;
    new = memory;
}

void categorize() {
    node *temp, *stack;
    int data;

    for (i = 0; i < MAX_NUM; i++) {
        if (out[i]) {
            classes[cnt] = createNode(i);
            out[i] = FALSE;
            temp = seq[i];
            stack = NULL;

            while(1) {
                while(temp) {
                    data = temp->data;

                    if (out[data]) {
                        appendNode2(data);
                        out[data] = FALSE;
                        push(temp, &stack);
                    }
                    temp = temp->next;
                }
                if (stack == NULL) break;

                temp = seq[stack->data];
                stack = stack->next;
            }
            cnt += 1;
        }
    }

}