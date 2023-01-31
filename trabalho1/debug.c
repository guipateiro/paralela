#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void foo(int x, int k){
    #pragma omp parallel for private(x) 
    for(int i=1;i<=11;i++) {
        x=i;
        printf("Thread number: %d x: %d\n", omp_get_thread_num(),x);
        foo(x, k+1);
        if (k >= 100)
            exit(1);
    }
}
int main(void) {
//int i;
int x;
x=44;
omp_set_dynamic(0);
omp_set_num_threads(4);
foo(x ,1);

printf("x is %d\n", x);
}