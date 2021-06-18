#include <omp.h>
#include <iostream>
#include <stdio.h>
int main(int argc, char *argv[])
{
    int nthreads, tid;
    int nprocs;
    char buf[32];
    omp_set_num_threads(4);
#pragma omp parallel private(nthreads, tid)
    {
        
        tid = omp_get_thread_num();
        printf("Hello world from OpenMP thread %d\n", tid);
        if (tid == 0)
        {
            nthreads = omp_get_num_threads();
            printf("Number of threads %d\n", nthreads);
        }
    }
    return 0;
}