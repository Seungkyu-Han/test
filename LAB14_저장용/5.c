#include <stdio.h>
#include <stdlib.h>

int findRoot(int *eqv, int i);
void process(int *arr, int a, int b);

int main(){
    int arr[30];

    for(int i = 0; i < 30; i++){
        arr[i] = 31;
    }

    FILE *f = fopen("input.txt", "r");
    int n;
    fscanf(f, "%d", &n);

    for(int i = 0; i < n; i++){
        int a, b;
        fscanf(f, "%d = %d,", &a, &b);
        process(arr, a, b);
    }

    int cnt = 0;
    for(int i = 0; i < 30; i++){
        if(arr[i] < 0){
            cnt++;
        }
    }

    f = fopen("output.txt", "w");
    if (f == NULL) exit(1);

    fprintf(f, "%d\n", cnt);

    int bracketNum = 0;

    for(int i = 0; i < 30; i++){
        if(arr[i] < 0){
            fprintf(f, "{%d", i);
            for(int j = 0; j < 30; j++){
                if(findRoot(arr, j) == i && j != i){
                    fprintf(f, ", %d", j);
                }
            }
            fprintf(f, "}");
            bracketNum++;
            if (bracketNum < cnt) fprintf(f, ", ");
        }
    }
}

void process(int *arr, int a, int b) {
    if(arr[a] == 31){
        arr[a] = -1;
    }

    if(arr[b] == 31){
        arr[b] = -1;
    }

    if(arr[b] < arr[a]){
        arr[a] = b;
        arr[b]--;
    }
    else if(arr[b] >= 0 && arr[a] < 0){
        arr[a] = findRoot(arr, b);
        arr[findRoot(arr, b)]--;
    }
    else if(arr[b] >= arr[a]){
        arr[b] = a;
        arr[a]--;
    }
    else if(arr[b] < 0 && arr[a] >= 0){
        arr[b] = findRoot(arr, a);
        arr[findRoot(arr, a)]--;
    }

}

int findRoot(int *eqv, int child){
    while(child != 31 && eqv[child] >= 0){
        child = eqv[child];
    }
    return child;
}




