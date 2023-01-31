#include <mpi.h>
#include <stdio.h>

#define TAM 1024 


int main(){
    double *A;
    double *B;
    
    MPI_Init(&argc, &argv);

    int num_proc;
    MPI_Comm_size(MPI_COMM_WORLD, &num_proc);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

     if(rank == 0) {
        A = (int*) malloc(sizeof(double)*TAM);
        B = (int*) malloc(sizeof(double)*TAM);
        for(int i=0; i<TAM; ++i){
            A[i] = rand()%100;
            B[i] = rand()%100;
        }
        //imprime_vetor(rank,vetorTotal,TAM, "Vetor total,");
    }
    double *Aparcial = (double*) malloc(sizeof(double)*TAM/num_proc);
    double *Bparcial = (double*) malloc(sizeof(double)*TAM/num_proc);
    MPI_Scatter(A, TAM/num_proc, MPI_DOUBLE, Aparcial, TAM/num_proc, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Scatter(B, TAM/num_proc, MPI_DOUBLE, Bparcial, TAM/num_proc, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    double somaparcial = 0;
    double Asomaparcial = 0;
    double Bsomaparcial = 0;

    for(int i = 0; i < TAM/num_proc; i++){
        somaparcial+= Bparcial[i]*Aparcial[i];
        Asomaparcial+= Aparcial[i]*Aparcial[i];
        Bsomaparcial+= Bparcial[i]*Bparcial[i];
    }

    MPI_Reduce(&soma, &somaparcial, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    MPI_Reduce(&soma, &Asomaparcial, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    MPI_Reduce(&soma, &Bsomaparcial, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    //vetores A e B 

    //A * B 
    //-----
    //|A| *|B|

    //A*B = a1*b1 + a2 *b2 + ... + an*bn 

    //|A| = sqrt (a1*a1 + a2*a2 + ... ) 
    //idem para o B

    //passar pedacos de ambos os vetores

    //calcular as parciais

    //reduce com MPI_SUM    

    //FAZER OS CALCULOS FINAIS



}






