#include<stdio.h>

#include<mpi.h>

int main(int arc, char** arv)
{

	int rank, num_process;

	MPI_Init(NULL, NULL);

	MPI_Comm_size(MPI_COMM_WORLD, &num_process);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	
	printf("Total number of process %d\n", num_process);


	
	printf("rank is - %d", rank);

	MPI_Finalize();

}