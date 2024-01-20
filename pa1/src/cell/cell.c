#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int table[8][3] = {
        {0,0,0},
        {0,0,1},
        {0,1,0},
        {0,1,1},
        {1,0,0},
        {1,0,1},
        {1,1,0},
        {1,1,1},
    };

void print_line(int output[], int size){

    int a;

    for(a = 0; a < size; a++){
        if(output[a] == 1) printf("*");
        else if (output[a] == 0) printf(".");
    }

    printf("\n");

}

int main(){

    int size, inputIteration, ops;

    int given = 0;

    char *initialState = malloc(100*sizeof(char));
    char *rule = malloc(100*sizeof(char));
    char *temp = malloc(100*sizeof(char));

    inputIteration = 1;

    while(scanf("%s", temp) != EOF){

        if(inputIteration == 1) size = atoi(temp);
        else if(inputIteration == 2) ops = atoi(temp);
        else if(inputIteration == 3) strcpy(rule, temp);
        else if(inputIteration == 4){ strcpy(initialState, temp); given = 1; break; }
        inputIteration++;
    }

    free(temp);

    int output[size];

    if(given){
        int length = strlen(initialState);
        int i;
        for(i = 0; i < size; i++){
            if(i >= length){
                output[i] = 0;
                continue;
            }
            if(initialState[i] == '*'){
                output[i] = 1;
                continue;
            }
            if(initialState[i] == '.'){
                output[i] = 0;
                continue;
            }
        }
        free(initialState);
    }
    else{
        free(initialState);
        int half = size / 2;
        int i;
        for(i = 0; i < size; i++){
            if(i == half) output[i] = 1;
            else output[i] = 0;
        }
    }

    if(ops == 1){

        print_line(output, size);

        return 0;

    }

    int count;

    int next[3]; int tmp[size];

    int f;
    for(f = 0; f < size; f++){
        tmp[f] = output[f];
    }

    print_line(output, size);

    for(count = 0; count < ops; count++){

        int i;

        for(i = 0; i < size; i++){
            if(i == 0){
                next[0] = tmp[size-1];
                next[1] = tmp[0];
                next[2] = tmp[1];
                int l; int L;
                for(l = 0; l < 8; l++){
                    if(next[0] == table[l][0] && next[1] == table[l][1] && next[2] == table[l][2]){ L = l; break; }
                }
                if(rule[L] == '*') output[0] = 1;
                else output[0] = 0;
            }
            else if (i == size - 1){
                next[0] = tmp[size-2];
                next[1] = tmp[size-1];
                next[2] = tmp[0];
                int l; int L;
                for(l = 0; l < 8; l++){
                    if(next[0] == table[l][0] && next[1] == table[l][1] && next[2] == table[l][2]){ L = l; break; }
                }
                if(rule[L] == '*') output[size-1] = 1;
                else output[size-1] = 0;
            }
            else{
                next[0] = tmp[i-1];
                next[1] = tmp[i];
                next[2] = tmp[i+1];
                int l; int L;
                for(l = 0; l < 8; l++){
                    if(next[0] == table[l][0] && next[1] == table[l][1] && next[2] == table[l][2]){ L = l; break; }
                }
                if(rule[L] == '*') output[i] = 1;
                else output[i] = 0;
            }
        }

        for(f = 0; f < size; f++){

            tmp[f] = output[f];

        }

        print_line(output, size);

    }

    free(rule);

    return 0;

}
