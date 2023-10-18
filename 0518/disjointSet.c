#include <stdio.h>
#include <stdlib.h>


void initTree(int **runs, int row);
void adjust(int row);
printTree();

int *tree;
int size = 1;

int *cnt;


int main(void) {
    FILE *f = fopen("input3.txt", "r");
    if (!f) exit(1);

    int n, row;
    fscanf(f, "%d %d\n", &n, &row);
    int col = n / row;

    int** runs = (int**)malloc(sizeof(int*) * row);
    cnt = (int*)malloc(sizeof(int) * row);

    int i, j;
    for(i = 0; i < row; i++) {
        runs[i] = (int*)malloc(sizeof(int) * col);
        cnt[i] = 0;
    }

    for (i = 0; i < row; i++) {
        for (j = 0; j < col; j++) {
            fscanf(f, "%d ", &runs[i][j]);
        }
    }

    fclose(f);

    initTree(runs, row);

    int *result = (int*)malloc(sizeof(int) * n);
    result[0] = tree[1];

    for (i = 1; i < n; i++) {
        for (j = 0; j < row; j++) {
            if (tree[row + j] == tree[1]) {
                if (cnt[j] < col) {
                    tree[row + j] = runs[j][cnt[j]++];
                    break;
                } else {
                    tree[row + j] = 100000;
                }
            } 
        }
        adjust(row);
        result[i] = tree[1];
    }


    for (int k = 0; k < n; k++)
        printf("%d ", result[k]);
    puts("");
}


void initTree(int **runs, int row) {
    int level = 1, temp = row, i, j;
    
    while(temp != 1) {
        temp /= 2;
        level++;
    }
    
    temp = 1;
    for (i = 0; i < level; i++) {
        size += temp;
        temp *= 2;
    }

    tree = (int*)malloc(sizeof(int) * size);

    for (i = 0; i < row; i++) 
        tree[row + i] = runs[i][cnt[i]++];

    adjust(row);
}


void adjust(int row) {
    for (int i = row - 1; i > 0; i--) {
        if (tree[2 * i] >= tree[2 * i + 1]) tree[i] = tree[2 * i + 1];
        else tree[i] = tree[2 * i];
    }
}

printTree() {
    for (int k = 1; k < size; k++)
        printf("%d ", tree[k]);
    puts("");
}
