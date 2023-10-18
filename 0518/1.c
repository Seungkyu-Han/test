#include <stdio.h>
#include <stdlib.h>


void inorder(char *arr, int idx);
void preorder(char *arr, int idx);
void postorder(char *arr, int idx);


char arr[21];

int main(void) {
    for (int i = 0; i < 21; i++) 
        arr[i] = 'N'; 

    FILE *f = fopen("input.txt", "r");
    if (f == NULL) exit(1);

    int avail;
    fscanf(f, "%d\n", &avail);

    int idx = 1;
    char data;
    while(!feof(f)) {
        fscanf(f, "%c ", &data);
        if(data != 'N') arr[idx] = data;
        idx++;
    }

    fclose(f);

    inorder(arr, 1);
    printf("\n");

    preorder(arr, 1);
    printf("\n");

    postorder(arr, 1);
    printf("\n");
}

void inorder(char *arr, int idx) {
    if (idx <= 20 && arr[idx] != 'N') {
        inorder(arr, idx*2);
        printf("%c", arr[idx]);
        inorder(arr, idx*2 + 1);
    }
}


void preorder(char *arr, int idx) {
    if (idx <= 20 && arr[idx] != 'N') {
        printf("%c", arr[idx]);
        preorder(arr, idx * 2);
        preorder(arr, idx * 2 + 1);

    }
}

void postorder(char *arr, int idx) {
    if (idx <= 20 && arr[idx] != 'N') {
        postorder(arr, idx * 2);
        postorder(arr, idx * 2 + 1);
        printf("%c", arr[idx]);
    }    
}