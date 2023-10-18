#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TRUE 1
#define FALSE 0
#define SIZE 13


typedef struct node* nodePointer;
typedef struct node{
    char data[100];
    int key;
    nodePointer next;
} node;


nodePointer createNode(char *item);
int hash(int key);
void insert(char *input);
nodePointer search(char *item);
int stringToInt(char *item);

nodePointer ht[SIZE];


int main(void) {
    FILE *f = fopen("input.txt", "r");
    if (!f) exit(1);

    int num;
    fscanf(f, "%d\n\n", &num);

    int i; char input[100];
    for (i = 0; i < num; i++) {
        fscanf(f, "%s ", input);
        insert(input);
    }

    fclose(f);

    nodePointer temp;
    while(1) {
        printf("검색할 키워드를 입력하시오...\n");
        scanf("%s", input);
        if (!strcmp("quit", input)) break;

        temp = search(input);
        if (!temp) printf("> 키워드가 존재하지 않습니다.\n");
        else printf("> 버킷 주소 %d에 저장된 키워드입니다.\n", temp->key);
    }
}



int hash(int key) {
    return key % SIZE;
} 


int stringToInt(char *item) {
    int sum = 0;
    while(*item) sum += *item++;

    return sum;
}

nodePointer createNode(char *item) {
    nodePointer new = (nodePointer)malloc(sizeof(node));
    strcpy(new->data, item);
    new->key = hash(stringToInt(item));
    new->next = NULL;

    return new;
}


void insert(char *input) {
    nodePointer new = createNode(input);

    if (ht[new->key]) new->next = ht[new->key];
    ht[new->key] = new;
}


nodePointer search(char *item) {
    int homeBucket = hash(stringToInt(item));
    for (nodePointer temp = ht[homeBucket]; temp; temp = temp->next) {
        if (!strcmp(temp->data, item)) return temp;
    }
    return NULL;
}