#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct account {
 int accountNum;
 char name[30];
 int deposit;
 int loan;
};
typedef struct account account;

int main(void) {
    account arr[100];

    FILE * f1 = fopen("input.txt", "r");
    if(f1 == NULL) exit(1);

    int i = 0, j;
    while(!feof(f1)) {
        int num, deposit, loan;
        char name[101];
        fscanf(f1, "%d %s %d %d", &num, name, &deposit, &loan);

        arr[i].accountNum = num;
        arr[i].deposit = deposit;
        arr[i].loan = loan;
        strcpy(arr[i].name, name);
        i += 1;
    }
    fclose(f1);

    int maxId = 0;

    for (j = 1; j < i; j++) {
        if (arr[maxId].loan < arr[j].loan) maxId = j;
    }

    FILE * f2 = fopen("output.txt", "w");
    if(f2 == NULL) exit(1);

    fprintf(f2, "%d %s %d %d\n", arr[maxId].accountNum, arr[maxId].name, arr[maxId].deposit, arr[maxId].loan);
    fclose(f2);
}