#include <stdio.h>
#include <time.h>
#include <omp.h>
#include <stdlib.h>


#define N 5
#define M 5

int xMove[8] = { 2, 1, -1, -2, -2, -1, 1, 2 };
int yMove[8] = { 1, 2, 2, 1, -1, -2, -2, -1 };

clock_t start, end;

void print_tabuleiro(int tabuleiro[N][M]){
    int i, j;
    for (i=0; i < N; i++){
        for (j=0; j < M; j++)
            printf("%3d ",tabuleiro[i][j]);
        printf("\n");
    }
}

int jogada_valida(int x, int y, int tabuleiro[N][M]){
    if (x < 0  || x >= N || y < 0 || y >= M)
        return 0;
    if(tabuleiro[x][y] != 0)
        return 0;
    return 1;
}

int passeio_cavalo(int tabuleiro[N][M], int x, int y, int jogada){
   
    if (jogada == N*M)
        return 1;
    int i;    
    #pragma omp parallel for firstprivate(tabuleiro, jogada) num_threads(4)
    for (i=0;i<8;i++){
        //if (omp_get_num_threads() == 1){
        //    perror("treds nao incializadas");
        //    exit(-1);
       // }
        int x2, y2;
        x2 = x + xMove[i];
        y2 = y + yMove[i];
        if (jogada_valida(x2,y2, tabuleiro)){
            tabuleiro[x2][y2] = jogada+1;
            printf("jogada = %i || tread = %i \n", jogada , omp_get_thread_num());
            if (/*omp_get_thread_num() != 0 &&*/ passeio_cavalo(tabuleiro, x2,y2, jogada+1) ){
                print_tabuleiro(tabuleiro);
                end = clock();
                double cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
                printf("%f seconds\n",cpu_time_used);
                exit(1);
            }
                
            tabuleiro[x2][y2] = 0;
        }
    }

    return 0;
}

int main(){
    int i, j;
    int tabuleiro[N][M];
    int x_inicio = 0, y_inicio = 0;
    
    double cpu_time_used;
    start = clock();
    
    printf("Resolvendo para N=%d e M=%d\n",N,M);

    for (i=0; i < N; i++)
        for (j=0; j < M; j++)
            tabuleiro[i][j] = 0;

    tabuleiro[x_inicio][y_inicio] = 1;
    if (passeio_cavalo(tabuleiro, x_inicio, y_inicio, 1))
        print_tabuleiro(tabuleiro);
    else
        printf("Nao existe solucao\n");
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("%f seconds\n",cpu_time_used);
}
