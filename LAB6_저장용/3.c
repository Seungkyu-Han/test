#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//---------------------------------------- 

typedef enum {lparen, rparen, plus, minus, times, divide, mod, and, or, equal, not, over, less, eover, eless, eos, operand} precedence; 

void push(precedence item);
precedence pop();
void remove_spaces(char *str);
precedence getToken(char *symbol, int *cnt, char exp[]);
void printToken(precedence token);
void convertToPostFIx();
int calculate();
void push2(int item);
int pop2();

//----------------------------------------stack

precedence *stack;
int top = 0;
int capacity = 2;

int *stack2;
int top2 = -1;
int capacity2 = 2;

//---------------------------------------- others
char exps[1000];
char exps_postfix[1000];
int isp[] = {0, 19, 12, 12, 13, 13, 13, 5, 4, 9, 9, 10, 10, 10, 10, 0};
int icp[] = {20, 19, 12, 12, 13, 13, 13, 5, 4, 9, 9, 10, 10, 10, 10, 0};
int i, j;
FILE *f1, *f2;

//----------------------------------------
int main(void) {
    stack = (precedence*)malloc(sizeof(precedence) * capacity);
    stack[0] = eos;

    f1 = fopen("input.txt", "r");
    f2 = fopen("output.txt", "w");

    if ((f1 == NULL) || (f2 == NULL)) exit(1);

    fgets(exps, 101, f1);
    remove_spaces(exps);

    convertToPostFIx();

    fclose(f2);
    f2 = fopen("output.txt", "r+");
    
    stack2 = (int*)malloc(sizeof(int) * capacity2);

    fgets(exps_postfix, 101, f2);
    exps_postfix[strlen(exps_postfix)] = ' ';


    printf("%s\n", exps_postfix);

    int result = calculate();

    printf("%d\n", result);
    fprintf(f2, "\n%d", result);

    fclose(f1);
    fclose(f2);
}

//---------------------------------------- functions

void push(precedence item) {
    if (top >= capacity - 1) {
        capacity *= 2;
        stack = realloc(stack, sizeof(precedence) * capacity);
    }
    stack[++top] = item;
}

void push2(int item) {
    if (top2 >= capacity2 - 1) {
        capacity2 *= 2;
        stack2 = realloc(stack2, sizeof(int) * capacity2);
    }
    stack2[++top2] = item;
}

precedence pop() {
    if (top <= -1) {
        printf("stack is empty\n");
        exit(1);
    }
    return stack[top--];
}

int pop2() {
    if (top2 <= -1) {
        printf("stack2 is empty\n");
        exit(1);
    }
    return stack2[top2--];
}


void remove_spaces(char *str) {
    char *src = str, *dst = str;
    while (*src) {
        if (isspace((unsigned char)*src)) 
            src++;
        else 
            *dst++ = *src++;
    }
}

precedence getToken(char *symbol, int *cnt, char exp[]) {

        *symbol = exp[++(*cnt)];

        switch (*symbol)
        {
        case '(': return lparen;
        case ')': return rparen;
        case '+': return plus;
        case '-': return minus;
        case '/': return divide;
        case '*': return times;
        case '%': return mod;
        case '>':
            if (exp[++(*cnt)] == '=') {
                return eover;
            }
            else {
                (*cnt)-= 1;
                return over;
            }
        case '<': 
            if (exp[++(*cnt)] == '=') {
                return eless;  
            }   
            else {
                (*cnt)-= 1;
                return less;
            }
        case '&':
            (*cnt)+= 1;
            return and;
        case '|':
            (*cnt)+= 1;
            return or;
        case '=':
            (*cnt)+= 1;
            return equal;
        case '!':
            (*cnt)+= 1;
            return not;
        case ' ': return eos;
        default: return operand;
        }
}

void printToken(precedence token) {
    switch(token) {  
        case plus:
            printf("+");
            fprintf(f2, "+");
            break;   
        case minus:
            printf("-");
            fprintf(f2, "-");
            break;      
        case divide:
            printf("/");
            fprintf(f2, "/");
            break;  
        case times:
            printf("*");
            fprintf(f2, "*");
            break;            
        case mod:
            printf("%%");
            fprintf(f2, "%%");
            break;
        case and:
            printf("&&");
            fprintf(f2, "&&"); 
            break;  
        case or:
            printf("||");
            fprintf(f2, "||");    
            break; 
        case equal:
            printf("==");
            fprintf(f2, "=="); 
            break;
        case not:
            printf("!=");
            fprintf(f2, "!="); 
            break;  
        case over:
            printf(">");
            fprintf(f2, ">");   
            break;
        case less:
            printf("<");
            fprintf(f2, "<");  
            break;
        case eover:
            printf(">=");
            fprintf(f2, ">=");   
            break; 
        case eless:
            printf("<=");
            fprintf(f2, "<="); 
            break;                                                                                     
        default :
            break;                                                        
    }
}

void convertToPostFIx() {
    precedence token;
    char symbol;
    int cnt = -1;   //last symbol counter

    for (token = getToken(&symbol, &cnt, exps); token != eos; token = getToken(&symbol, &cnt, exps)) {
        if (token == operand) {
            printf("%c", symbol);
            fprintf(f2, "%c", symbol);
        } else if (token == rparen) {
            while(stack[top] != lparen) {
                printToken(pop());
            }
            pop();
        } else {
            while(isp[stack[top]] >= icp[token]) {
                 printToken(pop());
            }
            push(token);
        }
    }

    while((token = pop()) != eos) {
        if ((top2 == -1) && (token == plus))
            continue;
        printToken(token);
    }

    puts("");
}

int calculate() {
    precedence token;
    char symbol;
    int op1, op2;
    int cnt = -1;  //last symbol counter
    int i = 0;

    token = getToken(&symbol, &cnt, exps_postfix);

    while(token != eos) {
        if (token == operand) {
            printf("%c : push\n", symbol);
            push2(symbol - '0');
        } else {
            op2 = pop2();
            op1 = pop2();

            printf("popx2\n");

            switch(token) {
                case plus:
                    push2(op1 + op2);
                    break;
                case minus: 
                    push2(op1 - op2);
                    break;
                case times:
                    push2(op1 * op2);
                    break;
                case divide: 
                    push2(op1 / op2);
                    break;
                case mod: 
                    push2(op1 % op2);
                    break;
                case and:
                    push2(op1 && op2);
                    break;
                case or:
                    push2(op1 || op2);
                    break;
                case equal:
                    push2(op1 == op2);
                    break;
                case not:
                    push2(op1 != op2);
                    break;
                case over:
                    push2(op1 > op2);
                    break;
                case less:
                    push2(op1 < op2);
                    break;
                case eover:
                    push2(op1 >= op2);
                    break;
                case eless:
                    push2(op1 <= op2);
                    break;
                default :
                    break;
            }
        }
        token = getToken(&symbol, &cnt, exps_postfix);
    }

    return pop2();
}