#include <stdio.h>
#include <stdlib.h>
#define MAX 5

void add ();
int delete();
void printList();

int queue [MAX];
int front = -1, rear = -1;

int main(void) {
    int option, check = 1, num;

    do {
        printf("****************************************\n");
        printf("* 1. AddQ                              *\n");
        printf("* 2.DeleteQ                            *\n");
        printf("* 3. List                              *\n");
        printf("* 4. Exit                              *\n");
        printf("****************************************\n");
        printf("Menu : ");
        scanf("%d", &option);

        switch (option)
        {
        case 1:
            add();
            break;
        case 2:
            num = delete();
            if (num)
                printf("DeleteQ Data : %d\n", num);
            break;
        case 3:
            printList();
            break;
        default:
            check = 0;
            printf("Exit\n");
            break;
        }

        puts("");
    }while(check);
}

void add () {
    if (rear == MAX - 1) printf("Error!\n");
    else {
        int item;
        printf("AddQ Data : ");
        scanf("%d", &item);
        queue[++rear] = item;
    }
}

int delete() {
     if (rear == front) {
        printf("Error!\n");
        return 0;
     }

    else {
        return queue[++front];
    }   
}

void printList() {
    if (rear != front)
        printf("List : ");

    for (int i = front + 1; i <= rear; i++) {
        printf("%d ", queue[i]);
    }
    puts("");
}