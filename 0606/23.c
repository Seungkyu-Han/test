#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0


typedef struct node* nodePointer;
typedef struct node {
    int v, w;
    int cost;
    nodePointer next;
}node;


void appendNode(int v, int w, int cost);
void push(nodePointer item);
nodePointer pop();
int collapsingFind(int i);
void weightedUnion(int i, int j);
nodePointer* kruskal(int num);


nodePointer *graph;
nodePointer heap[100];
int size = 0;
int *parent;
int **result;


int main(void) {
    FILE *f = fopen("input.txt", "r");
    if (!f) exit(1);

    int num;
    fscanf(f, "%d\n", &num);
    graph = (nodePointer*)malloc(sizeof(nodePointer) * num);
    parent = (int*)malloc(sizeof(int) * num);
    result = (int**)malloc(sizeof(int*) * num);

    int i, j, data;
    for (i = 0; i < num; i++) {
        parent[i] = -1;
        result[i] = (int*)malloc(sizeof(int) * num);
        for (j = 0; j < num; j++) {
            fscanf(f, "%d ", &data);
            if (data) {
                appendNode(i, j, data);
            }
        }
    }

    fclose(f);

    nodePointer *mcst = kruskal(num);
    puts("");

    int totalCost = 0;
    for (i = 0; i < num - 1; i++) {
        totalCost += mcst[i]->cost;
    }

    printf("%d\n", totalCost);
    
    for (i = 0; i < num; i++) {
        for (j = 0; j < num; j++) {
            printf("%d ", result[i][j]);
        }
        puts("");
    }
}


void appendNode(int v, int w, int cost) {
    nodePointer new = (nodePointer)malloc(sizeof(node));
    new->v = v;
    new->w = w;
    new->cost = cost;
    new->next = NULL;
    if (graph[v]) new->next = graph[v];
    graph[v] = new;
}


void push(nodePointer item) {
    int idx = ++size;

    while(idx != 1 && item->cost < heap[idx / 2]->cost) {
        heap[idx] = heap[idx / 2];
        idx /= 2;
    }
    heap[idx] = item;
}


nodePointer pop() {
    nodePointer item = heap[1];
    nodePointer temp = heap[size--];
    int parent = 1;
    int child = 2;

    while(child <= size) {
        if (child < size && heap[child]->cost > heap[child + 1]->cost) child++;
        if (temp->cost <= heap[child]->cost) break;

        heap[parent] = heap[child];
        parent = child;
        child *= 2;
    }

    heap[parent] = temp;
    return item;
}


int collapsingFind(int i) {
    int root = i, trail = i, lead;
    for (; parent[root] >= 0; root = parent[root]);
    for (; trail != root; trail = lead) {
        lead = parent[trail];
        parent[trail] = root;
    }

    return root;
}


void weightedUnion(int i, int j) {
    if (parent[i] >= 0) i = collapsingFind(i);
    if (parent[j] >= 0) j = collapsingFind(j);

    int temp = parent[i] + parent[j];

    if (parent[i] > parent[j]) {
        parent[i] = j;
        parent[j] = temp;
    } else {
        parent[j] = i;
        parent[i] = temp;
    }
}


nodePointer* kruskal(int num) {
    int i;
    nodePointer w;
    for (i = 0; i < num; i++) {
        for (w = graph[i]; w; w = w->next) {
            if (w->v <= w->w) {
                push(w);
            }
        }
    }

    nodePointer *mcst = (nodePointer*)malloc(sizeof(nodePointer) * (num - 1));
    int top = -1;

    while(top < num - 2) {
        w = pop();
        if (!w) break;

        if (collapsingFind(w->v) != collapsingFind(w->w)) {
            weightedUnion(w->v, w->w);
            printf("(%d, %d), ", w->v, w->w);
            result[w->v][w->w] = w->cost; result[w->w][w->v] = w->cost;
            mcst[++top] = w;
        }
    }

    return mcst;
}