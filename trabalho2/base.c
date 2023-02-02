#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

void read_serie(char * arquivo, double *vetor, int tamanho){
    FILE *fp = fopen(arquivo, "r");
     double max = 0 , min = 0 , media;
     double soma = 0;
    if(fp==NULL){
        fprintf(stderr, "não foi possivel abrir o arquivo %s\n", arquivo);
        exit(1);
    }
    for(int i=0; i<tamanho; ++i){
        fscanf(fp, "%lf", &vetor[i]);
        soma += vetor[i];
        if (vetor[i] > max)
            max = vetor[i];
        if (vetor[i] < min)
            min = vetor[i];
    }
     media = soma / tamanho;
     printf("serie total - max: %lf, min: %lf, media: %lf\n", max, min, media);
}

void max_min_avg(double *vetor, int tamanho, double *max, double *min, double *media){
    double soma = 0;
    *max = *min = vetor[0];
    for(int i=0; i< tamanho; i++){
        soma += vetor[i];
        if (vetor[i] > *max)
            *max = vetor[i];
        if (vetor[i] < *min)
            *min = vetor[i];
    }
    *media = soma / tamanho;
}

int main(int argc, char **argv){
    double *serie;
    double *vet_parcial;

    if (argc != 4){
        fprintf(stderr, "necessário 2 argumentos: %s <arquivo time series> <tamanho time series> <tamanho janela>\n", argv[0]);
        return 1;
    }
    int tam_serie = atoi(argv[2]);
    int tam_janela = atoi(argv[3]);


    MPI_Init(&argc, &argv);

    int num_proc;
    MPI_Comm_size(MPI_COMM_WORLD, &num_proc);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if(rank == 0){
        serie = (double *) malloc(sizeof(double)*tam_serie);
        read_serie(argv[1], serie, tam_serie);
        printf("tamanho da serie: %d, tamanho da janela: %d\n",tam_serie, tam_janela);

    }
    vet_parcial = (double*) malloc((tam_serie/num_proc  + 1) * sizeof(double));
    MPI_Scatter(serie, tam_serie/num_proc, MPI_DOUBLE, vet_parcial, tam_serie/num_proc, MPI_DOUBLE, 0, MPI_COMM_WORLD);



    double max, min, media;
    printf("numero de janelas: %i\n",((tam_serie/num_proc) - tam_janela));
    for(int i = 0; i <= ((tam_serie/num_proc) - tam_janela); i++){
        max_min_avg(&vet_parcial[i],tam_janela, &max, &min, &media);
        printf("janela %d - max: %lf, min: %lf, media: %lf\n", i, max, min, media);
    }

    free(vet_parcial);
    if(rank == 0){
        free(serie);
    }    
    MPI_Finalize();
    return 0;
}
