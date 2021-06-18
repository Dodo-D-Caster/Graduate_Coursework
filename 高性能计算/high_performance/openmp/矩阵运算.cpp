//计算 matrix1(A*B) * matrix2(B*C) = matrixAns(A*C)
#include <stdio.h>
#include <omp.h>

#define A 3
#define B 3
#define C 3
#define nThreads 4

//第一个A*B矩阵
int matrix1[A][B] = {
    {1, 2, 3},
    {4, 5, 6},
    {7, 8, 9}};

//第二个B*C矩阵
int matrix2[B][C] = {
    {1, 2, 3},
    {4, 5, 6},
    {7, 8, 9}};

int matrixAns[A][C]; //结果矩阵
int main()
{
    double start, stop;
    omp_set_num_threads(nThreads);
    int temp;
    start = omp_get_wtime();
#pragma omp parallel
    {
#pragma omp for private(temp)
        for (int a = 0; a < A; a++)
        {
            for (int c = 0; c < C; c++)
            {
                temp = 0;
                for (int b = 0; b < B; b++)
                {
                    temp += matrix1[a][b] * matrix2[b][c];
                }
                matrixAns[a][c] = temp;
            }
        }
    }
    stop = omp_get_wtime();
    //输出
    printf("result:\n");
    for (int i = 0; i < A; ++i)
    {
        for (int j = 0; j < C; ++j)
            printf("%d ", matrixAns[i][j]);
        printf("\n");
    }
    printf("time = %lf\n", stop-start);
    return 0;
}