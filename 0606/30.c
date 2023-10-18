#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TRUE 1
#define FALSE 0


typedef struct {
    char data[100];
    int key;
} bucket;


int getSize(int n);
int hash(int key);
void insert(char *input);
int search(char *input);


bucket *ht;
int size;


int main(void) {
    FILE *f = fopen("input.txt", "r");
    if (!f) exit(1);

    int num;
    fscanf(f, "%d\n\n", &num);
    size = getSize(num);
    ht = (bucket*)malloc(sizeof(bucket) * size);

    int i; char input[100];
    for (i = 0; i < num; i++) {
        fscanf(f, "%s ", input);
        insert(input);
    }

    fclose(f);

    while(1) {
        printf("검색할 키워드를 입력하시오...\n");
        scanf("%s", input);
        if (!strcmp("quit", input)) break;
        i = search(input);
        if (!i) printf("> 키워드가 존재하지 않습니다.\n");
    }
}


int getSize(int n) {
    int i, j, isPrime;
    for (i = n + 1;; i++) {
        isPrime = TRUE;
        for (j = 2; j * j <= i; j++) {
            if (i % j == 0) {
                isPrime = FALSE;
                break;
            }
        }

        if (isPrime) return i;
    }

    return -1;
}


int hash(int key) {
    return key % size;
} 


int stringToInt(char *item) {
    int sum = 0;
    while(*item) sum += *item++;

    return sum;
}


void insert(char *input) {
    int homeBucket = hash(stringToInt(input));

    while(ht[homeBucket].key) {
        homeBucket = (homeBucket + 1) % size;
    }

    strcpy(ht[homeBucket].data, input);
    ht[homeBucket].key = homeBucket;
}


int search(char *input) {
    int temp = hash(stringToInt(input));
    int hb = temp;
    while(ht[hb].key) {
        if (!strcmp(ht[hb].data, input)) {
            printf("> 버킷 주소 %d에 저장된 키워드입니다.\n", ht[hb].key);
            return TRUE;
        }
        hb = (hb + 1) % size;
        if (hb == temp) break;
    }

    return FALSE;
}