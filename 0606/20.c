#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void makeTopology(int start, int left, int right, int idx);


char preorder[100];
char inorder[100];
int len;
char bt[100];


int main(void) {
    FILE *f = fopen("input.txt", "r");
    if (!f) exit(1);

    fscanf(f, "preorder sequence : %s\n", preorder);
    fscanf(f, "inorder sequence : %s", inorder);

    fclose(f);

    len = strlen(preorder);


    makeTopology(0, 0, len - 1, 1);

    int cnt = 0;
    for (int i = 1; i < 100; i++) {
        if (cnt <= len && bt[i]) {
            cnt++;
            printf("%d, ", i);
        }
    }
}

void makeTopology (int start, int left, int right, int idx) {

    if (left <= right && start <= len) {
        char pivot = preorder[start];

        int i;
        for (i = left; i <= right; i++) {
            if (pivot == inorder[i]) break;
        }

        bt[idx] = inorder[i];

        makeTopology(start + 1, left, i - 1, idx * 2);
        makeTopology(start + i - left + 1, i + 1, right, idx * 2 + 1);
    }    
}


