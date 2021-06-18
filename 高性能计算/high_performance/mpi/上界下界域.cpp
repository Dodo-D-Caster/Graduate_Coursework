#include <cstdio>
#include <mpi.h>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <ctime>

using namespace std;

#define maxbuf 200
#define len 10
#define mp 5

struct data
{
    double value;
    char str;
};

int main(int argc, char *argv[])
{
    int myid, np;
    int root = 0;
    int startWtime = 0;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);
    MPI_Comm_size(MPI_COMM_WORLD, &np);
    printf("Process %d of %d is running.\n", myid, np);
    if (myid == root)
    {
        startWtime = MPI_Wtime();
    }
    //--------------------------------------------
    //代码部分:
    MPI_Aint address1;
    int a = 1;
    MPI_Datatype newType1, newType2;
    int size1, size2;
    MPI_Aint extent1 = 0, ub1 = 0, lb1 = 0;
    MPI_Aint extent2 = 0, ub2 = 0, lb2 = 0;

    MPI_Type_contiguous(3, MPI_INT, &newType1);
    MPI_Type_commit(&newType1);
    MPI_Type_size(newType1, &size1);
    MPI_Type_extent(newType1, &extent1);
    MPI_Type_ub(newType1, &ub1);
    MPI_Type_lb(newType1, &lb1);

    MPI_Type_vector(2, 3, 1, newType1, &newType2);
    MPI_Type_commit(&newType2);
    MPI_Type_free(&newType1);
    MPI_Type_size(newType2, &size2);
    MPI_Type_extent(newType2, &extent2);
    MPI_Type_ub(newType2, &ub2);
    MPI_Type_lb(newType2, &lb2);

    if (myid == 0)
    {
        printf(
            "size = %d\n"
            "extent = %ld\n"
            "ub = %ld\n"
            "lb = %ld\n",
            size1, extent1, ub1, lb1);
        putchar('\n');
        printf(
            "size = %d\n"
            "extent = %ld\n"
            "ub = %ld\n"
            "lb = %ld\n",
            size2, extent2, ub2, lb2);
        putchar('\n');
    }

    //--------------------------------------------
    //Wait for other process to complete the work
    MPI_Barrier(MPI_COMM_WORLD);
    if (myid == root)
    {
        printf("Used %lfs.\n", MPI_Wtime() - startWtime);
    }
    MPI_Finalize();
    return 0;
}
