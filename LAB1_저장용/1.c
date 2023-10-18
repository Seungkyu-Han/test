#include <stdio.h>
#include <stdlib.h>

int main(void) {
    FILE * input = fopen("input.txt", "r");
    if (input == NULL) exit(1);
    int num;
    fscanf(input, "%d", &num);
    fclose(input);

    int sum = 0;
    for (int i = 1; i <= num; i++) sum += i;

    FILE * output = fopen("output.txt", "w");
    if (output == NULL) exit(1);
    fprintf(output, "%d", sum);
    fclose(output);
}