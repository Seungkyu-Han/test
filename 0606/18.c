#include <stdio.h>
#include <stdlib.h>
#define NO 100000


int collapsingFind(int i);
void weightedUnion(int i, int j);

int *parent;


int main(void) {
    FILE *f = fopen("input.txt", "r");
    if (!f) exit(1);

    int num;
    fscanf(f, "%d\n", &num);
    int *first = (int*)malloc(sizeof(int) * num);
    int *second = (int*)malloc(sizeof(int) * num);

    fscanf(f, "%d = %d, ", &first[0], &second[0]);

    int max = (first[0] > second[0]) ? first[0] : second[0];

    int i;
    for (i = 1; i < num; i++) {
        fscanf(f, "%d = %d, ", &first[i], &second[i]);
        int bigger = (first[i] > second[i]) ? first[i] : second[i];
        if (max < bigger) max = bigger;
    }

    fclose(f);

    parent = (int*)malloc(sizeof(int) * (max + 1));

    int j;
    for (i = 0; i <= max; i++) {
        int included = 0;
        for (j = 0; j < num; j++) {
            if (i == first[j] || i == second[j]) {
                included = 1;
                break;
            }
        }

        if (included) parent[i] = -1;
        else parent[i] = NO;
    }

    for (i = 0; i < num; i++)
        weightedUnion(first[i], second[i]);

    for (i = 0; i <= max; i++) {
        if (parent[i] < 0) {
            printf("{%d, ", i);
            for (j = 0; j <= max; j++) {
                if (parent[j] == i) {
                    printf("%d, ", j);
                }
            }
            printf("}, ");
        }
    }
}


int collapsingFind(int i) {
    if (parent[i] == NO) return -1;

    int root = i, trail = i, lead;
    for (; parent[root] >= 0; root = parent[root]);
    for (; trail != root; trail = lead) {
        lead = parent[trail];
        parent[trail] = root;
    }

    return root;
}


void weightedUnion(int i, int j) {
    if (parent[i] == NO || parent[j] == NO) return;

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