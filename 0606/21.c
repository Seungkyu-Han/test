#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0


typedef struct node* nodePointer;
typedef struct node {
    int vertex;
    nodePointer next;
}node;


nodePointer createNode(int v);
void appendNode(int v, int w);
void dfs(int v);
void dfs2(int v);
void connectedComponents (int n);


nodePointer *graph;
int *visited;
int **result;


int main(void)  {
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
            if (data) appendNode(i, j);
        }
    }

    fclose(f);

    dfs(0);
    puts("");

    short int connected = TRUE;

    for (i = 0; i < num; i++) {
        if (!visited[i]) connected = FALSE;
    }

    for (i = 0; i < num; i++) {
        visited[i] = FALSE;
    }


    if (connected) {
        for (i = 0; i < num; i++) {
            for (j = 0; j < num; j++) {
                printf("%d ", result[i][j]);
            }
            puts("");
        }
    } else connectedComponents(num);
}

nodePointer createNode(int v) {
    nodePointer new = (nodePointer)malloc(sizeof(node));
    new->vertex = v;
    new->next = NULL;

    return new;
}

void appendNode(int v, int w) {
    nodePointer new = createNode(w);

    if (graph[v]) new->next = graph[v];
    graph[v] = new;
}

void dfs(int v) {
    visited[v] = TRUE;

    for(nodePointer w = graph[v]; w; w = w->next) {
        if (!visited[w->vertex]) {
            visited[w->vertex] = TRUE;
            printf("(%d, %d), ", v, w->vertex);
            result[v][w->vertex] = TRUE; result[w->vertex][v] = TRUE;
            dfs(w->vertex);
        }
    }
}

void dfs2(int v) {
    visited[v] = TRUE;
    printf("%d, ", v);
    for(nodePointer w = graph[v]; w; w = w->next) {
        if (!visited[w->vertex]) {
            visited[w->vertex] = TRUE;
            dfs2(w->vertex);
        }
    }
}

void connectedComponents (int n) {
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            printf("{");
            dfs2(i);
            printf("}, ");
        }
    }
}