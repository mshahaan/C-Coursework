#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int main(int argc, char** argv){

    FILE *fp = fopen(argv[1], "r");

    if(fp == NULL){ printf("File Error.\nTerminating..."); return 0;}

    int dim;

    fscanf(fp, "%d", &dim);

    if(dim == 0){
        printf("0\n");
        fclose(fp);
        return 0;
    }

    if(dim == 1){
        int x;
        fscanf(fp, "%d", &x);
        int exp;
        fscanf(fp, "%d", &exp);
        int result = x;
        int i;
        for (i = 1; i < exp; i++){
            result = result * x;
        }
        printf("%d\n", result);
        fclose(fp);
        return 0;
    }

    int matrix[dim][dim];
    int i, j;

    for(i = 0; i < dim; i++){
        for(j = 0; j < dim; j++){
            int temp;
            fscanf(fp, "%d ", &temp);
            matrix[i][j] = temp;
        }
    }

    int exp;

    fscanf(fp, "%d", &exp);

    if(exp == 0){
        for(i = 0; i < dim; i++){
            for(j = 0; j < dim; j++){
                if(i == j) matrix[i][j] = 1;
                else matrix[i][j] = 0;
            }
        }
        for(i = 0; i < dim; i++){
            for(j = 0; j < dim; j++){
                printf("%d ", matrix[i][j]);
            }
            printf("\n");
        }
        return 0;
    }

    if(exp == 1){
        for(i = 0; i < dim; i++){
            for(j = 0; j < dim; j++){
                if(j == dim-1) printf("%d", matrix[i][j]);
                else printf("%d ", matrix[i][j]);
            }
            printf("\n");
        }
        return 0;
    }

    int mexp[dim][dim];

    int firstMultiplication = 1;

    int e = 1;

    while(e < exp){

        int tempResult[dim][dim];

        for(i = 0; i < dim; i++){
            for(j = 0; j < dim; j++){
                tempResult[i][j] = 0;
            }
        }

        int a, b, c;

        if(firstMultiplication == 1){
            firstMultiplication = 0;
            for(a = 0; a < dim; a++){
                for(b = 0; b < dim; b++){
                    for(c = 0; c < dim; c++){
                        tempResult[a][b] += matrix[a][c] * matrix[c][b];
                    }
                }
            }
        }
        else{
            for(a = 0; a < dim; a++){
                for(b = 0; b < dim; b++){
                    for(c = 0; c < dim; c++){
                        tempResult[a][b] += mexp[a][c] * matrix[c][b];
                    }
                }
            }
        }

        memcpy(mexp, tempResult, sizeof(mexp));

        e++;
    }

    for(i = 0; i < dim; i++){
        for(j = 0; j < dim; j++){
            if(j == dim-1) printf("%d", mexp[i][j]);
            else printf("%d ", mexp[i][j]);
        }
        printf("\n");
    }

    fclose(fp);

    return 0;

}
