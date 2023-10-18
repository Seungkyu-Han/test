#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0


typedef struct edge* edgePointer;
typedef struct edge {
    int v, w;
    int cost;
    edgePointer next;
}edge;



void appendEdge(int v, int w, int cost);
void push(edgePointer *heap, int *size, edgePointer item);
edgePointer pop(edgePointer *heap, int *size);
int prim(int num);


edgePointer *graph;
int *visited;
int **result;
edgePointer route[100];
int top = -1;


int main(void) {
    FILE *f = fopen("input.txt", "r");
    if (!f) exit(1);

    int num;
    fscanf(f, "%d\n", &num);
    graph = (edgePointer*)malloc(sizeof(edgePointer) * num);
    visited = (int*)malloc(sizeof(int) * num);
    result = (int**)malloc(sizeof(int*) * num);

    int i, j, data;
    for (i = 0; i < num; i++) {
        result[i] = (int*)malloc(sizeof(int) * num);
        visited[i] = FALSE;
        for (j = 0; j < num; j++) {
            fscanf(f, "%d ", &data);
            if (data) appendEdge(i, j, data);
        }
    }

    fclose(f);

    int hasSPT = prim(num);
    puts("");

    if (hasSPT) {
        for (i = 0; i < num; i++) {
            for (j = 0; j < num; j++) {
                printf("%d ", result[i][j]);
            }
            puts("");
        }
    }
}


void appendEdge(int v, int w, int cost) {
    edgePointer new = (edgePointer)malloc(sizeof(edge));
    new->cost = cost;
    new->v = v;
    new->w = w;
    new->next = NULL;

    if (graph[v]) new->next = graph[v];
    graph[v] = new;
}


void push(edgePointer *heap, int *size, edgePointer item) {
    int idx = ++(*size);

    while(idx != 1 && item->cost < heap[idx / 2]->cost) {
        heap[idx] = heap[idx / 2];
        idx /= 2;
    }

    heap[idx] = item;
}


edgePointer pop(edgePointer *heap, int *size) {
    edgePointer item = heap[1];
    edgePointer temp = heap[(*size)--];
    int parent = 1, child = 2;

    while(child <= *size) {
        if (child < *size && heap[child]->cost > heap[child + 1]->cost) child++;
        if (heap[child] >= temp) break;

        heap[parent] = heap[child];
        parent = child;
        child *= 2; 
    }

    heap[parent] = temp;
    return item;
}


int prim(int num) {
    edgePointer heap[100];
    int size = 0;
    int i, v, w; edgePointer temp;

    visited[0] = TRUE;
    while (top < num - 2) {
        for (i = 0; i < num; i++) {
            for (temp = graph[i]; temp; temp = temp->next) {
                v = temp->v; w = temp->w;
                if (v <= w && ((visited[v] && !visited[w]) || (visited[w] && !visited[v]))) {
                    push(heap, &size, temp);
                }
            }
        }
            temp =  pop(heap, &size);
            if (!temp) break;

            printf("(%d, %d), ", temp->v, temp->w);
            visited[temp->w] = TRUE; visited[temp->w] = TRUE;
            result[temp->v][temp->w] = temp->cost; result[temp->w][temp->v] = temp->cost;
            route[++top] = temp;
     }

     if (top < num - 2) {
        printf("No Spanning Tree");
        return FALSE;
     } else return TRUE;

}