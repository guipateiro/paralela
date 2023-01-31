#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define TAM 2048

void imprime_vetor(int rank, int *vetor, int tamanho, char *msg_inicial) {
    int i;
    char *str, strT[20];
    str = (char*)malloc(sizeof(char)*tamanho*20);
    str[0]='\0';
    // Salva o vetor em uma unica string
    for(i=0; i<tamanho; ++i) {
        sprintf(strT, "%d ",vetor[i]);
        strcat(str,strT);
    }

    printf("%s processo %d, vetor: %s\n",msg_inicial,rank,str);
    free(str);
}

int main(int argc, char** argv){
    int i;
    int *vetorTotal, *vetorParte;

     MPI_Init(&argc, &argv);

    int num_proc;
    MPI_Comm_size(MPI_COMM_WORLD, &num_proc);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if(rank == 0) {
        vetorTotal = (int*) malloc(sizeof(int)*TAM);
        for(i=0; i<TAM; ++i)
            vetorTotal[i] = rand()%100;
        imprime_vetor(rank,vetorTotal,TAM, "Vetor total,");
    }

    vetorParte = (int*) malloc(sizeof(int)*TAM/num_proc);
    //imprime_vetor(rank, vetorParte, TAM, "Vetor parte antes do scatter,");

    // Copia o vetor do processo 0 para todos os processos no comunicador MPI_COMM_WORLD
    MPI_Scatter(vetorTotal, TAM/num_proc, MPI_INT, vetorParte, TAM/num_proc, MPI_INT, 0, MPI_COMM_WORLD);
    
    imprime_vetor(rank,vetorParte,TAM/num_proc, "Vetor total,");
    int soma = 0;
    for(int j = 0; j < TAM/num_proc ; j++){
        soma+= vetorParte[j];
    }

    printf("soma parcial do processo %d : %d \n", rank, soma);
    int allsoma = 0;
    MPI_Reduce(&soma, &allsoma, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0)
        printf("a soma de todos os elementos é: %d \n" , allsoma);

    free(vetorParte);
    if(rank == 0)
        free(vetorTotal);
    MPI_Finalize();

}