#include <stdio.h>
#include <stdlib.h>

int isPrime(int num){

    int a = num-1;

    while(a > 2){

        if (num % a == 0) return 0;

        a--;

    }

    return 1;

}

int main(int argc, char** argv){

    int x = atoi(argv[1]);

    if(x % 2 == 0) printf("2\n");

    int y = 3;

    for(int y = 3; y <= x; y+=2){

        if(x % y == 0 && isPrime(y) == 1) printf("%d\n", y);

    }

    return 0;

}
