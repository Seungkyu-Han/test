#include <stdio.h>
#include <stdlib.h>
#define MAX_TERMS 100
#define COMPARE(x,y) ((x > y) ? 1 : ((x == y) ? 0 : -1))

typedef struct{
    int coef;
    int exp;
}item;

int avail = 0;

void add(item *poly, int start1, int finish1, int start2, int finish2, int *startS, int *finishS);
void attach(item *poly, int coef, int exp);

int main(void) {
    FILE *f1 = fopen("input.txt", "r");
    if (f1 == NULL) exit(1);

    int n, m, i;

    fscanf(f1, "%d %d", &n, &m);

    int start1 = 0, finish1 = n - 1, start2 = n, finish2 = (n - 1) + m, startS = 0, finishS;

    item *poly = (item *) malloc(sizeof(item) * 100);

    while(!feof(f1)) {
        fscanf(f1, "%d %d", &poly[avail].coef, &poly[avail].exp);
        avail += 1;
    }

    fclose(f1);


    add(poly, start1, finish1, start2, finish2, &startS, &finishS);
    
    FILE *f2 = fopen("output.txt", "w");
    if (f2 == NULL) exit(1);

    for (i = startS; i <= finishS; i++) {
        fprintf(f2, "%d %d\n", poly[i].coef, poly[i].exp);
    }

    fclose(f2);
}

void add(item *poly,int start1, int finish1, int start2, int finish2, int *startS, int *finishS) {
    int coef;
    *startS = avail;

    while((start1 <= finish1) && (start2 <= finish2)) {
        switch (COMPARE(poly[start1].exp, poly[start2].exp))
        {
        case -1:
            attach(poly, poly[start2].coef, poly[start2].exp);
            start2 += 1;
            break;
        case 0:
            coef = poly[start1].coef + poly[start2].coef;
            if (coef)
                attach(poly, coef, poly[start1].exp);
            start1 += 1;
            start2 += 1;
            break;
        case 1:
            attach(poly, poly[start1].coef, poly[start1].exp);
            start1 += 1;
            break;
        }
    }

    for(; start1 <= finish1; start1++) {
        attach(poly, poly[start1].coef, poly[start1].exp);
    }

    for(; start2 <= finish2; start2++) {
        attach(poly, poly[start2].coef, poly[start2].exp);
    }

    *finishS = avail - 1;
}

void attach(item *poly, int coef, int exp) {
    if (avail >= MAX_TERMS) {
        exit(EXIT_FAILURE);
    }
    
    poly[avail].coef = coef;
    poly[avail++].exp = exp;
}