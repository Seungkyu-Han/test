#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int row;
    int col;
    int value;
}term;



void fastTranspose(term a[], term b[]);

int main(void) {
    FILE *f1 = fopen("input.txt", "r");
    if (f1 == NULL) exit(1);

    int n, i,j, cnt = 1;
    fscanf(f1, "%d", &n);


    term original[401];
    term posed[401];
    
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            int temp;
            fscanf(f1, "%d" , &temp);
    
            if (temp) {
                original[cnt].col = j;
                original[cnt].row = i;
                original[cnt++].value = temp;
            }
        }
    }

    original[0].row = n;
    original[0].col = n;
    cnt -= 1;
    original[0].value = cnt;

    fclose(f1);


    FILE *f2 = fopen("output.txt", "w");
    if (f2 == NULL) exit(1);

    fprintf(f2, "%d\n", cnt);

    fastTranspose(original, posed);

    for(i = 1; i <= cnt; i++) {
        fprintf(f2, "%d %d %d\n", posed[i].row, posed[i].col, posed[i].value);
    }

    fclose(f2);
}   

void fastTranspose(term a[], term b[]) {

    int rowTerms[20], startingPos[20];
    
    int elements = a[0].value;
    int cols = a[0].col;
    int rows = a[0].row;

    b[0].col = rows;
    b[0].row = cols;
    b[0].value = elements;

    int i, j;

    for (i = 0; i < cols; i++)
        rowTerms[i] = 0;

    for (i = 1; i <= elements; i++) {
        rowTerms[a[i].col] += 1;
    }
    
    startingPos[0] = 1;

    for (i = 1; i < cols; i++) {
        startingPos[i] = startingPos[i - 1] + rowTerms[i - 1];
    }
    
    for (i = 1; i <= elements; i++) {
        j = startingPos[a[i].col]++;

        b[j].row = a[i].col;
        b[j].col = a[i].row;
        b[j].value = a[i].value;
    }


}