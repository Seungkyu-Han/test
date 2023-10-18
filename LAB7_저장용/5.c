#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//---------------------------------------- 

typedef enum {lparen, rparen, plus, minus, times, divide, mod, and, or, equal, not, over, less, eover, eless, eos, operand} precedence;

typedef struct Node {
    precedence data;
    struct Node* next;
}node;

typedef struct Stack {
    node* top;
} Stack;

typedef struct Node2 {
    int data;
    struct Node2* next;
}node2;

typedef struct Stack2 {
    node2* top;
} Stack2;

//----------------------------------------


void remove_spaces(char *str);
precedence getToken(char *symbol, int *cnt, char exp[]);
void printToken(precedence token);
void convertToPostFIx(Stack *stack);
int calculate(Stack2 *stack);

void push(Stack* stack, precedence data);
precedence pop(Stack* stack);
void push2(Stack2* stack, int data);
int pop2(Stack2* stack);

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
    Stack stack = {NULL};
    push(&stack, eos);

    f1 = fopen("input.txt", "r");
    f2 = fopen("output.txt", "w");

    if ((f1 == NULL) || (f2 == NULL)) exit(1);

    fgets(exps, 101, f1);
    remove_spaces(exps);

    convertToPostFIx(&stack);

    fclose(f2);
    f2 = fopen("output.txt", "r+");
    
    Stack2 stack2 = {NULL};

    fgets(exps_postfix, 101, f2);
    exps_postfix[strlen(exps_postfix)] = ' ';


    printf("%s\n", exps_postfix);

    int result = calculate(&stack2);

    printf("%d\n", result);
    fprintf(f2, "\n%d", result);

    fclose(f1);
    fclose(f2);
}

//---------------------------------------- functions

void push(Stack* stack, precedence data) {
    node* newNode = (node*) malloc(sizeof(node));
    newNode->data = data;
    newNode->next = stack->top;
    stack->top = newNode;
}

precedence pop(Stack* stack) {
    if (stack->top == NULL) {
        printf("Error: Stack is empty!\n");
        exit(1);
    }
    node* temp = stack->top;
    precedence data = temp->data;
    stack->top = temp->next;
    free(temp);
    return data;
}

void push2(Stack2* stack, int data) {
    node2* newNode = (node2*) malloc(sizeof(node2));
    newNode->data = data;
    newNode->next = stack->top;
    stack->top = newNode;
}

int pop2(Stack2* stack) {
    if (stack->top == NULL) {
        printf("Error: Stack is empty!\n");
        exit(1);
    }
    node2* temp = stack->top;
    int data = temp->data;
    stack->top = temp->next;
    free(temp);
    return data;
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

void convertToPostFIx(Stack *stack) {
    precedence token;
    char symbol;
    int cnt = -1;   //last symbol counter

    for (token = getToken(&symbol, &cnt, exps); token != eos; token = getToken(&symbol, &cnt, exps)) {
        if (token == operand) {
            printf("%c", symbol);
            fprintf(f2, "%c", symbol);
        } else if (token == rparen) {
            while(stack->top->data != lparen) {
                printToken(pop(stack));
            }
            pop(stack);
        } else {
            while(isp[stack->top->data] >= icp[token]) {
                 printToken(pop(stack));
            }
            push(stack, token);
        }
    }

    while((token = pop(stack)) != eos)
        printToken(token);

    puts("");
}

int calculate(Stack2 *stack2) {
    precedence token;
    char symbol;
    int op1, op2;
    int cnt = -1;  //last symbol counter
    int i = 0;

    token = getToken(&symbol, &cnt, exps_postfix);

    while(token != eos) {
        if (token == operand) {
            printf("%c : push\n", symbol);
            push2(stack2, symbol - '0');
        } else {
            op2 = pop2(stack2);
            op1 = pop2(stack2);

            printf("popx2\n");

            switch(token) {
                case plus:
                    push2(stack2, op1 + op2);
                    break;
                case minus: 
                    push2(stack2, op1 - op2);
                    break;
                case times:
                    push2(stack2, op1 * op2);
                    break;
                case divide: 
                    push2(stack2, op1 / op2);
                    break;
                case mod: 
                    push2(stack2, op1 % op2);
                    break;
                case and:
                    push2(stack2, op1 && op2);
                    break;
                case or:
                    push2(stack2, op1 || op2);
                    break;
                case equal:
                    push2(stack2, op1 == op2);
                    break;
                case not:
                    push2(stack2, op1 != op2);
                    break;
                case over:
                    push2(stack2, op1 > op2);
                    break;
                case less:
                    push2(stack2, op1 < op2);
                    break;
                case eover:
                    push2(stack2, op1 >= op2);
                    break;
                case eless:
                    push2(stack2, op1 <= op2);
                    break;
                default :
                    break;
            }
        }
        token = getToken(&symbol, &cnt, exps_postfix);
    }

    return pop2(stack2);
}