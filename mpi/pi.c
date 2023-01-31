#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//compilar com mpicc pi.c -o teste
//executar com mpirun --host 'localhost:20' -np 10 ./teste (np é o numero de processos)

#define TAM 100000000

int main(int argc, char** argv){
    int i;
    double Total = 0;

    MPI_Init(&argc, &argv);

    int num_proc;
    MPI_Comm_size(MPI_COMM_WORLD, &num_proc);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    printf("o rank do processo é %d \n", rank);
    
    double Parte = 0;
    for(long j = rank*(TAM/num_proc); j < (rank+1)*(TAM/num_proc); ++j){
        if(j%2 == 0){
            Parte+= (double)1/(2*j+1);
        }else{
            Parte-= (double)1/(2*j+1);
        }
    }

    printf("valor de parte no processo %d é : %0.20f \n", rank, Parte);
    MPI_Reduce(&Parte, &Total, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);



    if (rank == 0)
        printf("O aalor de pi é: %0.20f \n" , 4*Total);

    MPI_Finalize();

}