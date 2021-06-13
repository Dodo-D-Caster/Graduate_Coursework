#include <iostream>
#include "sparsematrix.h"

int main()
{
    //生成两个稀疏矩阵a和b
    sparseMatrix a;
    sparseMatrix b;

    //该顺序不能变
    //按4*(row) + col大小排序
    a.setData(0,0,1);
    a.setData(1,1,1);
    a.setData(0,2,3);
    a.setData(2,2,1);
    a.setData(3,2,1);
    a.setData(3,3,1);

    b.setData(0,0,3);
    b.setData(1,1,4);
    b.setData(2,2,1);
    b.setData(3,3,2);

    printf("矩阵a: \n");
    a.output();
    printf("矩阵b: \n");
    b.output();

    //输出a转置的三元组
    printf("a转置的三元组: \n");
    a.transpose().output();

    //输出a+b的三元组
    printf("a+b的三元组: \n");
    a.add(b).output();
}
