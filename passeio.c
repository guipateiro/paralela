#include <stdio.h>
#include <time.h>
#include <omp.h>
#include <stdlib.h>

int xMove[8] = { -2, 1, -1, -2, 2, -1,  1,  2 };
int yMove[8] = { -1, 2,  2,  1, 1, -2, -2, -1 };

int M = 8;
int N = 8;

clock_t start, end;

int treads = 1; 

void print_tabuleiro(int **tabuleiro){
    int i, j;
    for (i=0; i < N; i++){
        for (j=0; j < M; j++)
            printf("%3d ",tabuleiro[i][j]);
        printf("\n");
    }
}

int jogada_valida(int x, int y, int **tabuleiro){
    if (x < 0  || x >= N || y < 0 || y >= M)
        return 0;
    if(tabuleiro[x][y] != 0)
        return 0;
    return 1;
}



int passeio_cavalo_seq2(int **tabuleiro, int x, int y, int jogada){
    if (jogada == N*M){
        #pragma omp critical
        {
        print_tabuleiro(tabuleiro);
        end = clock();
        double cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
        printf("%f seconds\n",cpu_time_used);
        }
        exit(1);
    }            
    for (int i=0;i<8;i++){
        int x2 = x + xMove[i];
        int y2 = y + yMove[i];
        if (jogada_valida(x2,y2, tabuleiro)){
            tabuleiro[x2][y2] = jogada+1;
            //printf("jogada = %i || tread = %i ||  endereco do tabuleiro = %p \n", jogada , omp_get_thread_num(),&tabuleiro);  
            passeio_cavalo_seq2(tabuleiro, x2,y2, jogada+1);
            tabuleiro[x2][y2] = 0;   
        }
    }
    return 0;
}

int **copiamatriz(int **tabuleiro){
    int **tabuleiro2;
     // aloca um vetor de LIN ponteiros para linhas
    tabuleiro2 = malloc (M * sizeof (int*)) ;

    // percorre a matriz
    for (int i=0; i < M; i++){
        tabuleiro2[i] = malloc (N * sizeof (int)) ;
        for (int j=0; j < N; j++)
            tabuleiro2[i][j] = tabuleiro[i][j] ; 
    }               // acesso com sintaxe mais simples
    return tabuleiro2;
}

int passeio_cavalo_par(int **tabuleiro, int x, int y, int jogada){
    #pragma omp parallel firstprivate(tabuleiro, jogada)
    {
    int **tabuleiro2 = copiamatriz(tabuleiro);
    #pragma omp for
    for (int i=0;i<8;i++){
        #pragma omp task firstprivate(tabuleiro2, jogada)
        {
            int x2 = x + xMove[i];
            int y2 = y + yMove[i];
            if (jogada_valida(x2,y2, tabuleiro2)){
                tabuleiro2[x2][y2] = jogada+1;
                printf("jogada = %i || tread = %i || i = %i || endereco do tabuleiro = %p \n", jogada , omp_get_thread_num(), i ,tabuleiro2);
                passeio_cavalo_seq2(tabuleiro2, x2,y2, jogada+1);
                tabuleiro2[x2][y2] = 0;
            }
        }
    }
    // libera a memória da matriz
    for (int i=0; i < N; i++)
        free (tabuleiro2[i]);
    free (tabuleiro2);
    } 
    return 0;
}

int passeio_cavalo_seq(int **tabuleiro, int x, int y, int jogada){
    if (jogada == N*M)
        return 1;
    for (int i=0;i<8;i++){
        int x2 = x + xMove[i];
        int y2 = y + yMove[i];
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

int main(int argc, char** argv){
    int **tabuleiro;
    int x_inicio = 0, y_inicio = 0;
    treads = 1;
    if (argc < 2) {
        fprintf(stderr, "Argumento nao fornecido: processando com 1 thread\n");
    }
    else
        treads = atoi(argv[1]);

    scanf("%d %d %d %d", &N, &M, &x_inicio, &y_inicio);

    double cpu_time_used;
    start = clock();
    
    printf("Resolvendo para N=%d e M=%d\n",N,M);

    omp_set_dynamic(0);
    omp_set_num_threads(treads);


    // aloca um vetor de LIN ponteiros para linhas
    tabuleiro = malloc (M * sizeof (int*)) ;

    // percorre a matriz
    for (int i=0; i < M; i++){
        tabuleiro[i] = malloc (N * sizeof (int)) ;
        for (int j=0; j < N; j++)
            tabuleiro[i][j] = 0 ; 
    }               // acesso com sintaxe mais simples
    tabuleiro[x_inicio][y_inicio] = 1;

    if (passeio_cavalo_seq(tabuleiro, x_inicio, y_inicio, 1))
        print_tabuleiro(tabuleiro);
    else
        printf("Nao existe solucao\n");
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("%f seconds\n",cpu_time_used);
}
