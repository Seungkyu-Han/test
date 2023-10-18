#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    char arr[3][21];
    char (*ptr)[21] = arr;

    FILE *f1 = fopen("input.txt", "r");
    if (f1 == NULL) exit(1);

    char str[21];
    fgets(str, 20, f1);
    strcpy(ptr[0], str);

    fgets(str, 20, f1);
    strcpy(ptr[1], str);

    fgets(str, 20, f1);
    strcpy(ptr[2], str);

    fclose(f1);

    FILE *f2 = fopen("output.txt", "w");
    if (f2 == NULL) exit(1);

    fprintf(f2, "%s", ptr[0]);
    fprintf(f2, "%s", ptr[1]);
    fprintf(f2, "%s", ptr[2]);

    fclose(f2);
}