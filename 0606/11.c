#include <stdio.h>
#include <stdlib.h>
#define FALSE 0
#define TRUE 1


typedef enum{false, true, and, or, not, empty} logical;
typedef struct node* nodePointer;
typedef struct node {
    logical data;
    short int value;
    nodePointer left, right;
}node;


nodePointer copy(logical *bt, int idx);
void satisfy(nodePointer bt);
void inorder(nodePointer bt);


int size = 0;


int main(void) {
    FILE *f = fopen("input.txt", "r");
    if (!f) exit(1);

    int num;
    fscanf(f, "%d\n", &num);
    int *tvalues = (int*)malloc(sizeof(int) * num);

    char str[10];

    int i;
    for (i = 0; i < num; i++) {
        fscanf(f, "%s, ", str);
        if (str[0] == 't') tvalues[i] = TRUE;
        else tvalues[i] = FALSE;
    }

    logical bt1[1000];
    while(!feof(f)) {
        fscanf(f, "%s ", str);
        
        switch (str[0])
        {
        case 'a':
            bt1[++size] = and;
            break;

        case 'o':
            bt1[++size] = or;
            break;  

        case 'n':
            bt1[++size] = not;
            break;

        case 'x':
            if (tvalues[str[1] - '0' - 1]) bt1[++size] = true;
            else bt1[++size] = false;
            break;
        case 'e':
            bt1[++size] = empty;    
        }
    }

    fclose(f);


    nodePointer bt = copy(bt1, 1);
    //inorder(bt);

    satisfy(bt);

    if(bt->value) {
        printf("yes\n");
    } else printf("no\n");
}


nodePointer copy(logical *bt, int idx) {
    nodePointer new = NULL;
    if (idx <= size && bt[idx] != empty) {
        new = (nodePointer)malloc(sizeof(node));
        new->left = copy(bt, idx * 2);
        new->right = copy(bt, idx * 2 + 1);
        new->data = bt[idx];
    }

    return new;
}


void satisfy(nodePointer bt) {
    if (bt) {
        satisfy(bt->left);
        satisfy(bt->right);

        switch (bt->data)
        {
        case true:
            bt->value = TRUE;
            break;
        case false:
            bt->value = FALSE;
            break;
        case and:
            bt->value = bt->left->value && bt->right->value;
            break;
        case or:
            bt->value = bt->left->value || bt->right->value;
            break;                                    
        case not:
            bt->value = !bt->right->value;
            break;
        default:
            break;
        }
    }
}

void inorder(nodePointer bt) {
    if (bt) {
        inorder(bt->left);

        switch (bt->data)
        {
        case and:
            printf("and ");
            break;
        case or:
            printf("or ");
            break;  
        case not:
            printf("not ");
            break;
        case true:
            printf("true ");
            break;
        case false:
            printf("false ");
            break;
        case empty:
            printf("empty "); 
        }

        inorder(bt->right);
    }
}