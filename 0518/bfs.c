#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
#define MAX 100


typedef struct node* nodePointer;
typedef struct node {
    int data;
    nodePointer link;
}node;


nodePointer createNode(int item);
void appendNode(nodePointer *list, nodePointer *rear, nodePointer new);
void enqueue(nodePointer *queue, int *rear, nodePointer item);
nodePointer dequeue(nodePointer *queue, int *front, int *rear);
void bfs( int v);
void connected (int num);


nodePointer * graph;
nodePointer *rear;
int *visited;
int *spanningTree;
int idx = -1;

int main(void) {
    FILE *f = fopen("input.txt", "r");
    if (!f) exit(1);

    int num;
    fscanf(f, "%d", &num);
    graph = (nodePointer*)malloc(sizeof(nodePointer) * num);
    rear = (nodePointer*)malloc(sizeof(nodePointer) * num);
    visited = (int*)malloc(sizeof(int) * num);

    int i,j, data;
    for (i = 0; i < num; i++) {
        visited[i] = FALSE;
        for (j = 0; j < num; j++) {
            fscanf(f, "%d ", &data);
            if (data) {
                appendNode(&graph[i], &rear[i], createNode(j));
            }
        }
    }

    fclose(f);
    
    spanningTree = (int*)malloc(sizeof(int) * num);
    nodePointer *queue = (nodePointer*)malloc(sizeof(nodePointer) * MAX);
    int front = -1, rearQ = -1;
    bfs(0);
    puts("");
    
    int haveSpanningTree = TRUE;

    for (i = 0; i < num; i++) {
        if (!visited[i]) haveSpanningTree = FALSE;
    }

    for (i = 0; i < num; i++) {
        visited[i] = FALSE;
    }

    if (haveSpanningTree) {
        for (i = 0; i < num; i++) {
            printf("%d ", spanningTree[i]);
        }
    } else {
        connected(num);
    }
}


nodePointer createNode(int item) {
    nodePointer new = (nodePointer)malloc(sizeof(nodePointer));
    new->data = item;
    new->link = NULL;

    return new;
}

void appendNode(nodePointer *list, nodePointer *rear, nodePointer new) {
    if (*list) {
        (*rear)->link = new;
        *rear = new;
    } else {
        (*list) = new;
        *rear = new;
    }
}


void enqueue(nodePointer *queue, int *rear, nodePointer item) {
    if (*rear >= MAX -1) {
        printf("the queue is full\n");
        exit(1);
    }
    queue[++(*rear)] = item;
}


nodePointer dequeue(nodePointer *queue, int *front, int *rear) {
    if (*front == *rear) {
        printf("the queue is empty\n");
        exit(1);
    }
    return queue[++(*front)];
}


void bfs( int v) {
    nodePointer *queue = (nodePointer*)malloc(sizeof(nodePointer) * MAX);
    int front = -1, rear = -1;

    enqueue(queue, &rear, createNode(v));
    visited[v] = TRUE;
    spanningTree[++idx] = v;

    nodePointer temp = NULL;
    while(front != rear) {
        temp = graph[dequeue(queue, &front, &rear)->data];
        for (; temp; temp = temp->link) {
            if (!visited[temp->data]) {
                printf("(%d, %d), ", v, temp->data);
                spanningTree[++idx] = temp->data;
                visited[temp->data] = TRUE;
            }
        }
    }
}


void connected (int num) {
    int i;
    nodePointer *queue;
    int front, rear;

    for (i = 0; i < num; i++) {
        printf("{");
        if (!visited[i]) {
            bfs(i);
        }
        printf("}, ");
    }
    puts("");
}