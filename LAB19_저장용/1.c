#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TRUE 1
#define FALSE 0


typedef struct {
    char key[100];
    int value;
} entry;


int getTableSize(int n);
int stringToInt(char *key);
int hash(char *key, int size);
void insert(char *key, int value, int size);
int search(char *key, int size);


entry *hashTable;


int main() {
    FILE *f = fopen("input.txt", "r");
    if (!f) exit(1);

    int num;
    fscanf(f, "%d", &num);

    int size = getTableSize(num);
    hashTable = (entry*)malloc(sizeof(entry) * size);

    char *word = (char*)malloc(sizeof(char) * num);
    for (int i = 0; i < num; i++) {
        fscanf(f, "%s", word);
        insert(word, i+1, size);
    }

    fclose(f);

    char *input = (char*)malloc(sizeof(char) * num);
    while (1) {
        printf("> 검색할 키워드를 입력하시오...\n");
        scanf("%s", input);

        if (!strcmp(input, "quit")) break;
        
        num = search(input, size);
        if (num == -1) printf("키워드가 존재하지 않습니다.\n");
        else printf("혹은 버킷 주소 %d에 저장된 키워드입니다.\n", num);
    }
}


int getTableSize(int n) {
    int i = n + 1, j;
    int isPrime;

    for(;; i++) {
        isPrime = TRUE;
        for(j = 2; j*j <= i; j++) {
            if(i % j == 0) {
                isPrime = FALSE;
                break;
            }
        }
        if(isPrime) return i;
    }
}


int stringToInt(char *key) {
    unsigned int number = 0;
    while (*key)
        number += *key++;
    return number;
}


int hash(char *key, int size) {
    return stringToInt(key) % size;
}


void insert(char *key, int value, int size) {
    unsigned int bucket = hash(key, size);
    while (hashTable[bucket].value) {
        bucket = (bucket + 1) % size;
    }
    strcpy(hashTable[bucket].key, key);
    hashTable[bucket].value = value;
}


int search(char *key, int size) {
    unsigned int bucket = hash(key, size);
    while (strcmp(hashTable[bucket].key, key)) {
        if (!hashTable[bucket].value) {
            return -1;
        }
        bucket = (bucket + 1) % size;
    }
    return bucket; 
}
