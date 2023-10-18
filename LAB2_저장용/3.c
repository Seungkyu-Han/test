#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    FILE * f1 = fopen("input.txt", "r");
    if(f1 == NULL) exit(1);

    char s1[101], s2[101];
    fgets(s1, 100, f1);
    fgets(s2, 100, f1);

    fclose(f1);

    int s1L = strlen(s1);
    int s2L = strlen(s2);

    char ** arr;
    arr = (char **) malloc(sizeof(char *) * 2);
    arr[0] = malloc(sizeof(char) * s1L);
    arr[1] = malloc(sizeof(char) * s2L);

    arr[0] = s1;
    arr[1] = s2;

    FILE * f2 = fopen("output.txt", "w");
    if(f2 == NULL) exit(1);

    fprintf(f2, "%s", arr[0]);
    fprintf(f2, "%s", arr[1]);

    fclose(f2);
}