#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(void) {
    char input[100], output[100];
    scanf("%s %s", input, output);

    FILE *f1 = fopen(input, "r");
    if (f1 == NULL) exit(1);

    FILE *f2 = fopen(output, "w");
    if (f2 == NULL) exit(1);

    char buffer[101];

    while(fgets(buffer, 100, f1) != NULL) {
        int cnt = 0;
        while(buffer[cnt]) {
            if (isupper(buffer[cnt]))
                buffer[cnt] = tolower(buffer[cnt]);
            else
                buffer[cnt] = toupper(buffer[cnt]);
            cnt += 1;
        }

        fputs(buffer, f2);
    }

    fclose(f1);
    fclose(f2);
}