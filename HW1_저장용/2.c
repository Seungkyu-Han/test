#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int num;
    char name[100];
    float score1;
    float score2;
    float sum;
}person;

int main(void) {
    FILE *f1 = fopen("input.txt", "r");
    if (f1 == NULL) exit(1);

    int i = 0;
    person *arr = (person *) malloc(sizeof(person));

    while(!feof(f1)) {
        fscanf(f1, "%d %s %f %f", &arr[i].num, arr[i].name, &arr[i].score1, &arr[i].score2);
        arr[i].sum = arr[i].score1 + arr[i].score2;
        i += 1;
        arr = realloc(arr, sizeof(person) * (i + 1));
    }

    fclose(f1);

    FILE *f2 = fopen("output.txt", "w");
    if (f2 == NULL) exit(1);

    for (int j = 0; j < i; j++)
        fprintf(f2, "%d %s %.1f %.1f %.1f\n", arr[j].num, arr[j].name, arr[j].score1, arr[j].score2, arr[j].sum);

    fclose(f2);

}