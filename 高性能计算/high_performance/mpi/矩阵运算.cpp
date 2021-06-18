#include <stdlib.h>
#include <stdio.h>
// #include <omp.h>
#include <mpi.h>

#define A 3
#define B 3
#define C 3

int mat1[A][B];    //第一个A*B矩阵
int mat2inv[C][B]; //第二个B*C矩阵的转置（转置是为了更高的baicache hit rate）
int matret[A][C];  //保存结果的矩阵
int nThreads = 4;
int main(int argc, char *argv[])
{
    printf("请输入第一个矩阵：\n");
    for (int i = 0; i < A; ++i)
        for (int j = 0; j < B; ++j)
            scanf("&d", mat1[i][j]);
    printf("请输入第二个矩阵：\n");
    for (int i = 0; i < C; ++i)
        for (int j = 0; j < B; ++j)
            scanf("%d", mat2inv[i][j]);

    //计算
    int myrank, numprocs;
    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);

    int temp;
    //针对第一个矩阵的行并行
    for (int a = 0; a < A; a++)
    {
        for (int c = 0; c < C; c++)
        {
            temp = 0;
            for (int b = 0; b < B; b += numprocs)
            {
                temp += mat1[a][b] * mat2inv[c][b];
            }
            MPI_Send(temp, 1, MPI_INt, (myrank + 1) % numprocs, 99, MPI_COMM_WORLD);
            MPI_Recv(matret[a][c], 1, MPI_INT, (myrank - 1 + numprocs) % numprocs, 99, MPI_COMM_WORLD, &status);
            // matret[a][c] = temp;
        }
    }
    
    MPI_Finalize();

    //输出
    for (int i = 0; i < A; ++i)
    {
        for (int j = 0; j < C; ++j)
            printf("%d ", matret[i][j]);
        printf("\n");
    }
    return 0;
}