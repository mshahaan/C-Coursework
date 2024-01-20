#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv){

    FILE *train = fopen(argv[1], "r");

    if(train == NULL){ printf("File Error\nTerminating..."); return 0; }

    char* garbage;

    int train_house, train_attr;

    fscanf(train, "%s", garbage);
    fscanf(train, "%d", &train_attr);
    fscanf(train, "%d", &train_house);

    double train_X[train_house][train_attr+1];
    double train_Y[train_house];
    double train_W[train_attr+1];

    int i, j;

    for(i = 0; i < train_house; i++){
        for(j = 0; j <= train_attr; j++){
            if(j == 0){ train_X[i][0] = 1; continue; }
            if(j == train_attr) fscanf(train, "%lf", &train_Y[i]);
            fscanf(train, "%lf ", &train_X[i][j]);
        }
    }

    double train_X_T[train_attr+1][train_house];

    for(i = 0; i <= train_attr; i++){
        for(j = 0; j < train_house; j++){
            train_X_T[i][j] = train_X[j][i];
        }
    }

    double train_X_T_X[train_attr+1][train_attr+1];

    for(i = 0; i <= train_attr; i++){
        for(j = 0; j <= train_attr; j++){
            train_X_T_X[i][j] = 0;
        }
    }

    int k;

    for(i = 0; i <= train_attr; i++){
        for(j = 0; j <= train_attr; j++){
            for(k = 0; k <= train_attr; k++){
                train_X_T_X[i][j] += train_X_T[i][k] * train_X[k][j];
            }
        }
    }

    double inverse[train_attr+1][train_attr+1];
    double temp1[train_attr+1][train_attr+1];
    double temp2[train_attr+1][train_attr+1];

    int a = 0, b = 0, c;

    for(i = 0; i <= train_attr; i++){
        for(j = 0; j <= train_attr; j++){
            for(k = 0; k <= train_attr; k++){
                for(c = 0; c <= train_attr; c++){
                    if(k != i && c != j){
                        temp1[a][b] = train_X_T_X[k][c];
                        //unfinished
                        //lets get a 0 on this shit
                    }
                }
            }
        }
    }

    return 0;

}
