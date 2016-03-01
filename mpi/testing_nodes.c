#include <stdio.h>
#include "mpi.h"

int main(int argc, char* argv[])
{
    MPI_Status status; 
    int my_rank;
    MPI_Comm solverComm;
    int p;
    
    MPI_Init(&argc, &argv);
    MPI_Comm_dup(MPI_COMM_WORLD, &solverComm);
    MPI_Comm_size(solverComm, &p);
    MPI_Comm_rank(solverComm, &my_rank);

    if (my_rank == 4) {
	  int q;
	  fprintf(stderr, "Testing process 4 receive\n");
	  MPI_Recv(&q, 1, MPI_INT, 3, 0, solverComm, &status);
	  fprintf(stderr, "$$$$$$$$$$$$$ process %d, q = %d\n", my_rank, q);
    }
    if(my_rank ==3) {
        fprintf(stderr, "Testing send from process 3\n");
        MPI_Send(&my_rank, 1, MPI_INT, 4, 0, solverComm);
    }
    
}

