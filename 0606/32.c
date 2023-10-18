#include <stdio.h>
#include <stdlib.h>


typedef struct {
    int w;
    int c;
    int r;
} node;


void getWeight(int diff, int start);
void getRoot(int diff, int start);
void getCost(int diff, int start);
void makeBT(int n);
void printBT(int diff, int start, int idx);


int a[100], p[100], q[100];
node **matrix;


int main(void) {
    FILE *f = fopen("input.txt", "r");
    if (!f) exit(1);

    int n, m;
    fscanf(f, "%d %d\n", &n, &m);
    matrix = (node**)malloc(sizeof(node*) * (n + 1));

    int i;
    for (i = 1; i <= n; i++)
        fscanf(f, "%d ", &a[i]);
    
    for (i = 1; i <= n; i++)
        fscanf(f, "%d ", &p[i]);

    for (i = 0; i <= n; i++) 
        fscanf(f, "%d ", &q[i]);


    fclose(f);

    for (i = 0; i <= n; i++) {
        matrix[i] = (node*)malloc(sizeof(node) * (n + 1));
        matrix[0][i].r = 0; matrix[0][i].c = 0; matrix[0][i].w = q[i];
    }

    makeBT(n);

    printBT(n, 0, 1);
}


void getWeight(int diff, int start) {
    matrix[diff][start].w = matrix[diff - 1][start].w + q[start + diff] + p[start + diff];
}


void getRoot(int diff, int start) {
    int root = start + 1;
    int min = root;

    for (root = start + 2; root <= start + diff; root++) {
        if ( matrix[min - start - 1][start].c + matrix[start + diff - min][min].c > (matrix[root - start - 1][start].c + matrix[start + diff - root][root].c)) min = root;
    }

    matrix[diff][start].r = min;
}


void getCost(int diff, int start) {
    getRoot(diff, start);
    int root = matrix[diff][start].r;
    matrix[diff][start].c = matrix[diff][start].w + matrix[root - 1 - start][start].c + matrix[start + diff - root][root].c;
}


void makeBT(int n) {
    int diff, start;
    for (diff = 1; diff <= n; diff++) {
        for (start = 0; start <= n - diff; start++) {
            getWeight(diff, start);
            getCost(diff, start);
        }
    }
}

void printBT(int diff, int start, int idx) {
    if (diff > 0) {
        int root = matrix[diff][start].r;
        printf("Complete BT의 %d번 노드 자리에 원소 %d가 위치합니다.\n", idx, a[root]);
        printBT(root- 1 - start, start, idx * 2);
        printBT(diff + start - root, root, idx * 2 + 1);
    }
}   