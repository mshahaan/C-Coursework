#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char** argv){

    int x, y;

    char result[1000] = "";

    int s;

    for(s = 1; s < argc; s++){

        strcat(result, argv[s]); strcat(result, " ");

    }

    int f;

    for(f = 0; f < strlen(result); f++){

        if (isalpha(result[f]) == 0) continue;

        if (result[f] >= 'A' && result[f] <= 'Z'){ x = 1; y = f; break; }
        else{ x = 0; y = f; break; }

    }

    if(x == 1){

        x = 0; int i;

        for(i = y+1; i < strlen(result); i++){

            if (isalpha(result[i]) == 0) continue;

            if(x == 0){
                x = 1;
            }
            else if(x == 1){

                if (result[i] >= 'a' && result[i] <= 'z'){

                    if(isalpha(result[i-1]) == 0){
                        int u = i-2;
                        for(u = i - 2; u >= 0; u--){
                            if(isalpha(result[u])) break;
                        }
                        if (isalpha(result[u]) && result[u] >= 'a' && result[u] <= 'z'){
                            result[i] = result[i] - 32;
                        }
                    }
                    else if (result[i-1] >= 'a' && result[i-1] <= 'z') result[i] = result[i] - 32;
                }

                x = 0;
            }
        }

    }
    else if(x == 0){

        x = 1; int l;

        for(l = y+1; l < strlen(result); l++){

            if (isalpha(result[l]) == 0) continue;

            if(x == 1){

                if(isalpha(result[l-1]) == 0){
                        int u =l-2;
                        for(u = l-2; u >= 0; u--){
                            if(isalpha(result[u])) break;
                        }
                        if (isalpha(result[u]) && result[u] >= 'a' && result[u] <= 'z'){
                            result[l] = result[l] - 32;
                        }
                    }
                else if (result[l-1] >= 'a' && result[l-1] <= 'z') result[l] = result[l] - 32;
                x = 0;
            }
            else if(x == 0){
                x = 1;
            }
        }

    }

    printf("%s", result); printf("\n");

    return 0;

}
