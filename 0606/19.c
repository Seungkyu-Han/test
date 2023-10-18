#include <stdio.h>
#include <stdlib.h>


typedef struct {
    int loser;
    int winner;
}node;


int findSize(int n);
void makeBT(int n);
int findNode(int row, int target);
void process(int nodeNum, int row, int col);



int **runs;
node *bt;
int size;
int *idx;


int main(void) {
    FILE *f = fopen("input.txt", "r");
    if (!f) exit(1);

    int total, row;
    fscanf(f, "%d %d\n\n", &total, &row);
    int col = total / row;
    runs = (int**)malloc(sizeof(int*) * row);
    idx = (int*)malloc(sizeof(int) * row);

    size = findSize(row);
    bt = (node*)malloc(sizeof(node) *size);
    size--;

    int i, j;
    for (i = 0; i < row; i++) {
        runs[i] = (int*)malloc(sizeof(int) * col);
        idx[i] = 1;
    }
    
    for (i = 0; i < row; i++) {
        for (j = 0; j < col; j++) {
            fscanf(f, "%d ", &runs[i][j]);
        }
    }

    fclose(f);

    makeBT(row);

    int winner = bt[1].winner;
    int nodeIdx = findNode(row, winner);

    for(i = 0; i < total; i++) {
        printf("%d %d\n", winner, nodeIdx - row);
        process(nodeIdx, row, col);
        winner = bt[1].winner;
        nodeIdx = findNode(row, winner);
    }
}

int findSize(int n)  { 
    int time = 0;
    while(n > 0) {
        n /= 2;
        time++;
    }

    int result = 1;

    for (int i = 0; i < time; i++)
        result *= 2;
    
    return result;
}


void makeBT(int n) {
    int i;
    for (i = n; i <= size; i++) {
        bt[i].loser = runs[i - n][0];
        bt[i].winner = runs[i - n][0];
    }

    for (i = size / 2; i > 0; i--) {
        if (bt[2 * i].winner > bt[2 * i + 1].winner) {
            bt[i].loser = bt[2 * i].winner;
            bt[i].winner = bt[2 * i + 1].winner;
        } else {
            bt[i].winner = bt[2 * i].winner;
            bt[i].loser = bt[2 * i + 1].winner;
        }
    }
    if () bt
}


int findNode(int row, int target) { // 몇 번 째 런인지 찾기
    for (int i = 0; i < row; i++) {
        if (runs[i][idx[i] - 1] == target) return i + row;
    }
    return -1;
}

void process(int nodeNum, int row, int col) {
    if (idx[nodeNum - row] >= col){
        bt[nodeNum].winner = 10000;
        bt[nodeNum].loser = 10000;
    } else {
        bt[nodeNum].winner = runs[nodeNum - row][idx[nodeNum - row]++];
        bt[nodeNum].loser =  bt[nodeNum].winner;
    }
    

    if (nodeNum % 2) nodeNum--; 
    while(nodeNum > 1) {
        if (bt[nodeNum].winner > bt[nodeNum + 1].winner) {
            bt[nodeNum / 2].winner = bt[nodeNum + 1].winner;
            bt[nodeNum / 2].loser = bt[nodeNum].winner;
        } else {
            bt[nodeNum / 2].loser = bt[nodeNum + 1].winner;
            bt[nodeNum / 2].winner = bt[nodeNum].winner;            
        }
        nodeNum /= 2;
    }
}