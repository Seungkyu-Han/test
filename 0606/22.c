#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0


typedef struct node* nodePointer;
typedef struct node {
    int v, w;
    nodePointer next;
}node;


void appendNode(int v, int w);
void add(int *queue, int *rear, int v);
int delete(int *queue, int *front, int rear);
void bfs(int v);
void bfs2(int v);
void connectedComponents(int num);


nodePointer *graph;
int *visited;
int **result;


int main(void) {
    FILE *f = fopen("input.txt", "r");
    if (!f) exit(1);

    int num;
    fscanf(f, "%d\n", &num);
    graph = (nodePointer*)malloc(sizeof(nodePointer) * num);
    visited = (int*)malloc(sizeof(int) * num);
    result = (int**)malloc(sizeof(int*) * num);

    int i, j, data;
    for (i = 0; i < num; i++) {
        visited[i] = FALSE;
        result[i] = (int*)malloc(sizeof(int) * num);
        for (j = 0; j < num; j++) {
            fscanf(f, "%d ", &data);
            if (data) {
                appendNode(i, j);
            }
        }
    }

    fclose(f);

    bfs(0);
    puts("");

    int connected = TRUE;

    for (i = 0; i < num; i++) {
        if (!visited[i]) {
            connected = FALSE;
            break;
        }
    }

    for (i = 0; i < num; i++)
        visited[i] = FALSE;
    
    if (connected) {
        for (i = 0; i < num; i++) {
            for (j = 0; j < num; j++) {
                printf("%d ", result[i][j]);
            }
            puts("");
        }
    } else connectedComponents(num);
}


void appendNode(int v, int w) {
    nodePointer new = (nodePointer)malloc(sizeof(node));
    new->v = v;
    new->w = w;
    new->next = NULL;
    if (graph[v]) new->next = graph[v];
    graph[v] = new;
}


void add(int *queue, int *rear, int v) {
    queue[++(*rear)] = v;
}


int delete(int *queue, int *front, int rear) {
    if (rear == *front) return -1;
    return queue[++(*front)];
}

void bfs(int v) {
    int queue[100];
    int rear = -1, front = -1;

    visited[v] = TRUE;
    add(queue, &rear, v);
    while(front < rear) {
        int temp = delete(queue, &front, rear);
        for (nodePointer w = graph[temp]; w; w = w->next) {
            if (!visited[w->w]) {
                visited[w->w] = TRUE;
                result[w->v][w->w] = 1; result[w->w][w->v] = 1;
                printf("(%d, %d), ", w->v, w->w);
                add(queue, &rear, w->w);
            }
        }
    }
}


void bfs2(int v) {
    int queue[100];
    int rear = -1, front = -1;

    visited[v] = TRUE;
    printf("{%d, ", v);

    add(queue, &rear, v);
    while(front < rear) {
        int temp = delete(queue, &front, rear);
        for (nodePointer w = graph[temp]; w; w = w->next) {
            if (!visited[w->w]) {
                visited[w->w] = TRUE;
                printf("%d, ", w->w);
                add(queue, &rear, w->w);
            }
        }
    }
    printf("}, ");
}


void connectedComponents(int num) {
    for (int i = 0; i < num; i++) {
        if (!visited[i]) bfs2(i);
    }
}