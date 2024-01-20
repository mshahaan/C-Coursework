#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char** argv){

    char originalString[50] = ""; char* temp = argv[1]; strcat(originalString, temp);

    char result[50] = "";

    int originalLength = strlen(temp);

    int i;

    for (i = 0; i < originalLength; i++){
        if(isdigit(originalString[i])){ printf("error\n"); return 0; }
    }

    int s;

    for (s = 0; s < originalLength; s++){
        char tmpc = originalString[s];

        char tmps[2]; tmps[0] = tmpc; tmps[1] = '\0';

        strcat(result, tmps);

        int x = 1;

        while (s < originalLength){
            if(originalString[s] == originalString[s+1]){
                x++; s++;
            }
            else break;
        }

        char num[12];
        sprintf(num, "%d", x);
        strcat(result, num);
    }

    int newLength = strlen(result);

    if(newLength > originalLength) printf("%s\n", originalString);
    else printf("%s\n", result);

    return 0;

}
