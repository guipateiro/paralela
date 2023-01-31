#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define A 100

int main(){
    long tam = 0;
    scanf("%li",&tam);
    srand((unsigned int)time(NULL));

    for (int i = 0; i < tam; i++){
        printf("%f\n", ((float)rand()/(float)(RAND_MAX)) * A);
    }
    
}