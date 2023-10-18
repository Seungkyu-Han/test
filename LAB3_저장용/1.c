#include <stdio.h>
#include <stdlib.h>
#define MAX_TERMS 100
#define COMPARE(x,y) ((x > y) ? 1 : ((x == y) ? 0 : -1))

int avail = 0;
int poly[MAX_TERMS][2];


void add(int start1, int finish1, int start2, int finish2, int *startS, int *finishS);
void attach(int coeff, int expp);

int main(void) {
    FILE *f1 = fopen("input.txt", "r");
    if (f1 == NULL) exit(1);

    int n, m, i;

    fscanf(f1, "%d %d", &n, &m);

    int start1 = 0, finish1 = n - 1, start2 = n, finish2 = (n - 1) + m, startS = 0, finishS;

    while(!feof(f1)) {
        fscanf(f1, "%d %d", &poly[avail][0], &poly[avail][1]);
        avail += 1;
    }

    fclose(f1);

    add(start1, finish1, start2, finish2, &startS, &finishS);
    
    FILE *f2 = fopen("output.txt", "w");
    if (f2 == NULL) exit(1);

    for (i = startS; i <= finishS; i++) {
        fprintf(f2, "%d %d\n", poly[i][0], poly[i][1]);
    }
    fclose(f2);
}

void add(int start1, int finish1, int start2, int finish2, int *startS, int *finishS) {
    *startS = avail;
    int co;

    while((start1 <= finish1) && (start2 <= finish2)) {
        switch (COMPARE(poly[start1][0], poly[start2][0]))
        {
        case -1:
            attach(poly[start2][0], poly[start2][1]);
            start2 += 1;
            break;
        case 0:
            co = poly[start1][0] + poly[start2][0];
            if (co)
                attach(co, poly[start1][1]);
            start1 += 1;
            start2 += 1;
            break;
        case 1:
            attach(poly[start1][0], poly[start1][1]);
            start1 += 1;
            break;
        }
    }

    for(; start1 <= finish1; start1++) {
        attach(poly[start1][0], poly[start1][1]);
    }

    for(; start2 <= finish2; start2++) {
        attach(poly[start2][0], poly[start2][1]);
    }

    *finishS = avail - 1;
}

void attach(int coeff, int expp) {
    if (avail >= MAX_TERMS) {
        exit(EXIT_FAILURE);
    }
    poly[avail][0] = coeff;
    poly[avail++][1] = expp;

}