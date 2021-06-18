#include <stdio.h>
#include <mpi.h>
#include <omp.h>
static long num_steps = 1000000;
double step;
#define NUM_THREADS 2
// const int n = 1000000;
int main(int argc, char *argv[])
{
    int myrank, nprocs;
    long i;
    double mypi = 0.0, x = 0.0, pi = 0.0, sum = 0.0;
    double start, stop;
    step = 1.0 / (double)num_steps;
    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
    omp_set_num_threads(NUM_THREADS);
    start = omp_get_wtime();
#pragma omp parallel for reduction(+ : sum) private(x)
    for (i = 1; i <= num_steps; ++i)
    {
        x = (i - 0.5) * step;
        sum += 4.0 / (1.0 + x * x);
    }

    pi += sum * step;

    MPI_Send(&pi, 1, MPI_DOUBLE, (myrank + 1) % nprocs, 99, MPI_COMM_WORLD);
    MPI_Recv(&mypi, 1, MPI_DOUBLE, (myrank - 1 + nprocs) % nprocs, 99, MPI_COMM_WORLD, &status);
    stop = omp_get_wtime();
    // if (myrank == 0)
    printf("PI = %lf\ntime = %lf\n", pi, stop-start);

    MPI_Finalize();
    return 0;
}
