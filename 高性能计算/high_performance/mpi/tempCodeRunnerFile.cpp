#include <stdio.h>
#include <mpi.h>
const int n = 1000000;
int main(int argc, char *argv[])
{
    int my_rank, num_procs;
    long i;
    double w, local, mypi = 0.0, pi;
    double start = 0.0, stop = 0.0;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    if (my_rank == 0)
        start = MPI_Wtime();
    w = 1.0 / n;
    for (i = my_rank; i < n; i += num_procs)
    {
        local = (i + 0.5) * w;
        mypi += 4.0 / (1.0 + local * local);
    }
    mypi *= w;
    MPI_Reduce(&mypi, &pi, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    if (my_rank == 0)
    {
        printf("PI is %f\n", pi);
        stop = MPI_Wtime();
        printf("Time:%f\n", stop - start);
        fflush(stdout); //清空缓冲区
    }
    MPI_Finalize();
    return 0;
}
