#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct tree* treePointer;
typedef struct tree {
    char data;
    treePointer left;
    treePointer right;
} tree;

treePointer createNode(char item);
treePointer buildTopology(int preStart, int inStart, int inEnd);
void getResult(treePointer lt, int nodeNum, char* nodes);

char preorder[100];
char inorder[100];


int main() {
    FILE* f;

    f = fopen("input2.txt", "r");
    if (f == NULL) exit(1);

    fscanf(f, "preorder sequence : %s\n", preorder);
    fscanf(f, "inorder sequence : %s\n", inorder);

    fclose(f);

    int len = strlen(inorder);
    treePointer lt= buildTopology(0, 0, len - 1);

    int size = pow(2, (strlen(preorder) + 1)) - 1;
    char* result = (char*)malloc(sizeof(char) * size);

    getResult(lt, 1, result);

    f = fopen("output.txt", "w");
    if (f == NULL) exit(1);

    int ind = 0;
    for (int i = 0; i < size; i++) {
        if (result[i] != '\0') {
            fprintf(f, "%d", i + 1);

            if (ind == len - 1) break;

            fprintf(f, ", ");
            ind++;
        }
    }

    fclose(f);
}


treePointer createNode(char item) {
    treePointer lt = (treePointer)malloc(sizeof(tree));
    lt->data = item;
    lt->left = NULL;
    lt->right = NULL;

    return lt;
}


treePointer buildTopology(int preStart, int inStart, int inEnd) {
    if (preStart >= strlen(preorder) || inStart > inEnd) {
        return NULL;
    }

    treePointer lt = createNode(preorder[preStart]);

    int rootIndex;
    for (rootIndex = inStart; rootIndex <= inEnd; rootIndex++) {
        if (inorder[rootIndex] == preorder[preStart]) {
            break;
        }
    }

    int leftSubtreeSize = rootIndex - inStart;

    lt->left = buildTopology(preStart + 1, inStart, rootIndex - 1);
    lt->right = buildTopology(preStart + leftSubtreeSize + 1, rootIndex + 1, inEnd);

    return lt;
}


void getResult(treePointer lt, int nodeNum, char* nodes) {
    if (lt) {
        nodes[nodeNum - 1] = lt->data;
        getResult(lt->left, nodeNum * 2, nodes);
        getResult(lt->right, nodeNum * 2 + 1, nodes);
    }
}


