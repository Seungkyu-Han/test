#include <stdio.h>
#include <stdlib.h>
#define DEFAULT_SIZE 20

typedef struct {
    int row;
    int col;
    int dir;
} element;

void push(int row, int col, int dir);
element pop();
int vert_move(int dir);
int hor_move(int dir);
void findPath(int start[], int end[]);

element *stack;
int top = -1;
int capacity;

int **maze, **mark;
int i, j, result = 0;

int main(void) {
    FILE *f1 = fopen("input.txt", "r");
    if (f1 == NULL) {
        printf("f1 error\n");
        exit(1);
    }

    int row, col;
    fscanf(f1, "%d %d", &row, &col);

    maze = (int**)malloc(sizeof(int*) * (row + 2));
    mark = (int**)malloc(sizeof(int*) * (row + 2));

    for (i = 0; i < row + 2; i++) {
        maze[i] = (int*)malloc(sizeof(int) * (col + 2));
        mark[i] = (int*)malloc(sizeof(int) * (col + 2));
    }

    for (i = 0; i <= row + 1; i++) {
        for (j = 0; j <= col + 1; j++) {
            if (i == 0 || j == 0 ||i == row + 1 || j == col + 1)
                maze[i][j] = 1;
            else 
            fscanf(f1, "%d", &maze[i][j]);
        }
    }

    fclose(f1);

    int start[2] = {1,1};
    int end[2] = {row, col};

    capacity = row * col;
    findPath(start, end);

    FILE *f2 = fopen("output.txt", "w");
    if (f2 == NULL) {
        printf("f2 error\n");
        exit(1);
    }

    if (result) {
        fprintf(f2, "success\n");
        fprintf(f2, "path는 ");

        push(row, col, 1);
        
        for (i = 0; i <= top; i++) {
            fprintf(f2,"(%d,%d) ", stack[i].row, stack[i].col);
        }
            fprintf(f2, "\n사용한 스택의 크기 / 스택의 최대 크기 = %d / %d", top + 1, row * col);
    }
    else fprintf(f2, "fail");

    fclose(f2);

    for (int i = 0; i < row; i++) {
        free(maze[i]);
        free(mark[i]);
    }
    free(stack);
    free(maze);
    free(mark);
}


void push(int row, int col, int dir) {
    if (top >= capacity - 1) {
        capacity *= 2;
        stack = realloc(stack, sizeof(element) * capacity);
    }
        top++;
        stack[top].col = col;
        stack[top].row = row;
        stack[top].dir = dir;
}


element pop() {
    if (top < 0) {
        fprintf(stderr, "stack이 비어있습니다.");
        exit(1);
    }
    else {
        element ret = stack[top];
        top--;
        return ret;
    }
}

void findPath(int start[], int end[]) {
    stack = (element*) malloc(sizeof(element) * capacity);

    int row, col, nextRow, nextCol, dir;
    element pos;

    mark[1][1] = 1;

    stack[++top].row = start[0];
    stack[top].col = start[1];
    stack[top].dir = 1;

    while (top > -1 && !result) {
        pos = pop();
        row = pos.row;
        col = pos.col;
        dir = pos.dir;

        while (dir < 8 && !result) {
            nextRow = row + vert_move(dir);
            nextCol = col + hor_move(dir);

            if (nextRow == end[0] && nextCol == end[1]) {
                result = 1;
                push(row, col, dir);
            }
            else if (!maze[nextRow][nextCol] && !mark[nextRow][nextCol]) {
                mark[nextRow][nextCol] = 1;

                pos.row = row;
                pos.col = col;
                pos.dir = ++dir;

                push(pos.row, pos.col, pos.dir);

                row = nextRow;
                col = nextCol;
                dir = 0;
            }
            else ++dir;
        }
    }
}


int vert_move(int dir) {
    switch (dir) {
        case 0:
        case 1:
        case 7:
            return -1;
        case 3:
        case 4:
        case 5:
            return 1;
        default:
            return 0;
    }
}


int hor_move(int dir) {
    switch (dir) {
        case 5:
        case 6:
        case 7:
            return -1;
        case 1:
        case 2:
        case 3:
            return 1;
        default:
            return 0;
    }
}
