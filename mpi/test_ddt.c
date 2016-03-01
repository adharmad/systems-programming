#include <stdio.h>
#include "mpi.h"

#define MAX 100

int main(int argc, char* argv[])
{
    MPI_Status status; 
    int my_rank;
    MPI_Comm solverComm;
    int p;
    int sendCount, recvCount;
    int blocks = 2;
    MPI_Datatype indexSendCheck; 
    MPI_Datatype indexRecvCheck;  
    int * x;
    int *y;
    int disp[2];
    int blocklen[2];
    
    disp[0] = 0;
    disp[1] = 1;

    blocklen[0] = 1;
    blocklen[1] = 1;
    
    x = (int *)malloc(sizeof(int) * MAX);
    y = (int *)malloc(sizeof(int) * MAX);    

    x[0] = 10;
    x[1] = 20;

    y[0] = 0;
    y[1] = 0;
    
    MPI_Init(&argc, &argv);
    MPI_Comm_dup(MPI_COMM_WORLD, &solverComm);
    MPI_Comm_size(solverComm, &p);
    MPI_Comm_rank(solverComm, &my_rank);

    if (my_rank == 0) {
        MPI_Type_indexed(blocks, blocklen, disp, MPI_INT, &indexSendCheck);
        MPI_Type_commit(&indexSendCheck);
    }

    if (my_rank == 1) {
        MPI_Type_indexed(blocks, blocklen, disp, MPI_INT, &indexRecvCheck);
        MPI_Type_commit(&indexRecvCheck);
    }
    
    
    if (my_rank == 1) {
        int q;
        fprintf(stdout, "Testing process 4 receive\n");
        MPI_Recv(y, 1, indexRecvCheck, 0, 0, solverComm, &status);         
        fprintf(stdout, "In process %d after receive\n", my_rank);            
        /*
              fprintf(stderr, "Testing process 4 receive\n");
	  MPI_Recv(&q, 1, MPI_INT, 3, 0, solverComm, &status);
	  fprintf("In process %d, q = %d\n", my_rank, q);*/
    }
    if(my_rank ==0) {
        fprintf(stdout, "Testing send from process 3\n");
        MPI_Send(x, 1, indexSendCheck, 1, 0, solverComm);
        fprintf(stdout, "after send from process 3\n");       
        /*
          fprintf(stderr, "Testing send from process 3\n");
          MPI_Send(&my_rank, 1, MPI_INT, 4, 0, solverComm);*/
    }
    
    
   free(x);
   free(y);
    
    MPI_Finalize();
}

