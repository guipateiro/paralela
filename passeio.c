#include <stdio.h>
#include <time.h>
#include <omp.h>
#include <stdlib.h>
#include "passeio.h"

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

int passeio_cavalo_seq(int tabuleiro[N][M], int x, int y, int jogada){
    int x2, y2;
    if (jogada == N*M)
        return 1;
    for (int i=0;i<8;i++){
        x2 = x + xMove[i];
        y2 = y + yMove[i];
        if (jogada_valida(x2,y2, tabuleiro)){
            tabuleiro[x2][y2] = jogada+1;
            //printf("jogada = %i || tread = %i \n", jogada , omp_get_thread_num());
            if((M*N)/2 == jogada){
                if (!passeio_cavalo_par(tabuleiro, x2,y2, jogada+1))
                    tabuleiro[x2][y2] = 0;
            }else{
                if (!passeio_cavalo_seq(tabuleiro, x2,y2, jogada+1) )
                    tabuleiro[x2][y2] = 0;
            }
        }
    }    
    return 0;
}

int passeio_cavalo_seq2(int tabuleiro[N][M], int x, int y, int jogada){
    int x2, y2;
    if (jogada == N*M)
        return 1;
    for (int i=0;i<8;i++){
        x2 = x + xMove[i];
        y2 = y + yMove[i];
        if (jogada_valida(x2,y2, tabuleiro)){
            tabuleiro[x2][y2] = jogada+1;
            //printf("jogada = %i || tread = %i ||  endereco do tabuleiro = %p \n", jogada , omp_get_thread_num(),&tabuleiro);  
            if (passeio_cavalo_seq2(tabuleiro, x2,y2, jogada+1) ){
                for (int j=0; j < N; j++){
                    for (int k =0; k < M; k++)
                        printf("%3d ",tabuleiro[j][k]);
                    printf("\n");
                }
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

int passeio_cavalo_par(int tabuleiro[N][M], int x, int y, int jogada){
    #pragma omp parallel firstprivate(tabuleiro, jogada)
    {
    #pragma omp for
    for (int i=0;i<8;i++){
        int x2 = x + xMove[i];
        int y2 = y + yMove[i];
        if (jogada_valida(x2,y2, tabuleiro)){
            tabuleiro[x2][y2] = jogada+1;
            printf("jogada = %i || tread = %i || i = %i || endereco do tabuleiro = %p \n", jogada , omp_get_thread_num(), i ,&tabuleiro);
            if (!passeio_cavalo_seq2(tabuleiro, x2,y2, jogada+1) )
                tabuleiro[x2][y2] = 0;
        }
    }
    #pragma omp barrier
    }
    return 0;
}



int main(int argc, char** argv){
    int i, j;
    int tabuleiro[N][M];
    int x_inicio = 0, y_inicio = 0;
    int treads = atoi(argv[1]);
    double cpu_time_used;
    start = clock();
    
    printf("Resolvendo para N=%d e M=%d\n",N,M);

    for (i=0; i < N; i++)
        for (j=0; j < M; j++)
            tabuleiro[i][j] = 0;

    tabuleiro[x_inicio][y_inicio] = 1;
    omp_set_dynamic(1);
    omp_set_num_threads(treads);

    if (passeio_cavalo_seq(tabuleiro, x_inicio, y_inicio, 1))
        print_tabuleiro(tabuleiro);
    else
        printf("Nao existe solucao\n");
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("%f seconds\n",cpu_time_used);
}
