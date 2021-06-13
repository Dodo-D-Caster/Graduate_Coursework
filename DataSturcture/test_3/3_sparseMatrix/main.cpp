#include <iostream>
#include "sparsematrix.h"

int main()
{
    //��������ϡ�����a��b
    sparseMatrix a;
    sparseMatrix b;

    //��˳���ܱ�
    //��4*(row) + col��С����
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

    printf("����a: \n");
    a.output();
    printf("����b: \n");
    b.output();

    //���aת�õ���Ԫ��
    printf("aת�õ���Ԫ��: \n");
    a.transpose().output();

    //���a+b����Ԫ��
    printf("a+b����Ԫ��: \n");
    a.add(b).output();
}
