#include <stdio.h>
#include <stdlib.h>


typedef struct {
    int weight;
    int cost;
    int root;
} node;


void print_tree(int i, int j, int pos, FILE* f);


int *nodes, *p, num;
node **arr;


int main(void) {
    FILE *f = fopen("input.txt", "r");
    if (!f) exit(1);

    int totalcost;
    fscanf(f, "%d %d\n", &num, &totalcost);
    nodes = (int*)malloc(sizeof(int) * (num + 1));
    p =  (int*)malloc(sizeof(int) * (num + 1));

    arr = (node**)malloc(sizeof(node*) * (num + 1));

    int i, j;
    for (i = 0; i < num + 1; i++)
        arr[i] = (node*)malloc(sizeof(node) * (num + 1));

    for (i = 1; i <= num; i++)
        fscanf(f, "%d ", &nodes[i]);
    
    for (i = 1; i <= num; i++)
        fscanf(f, "%d ", &p[i]);

    for (i = 0; i <= num; i++) {
        fscanf(f, "%d ", &arr[i][i].weight);
        arr[i][i].cost = 0;
        arr[i][i].root = 0;
    }
    
    fclose(f);

    for (i = 0; i < num; i++) 
        arr[i][i + 1].root = i + 1;

    for (i = 0; i < num - 1; i++)
        arr[i][i + 2].root = i + 1;

    arr[0][4].root = num / 2;

    int k;

    for (i = 1; i <= num; i++) {
        for (j = 0; j <= (num - i); j++) {
            arr[j][j + i].weight = arr[j][j].weight;
            for (k = j + 1; k <= j + i; k++) {
                arr[j][j + i].weight += arr[k][k].weight;
                arr[j][j + i].weight += p[k];
            }
            arr[j][j + i].cost = arr[j][j + i].weight;
            arr[j][j + i].cost += arr[j][arr[j][j + i].root - 1].cost;
            arr[j][j + i].cost += arr[arr[j][j + i].root][j + i].cost;
        }
    }

    f = fopen("output.txt", "w");
    if (!f) exit(1);

    fprintf(f, "Optimal Binary Search Tree의 총 비용은 %d이며 (%d/%d = %d)\n", arr[0][num].cost/totalcost, arr[0][num].cost, totalcost, arr[0][num].cost/totalcost);
    fprintf(f, "그 토폴로지는 다음과 같습니다.\n\n");
    print_tree(0, num, 1, f);

    fclose(f);
}


void print_tree(int i, int j, int pos, FILE* f) {
    if (i <= j) {
        int root = arr[i][j].root;
        if (root < 1 || root > num) return; 

        fprintf(f, "Complete BT의 %d번 노드 자리에 원소 %d가 위치합니다.\n", pos, nodes[root]);

        if (root > i) print_tree(i, root-1, pos*2, f);
        if (root < j) print_tree(root, j, pos*2+1, f);
    }
}