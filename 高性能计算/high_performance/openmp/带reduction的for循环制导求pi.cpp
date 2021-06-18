#include <omp.h>
#include <stdio.h>
static long num_steps = 1000000;
double step;
#define NUM_THREADS 2

int main(int argc, char *argv[])
{
    int i;
    double x = 0.0, pi = 0.0, sum = 0.0;
    double start = 0.0, stop = 0.0;
    step = 1.0 / (double)num_steps;
    omp_set_num_threads(NUM_THREADS);
    start = omp_get_wtime();
#pragma omp parallel for reduction(+ : sum) private(x)
    for (i = 1; i <= num_steps; ++i)
    {
        x = (i - 0.5) * step;
        sum += 4.0 / (1.0 + x * x);
    }
    pi += sum * step;
    stop = omp_get_wtime();
    printf("pi = %lf\ntime = %lf\n", pi, stop-start);
    return 0;
}