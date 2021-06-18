#include <stdio.h>
#include <omp.h>
#define N 100000
const int numthreads = 4;
int main()
{
    double pi, sum[numthreads];
    int i;
    double step = 1.0 / (double)N;
    omp_set_num_threads(numthreads);
#pragma omp parallel private(i)
    {
        int id = omp_get_thread_num();
        sum[id] = 0;
#pragma omp for
            for (i = 0; i < N; ++i)
        {
            double x = (i + 0.5) * step;
            sum[id] += 4.0 / (1.0 + x * x);
        }
    }
    for (i = 0; i < numthreads; ++i)
    {
        pi += sum[i] * step;
    }
    printf("%lf", pi);
    return 0;
}