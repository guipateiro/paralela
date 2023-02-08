#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <mpi.h>

void read_serie(char * arquivo, double *vetor, int tamanho){
    FILE *fp = fopen(arquivo, "r");
     double max = 0 , min = 100 , media;
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
    // printf("serie total - max: %lf, min: %lf, media: %lf\n", max, min, media);
	fclose(fp);
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
        fprintf(stderr, "necessário 3 argumentos: %s <arquivo time series> <tamanho time series> <tamanho janela>\n", argv[0]);
        return 1;
    }

    int tam_serie = atoi(argv[2]);
    int tam_janela = atoi(argv[3]);

	if (tam_janela > tam_serie){
		 fprintf(stderr, "tamanho de janela nao pode ser maior que o tamanho da serie\n");
		return 1;
	}

   	struct timeval inicio, fim;
	gettimeofday(&inicio, NULL);

    MPI_Init(&argc, &argv);

    int num_proc;
    MPI_Comm_size(MPI_COMM_WORLD, &num_proc);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if(rank == 0){
        serie = (double *) calloc(tam_serie + tam_janela, sizeof(double));
        read_serie(argv[1], serie, tam_serie);
        //printf("tamanho da serie: %d, tamanho da janela: %d\n",tam_serie, tam_janela);

    }
    vet_parcial = (double*) malloc((tam_serie/num_proc + tam_serie) * sizeof(double));

	if (rank == 0) {
        for(int i=1; i < num_proc; ++i) {
            	MPI_Send(&serie[(i*(tam_serie/num_proc))], (tam_serie/num_proc) + tam_janela , MPI_DOUBLE, i, 0, MPI_COMM_WORLD);
        }
		double max, min, media;
		for(int i = 0; (i <= tam_serie/num_proc) && (((rank*(tam_serie/num_proc)) + i + tam_janela) < tam_serie) ; i++){
       		max_min_avg(&serie[i],tam_janela, &max, &min, &media);
       		//printf("janela %d - max: %lf, min: %lf, media: %lf\n", i, max, min, media);
    	}
    }
    else {
    	double max, min, media;
        MPI_Recv(vet_parcial,tam_serie/num_proc + tam_serie , MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        for(int i = 0; (i <= tam_serie/num_proc) && (((rank*(tam_serie/num_proc)) + i + tam_janela) < tam_serie) ; i++){
       		max_min_avg(&vet_parcial[i],tam_janela, &max, &min, &media);
       		//printf("janela %d - max: %lf, min: %lf, media: %lf\n", i, max, min, media);
    	}
		free(vet_parcial);
    }

    if(rank == 0){
        free(serie);
    } 

	MPI_Barrier(MPI_COMM_WORLD);
	if (rank == 0) {
		gettimeofday(&fim, NULL);
		double tempo_exec;
  
    	tempo_exec = (fim.tv_sec - inicio.tv_sec) * 1e6;
    	tempo_exec = (tempo_exec + (fim.tv_usec - 
                              inicio.tv_usec)) * 1e-6;
   		printf("%f\n",tempo_exec);
	}	
    MPI_Finalize();

	return 0;
}
