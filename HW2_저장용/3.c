#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX 20

int push(int color);
int pop();
void make (int cnt, int order[]);
void takeMarble (int cnt, int *total, int order[]);

int stack[MAX] = {-1};
int top = -1;


int main(void) {
    int cnt; // cnt : 구슬 개수, cnt <= 20
    int i, total = 0;
    char repeat;

    do {
        printf("****************************************\n");
        printf("구슬 개수를 입력하세요 : ");
        scanf("%d", &cnt);
        fflush(stdin);
        printf("생성된 구슬 : "); 

        int order[20];
        make(cnt, order);
        takeMarble(cnt, &total, order);
        
        printf("다시 하겠습니까? [y/n] : ");
        scanf("%c", &repeat);

    } while ((repeat == 'y') || (repeat == 'Y'));

    printf("프로그램을 종료합니다.\n");
}

int push(int item) {
    if (top >= MAX - 1) 
        return 0;
    stack[++top] = item;
    return 1;
}

int pop () {
    if (top < 0) {
        return -1;
    }
    return stack[top--];
}

void make (int cnt, int order[]) {
    time_t  t = time(NULL);
    int color[2] = {0, 0}; //black = 0, white = 1
    srand(t);

    for (int i = 0; i < cnt; i++) {
        int num = rand() % 2;
        color[num] += 1;
        order[i] = num;
        if (num) printf("흰 ");
        else printf("검 ");
    }
}

void takeMarble (int cnt, int *total, int order[]) {
    int index = 0;

    while(index < cnt) {
        if (order[index++]) { // white
            if (pop() != -1) {
                *total -= 1;
                if (pop() != -1) *total -= 1;
            }
            push(1);
            *total += 1;
        } else {
            if (push(0)) {
                *total += 1;
                if (push(0)) *total += 1;
                else break;
            } else break;
        }
    }

    index = 0;
    int black = 0, white = 0;

    while(index < *total) {
        if (stack[index++]) white += 1;
        else black += 1;
    }

    printf("\n주머니에 구슬을 넣었습니다.\n\n");
    printf("결과\n");
    printf("하얀색 구슬: %d개\n", white);
    printf("검은색 구슬: %d개\n", black);    
}