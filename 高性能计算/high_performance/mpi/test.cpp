//由高数里的知识可知，根据上述公式可以求得pi/4。
#include <stdio.h>
#include <mpi.h>
const int n = 1000000;
int main(int argc, char *argv[])
{
    int my_rank, num_procs;
    long i;
    double sum, w, local, mypi = 0.0, pi;
    double start = 0.0, stop = 0.0;
    int proc_len;
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Get_processor_name(processor_name, &proc_len);
    printf("Process %d of %d\n", my_rank, num_procs);
    if (my_rank == 0)
    {
        start = MPI_Wtime();
    }
    w = 1.0 / n;
    for (i = my_rank; i < n; i += num_procs)
    {
        local = (i + 0.5) * w;
        mypi += 4.0 / (1.0 + local * local);
    }
    mypi *= w;
    MPI_Send(&mypi, n, MPI_DOUBLE, (my_rank + 1) % num_procs, 99, MPI_COMM_WORLD);
    if(my_rank % num_procs == 0){
        MPI_Recv(&pi, n, MPI_DOUBLE, (my_rank - 1 + num_procs) % num_procs, 99, MPI_COMM_WORLD, &status);
        pi += mypi;
        printf("PI is %.20f\n on %d line", pi, my_rank);
        stop = MPI_Wtime();
        printf("Time:%f on %s\n", stop - start, processor_name);
        // fflush(stdout); //清空缓冲区
    }
    MPI_Finalize();
    return 0;
}
