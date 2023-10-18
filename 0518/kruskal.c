#include <stdio.h>
#include <stdlib.h>
#define SWAP(x,y,temp) ((temp = *x), (*x = *y), (*y = temp))

typedef struct{
    int u; int v;
    int cost;
}edge;


void adjsut (int root, int size);
void heapSort();
int hasCycle(edge* arr, int addedEdge, edge new);
edge* kruskal();


edge* edges;
int size = 0, num;

int main(void) {
    FILE *f = fopen("input.txt", "r");
    if (!f) exit(1);

    fscanf(f, "%d\n", &num);
    edges = (edge*)malloc(sizeof(edge) * (num * num + 1));
    
    int i, j, data;
    for (i = 0; i < num; i++) {
        for (j = 0; j < num; j++) {
            fscanf(f, "%d ", &data);
            if (data) {
                edges[++size].u = i; edges[size].v = j;
                edges[size].cost = data;
            }
        }
    }

    fclose(f);

    heapSort();

    edge *result = kruskal();

    if (result) {
        for (i = 0; i < num - 1; i++)
            printf("(%d, %d) ", result[i].u, result[i].v);
    }
}


void adjsut (int root, int size) {
    int parent = root;
    int child = root * 2;
    edge temp = edges[root];

    while(child <= size) {
        if ((child < size) && (edges[child].cost < edges[child + 1].cost))
            child++;
        if (edges[child].cost < temp.cost) break;
        else {
            edges[parent] = edges[child];
            parent = child;
            child *= 2;
        }
    }
    edges[parent] = temp;
}


void heapSort() {
    int i;
    for (i = size / 2; i >= 1; i--)
        adjsut(i, size);
    
    edge temp;
    for (i = size - 1; i > 0; i--) {
        SWAP(&edges[1], &edges[i + 1], temp);
        adjsut(1, i);
    }
}


int hasCycle(edge* arr, int addedEdge, edge new) {
}

edge* kruskal() {
    edge *minST = (edge*)malloc(sizeof(edge) * (num - 1));
    int addedEdge = 0, front = 1;
    
    while(front <= size && addedEdge < (num - 1)) {
        if (!hasCycle(minST, addedEdge, edges[front])) minST[addedEdge++] = edges[front];
        front++;
    }

    if (addedEdge < num - 1) {
        printf("it doesn't have a spanning tree\n");
        return NULL;
    }

    return minST;
}



