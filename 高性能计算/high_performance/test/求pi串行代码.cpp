#include <cstdio>
#define n 100000
int main()
{
    double pi = 0;
    double step = 1.0 / (double)n;
    for (int i = 0; i < n; ++i)
    {
        double x = (i + 0.5) * step;
        pi += 4.0 / (1 + x * x);
    }
    printf("%.8f", pi * step);
}