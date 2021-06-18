#include <stdio.h>
#include <mpi.h>
const int n = 10;
int main(int argc, char *argv[])
{
    int a[n]={0}, b=0, myrank, nprocs;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
    if (myrank == 0){
        for(int i=0; i<n; ++i)
            a[i] = i;
    }
    MPI_Scatter(a, 1, MPI_INT, &b, 1, MPI_INT, 0, MPI_COMM_WORLD);
    printf("%d processor's b is %d\n", myrank, b);
    MPI_Finalize();
    return 0;
}