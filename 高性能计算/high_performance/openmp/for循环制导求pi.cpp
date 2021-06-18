#include <omp.h>
#include <stdio.h>
static long num_steps = 1000000;
double step;
#define NUM_THREADS 4

int main(int argc, char *argv[])
{
    int i, id;
    double x, pi, sum[NUM_THREADS];
    double start = 0.0, stop = 0.0;
    step = 1.0 / (double)num_steps;
    omp_set_num_threads(NUM_THREADS);
    start = omp_get_wtime();
#pragma omp parallel private(x, id)
    {
        id = omp_get_thread_num();
        sum[id] = 0;
#pragma omp for
        for (i = 0; i <= num_steps; ++i)
        {
            x = (i + 0.5) * step;
            sum[id] += 4.0 / (1.0 + x * x);
        }
    }
    for (i = 0, pi = 0.0; i < NUM_THREADS; ++i)
        pi += sum[i] * step;
    stop = omp_get_wtime();
    printf("pi = %lf\ntime = %lf\n", pi, stop-start);
    return 0;
}