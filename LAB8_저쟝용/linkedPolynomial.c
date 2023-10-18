#include <stdio.h>
#include <stdlib.h>
#define COMPARE(x,y) ((x > y) ? 1 : ((x == y) ? 0 : -1))

typedef struct Node{
    int coeff;
    int exp;
    struct Node* next;
}node;

node* makeheader();
node* createNode(node *header, int coeff, int exp);
void attach(node *polys, int coeff, int exp);
node* makeList (int len, FILE *f);
void add (node *a, node *b, node *c);
void printNode(node *polys, FILE * f);
void cerase(node **header);

node* inverse(node *header);
node* concatenate (node *header1, node*header2);

int main(void) {
    FILE *f = fopen("input.txt", "r");
    if (f == NULL) exit(1);

    int lenA, lenB;
    fscanf(f, "%d %d", &lenA, &lenB);

    node *headerA = makeList(lenA, f);
    node *headerB = makeList(lenB, f);

    fclose(f);

    node *headerC = makeheader();
 
    add(headerA, headerB, headerC);

    f = fopen("output.txt", "w");
    if (f == NULL) exit(1);

    printNode(headerC, f);

    node *inversed = inverse(headerC);

    fprintf(f, "inversed :\n");
    printNode(inversed, f);

    node * concated = concatenate(headerA, headerB);
    fprintf(f, "concate\n");
    printNode(concated, f);
    fclose(f); 

    // cerase(&headerA);
    // cerase(&headerB);
    // cerase(&headerC);
    // cerase(&inversed);
}

node* makeheader() {
    node *header = (node*)malloc(sizeof(node));
    header->exp = -1;
    header->next = header;

    return header;
} 

node* createNode(node *header, int coeff, int exp) {
    node * new = (node*)malloc(sizeof(node));
    new-> coeff = coeff;
    new->exp = exp;
    new->next = header;

    return new;
}

void attach(node *header, int coeff, int exp) {
    node * new = createNode(header, coeff, exp);

    node *temp = header->next;
    while(temp->next->exp != -1) {
        temp = temp->next;
    }

    temp->next = new;
}

node* makeList (int len, FILE *f) {
    node *header = makeheader();

    int coeff, exp, i;

    for (i = 0; i < len; i++) {
        fscanf(f, "%d %d", &coeff, &exp);
        attach(header, coeff, exp);
    }

    return header;
}

void add (node *a, node *b, node *c) {
    a = a->next;
    b = b->next;
    node *temp = c;
    int sum;

    while((a->exp != -1) && (b->exp != -1)) {
        switch(COMPARE(a->exp, b->exp)) {
            case -1:
                attach(c, b->coeff, b->exp);
                b = b->next;
                break;
            case 0:
                sum = a->coeff + b->coeff;
                attach(c, sum, a->exp);
                a = a->next;
                b = b->next;
                break;
            case 1:
                attach(c, a->coeff, a->exp);
                a = a->next;
                break;
        }
        temp = temp->next;
    }
    temp->next = c;

}

void printNode(node *header, FILE * f) {
    node *temp = header;
    temp = temp->next;
    while(temp->exp != -1) {
        fprintf(f, "%d %d\n", temp->coeff, temp->exp);
        temp = temp->next;
    }
}

void cerase(node **header) {
    *header = (*header)->next;
    node *temp;

    while((*header)->exp != -1) {
        temp = *header;
        *header = (*header) ->next;
        free(temp);
    }
    free(*header);
    *header = NULL;
}

node* inverse(node *header) {
    node *middle = makeheader();
    node *newheader = middle;
    node *trail;
    header = header->next;

    while (header->exp != -1) {
        trail = middle;
        middle = header;
        header = header->next;
        middle->next = trail;
    }
    
    newheader->next = middle;
    middle = newheader;

    return middle;
}

node* concatenate (node *header1, node*header2) {
    if (header1->next->exp == -1) return header2;
    if (header2->next->exp == -1) return header1;

    header1 = header1->next;
    node *temp = header2;
    header2 = header2->next;

    for(; header1->next->exp != -1; header1 = header1->next);

    header1->next = header2;
    temp->next = header1;
    header1 = temp;
    
    return header1;
}