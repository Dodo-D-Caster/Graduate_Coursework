#include <stdio.h>
#include <mpi.h>
#define n 1024
int main(int argc, char *argv[])
{
    int myrank, nprocs, namelen, i;
    double a[n], b[n];
    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
    for (i = 0; i < n; ++i)
    {
        a[i] = myrank;
        b[i] = 0;
    }
    MPI_Send(a, n, MPI_DOUBLE, (myrank + 1) % nprocs, 99, MPI_COMM_WORLD);
    MPI_Recv(b, n, MPI_DOUBLE, (myrank - 1 + nprocs) % nprocs, 99, MPI_COMM_WORLD, &status);
    printf("b[0]=%f in process %d\n", b[0], myrank);
    MPI_Finalize();
    return 0;
}