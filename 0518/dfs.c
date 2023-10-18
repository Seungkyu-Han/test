#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0


typedef struct node* nodePointer;
typedef struct node {
    int data;
    nodePointer link;
}node;


nodePointer createNode(int item);
void appendNode(nodePointer *list, nodePointer *rear, nodePointer new);
void dfs(int v);
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
    dfs(0);
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


void dfs(int v) {
    visited[v] = TRUE;

    if (graph[v]) {
        spanningTree[++idx] = v;
        
        for(nodePointer temp = graph[v]; temp; temp = temp->link) {
            if (!visited[temp->data]) {
                printf("(%d, %d), ", v, temp->data);
                dfs(temp->data);
            }
        }
    }
}


void connected (int num) {
    int i;
    for (i = 0; i < num; i++) {
        printf("{");
        if (!visited[i]) {
            dfs(i);
        }
        printf("}, ");
    }
    puts("");
}