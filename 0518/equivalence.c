#include <stdio.h>
#include <stdlib.h>


void weightedUnion (int i, int j);
int find(int i);


int parent[11];
int count[11];


int main(void) {
    int i;
    for (i = 0; i < 11; i++) {
        count[i] = 1;
        parent[i] = -2;
    }

    FILE *f = fopen("input.txt", "r");
    if (!f) exit(1);

    int num;
    fscanf(f, "%d\n", &num);

    int first, second;
    for (i = 0; i < num; i++) {
        fscanf(f, "%d = %d, ", &first, &second);
        if (parent[second] > parent[first]) weightedUnion(second, first);
        else weightedUnion(first, second);
    }

    fclose(f);

    int j;
    for (i = 0; i < 11; i++) {
        if (parent[i] != -2 && i == find(i)) {
            printf("{%d, ", i);
            for (j = 0; j < 11; j++) {
                if (parent[j] == i) {
                    printf("%d, ", j);
                }
            }
            printf("}, ");
        }
    }
}

void weightedUnion (int i, int j) {
    if (parent[i] == -2) parent[i] = -1;
    if (parent[j] == -2) parent[j] = -1;

    int temp, root;
    if (count[i] >= count[j]) {
        root = find(i);
        count[root] += count[j];
        parent[j] = root;
    }
    else {
        root = find(j);
        count[root] += count[i];
        parent[i] = root;
    }
}


int find(int i) {
    int root = i;
    for (; parent[root] > -1; root = parent[root]);

    return root;
}