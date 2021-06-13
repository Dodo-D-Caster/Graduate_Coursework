#ifndef SPARSEMATRIX_H
#define SPARSEMATRIX_H

#include <iostream>

//��Ԫ���� <row, col, value>
struct triple
{
    int row, col;   //�кţ��к�
    int value; //Ԫ��
    //����
    triple(){}
    triple(int row, int col, int value){
        this->col = col;
        this->row = row;
        this->value = value;
    }
    triple &operator = (triple & tri);
};

//��Ԫ���
class sparseMatrix
{
private:
    int rows, cols; //����������
    int size;   //����
    triple *data = new triple[16];  //ÿһ����Ԫ��
    int maxSize=16;    //���洢����

public:
    sparseMatrix(); //����
    sparseMatrix(sparseMatrix &spa);    //����
    ~sparseMatrix(){} //����
    void setData(int row, int col, int value){data[size].col=col; data[size].row=row; data[size].value=value; size++;}   //�����ʽ2
    sparseMatrix transpose();   //ת��
    sparseMatrix add(sparseMatrix &spa);  //�ӷ�
    void output();  //���
    sparseMatrix & operator = (sparseMatrix & spa); //��д=

};

#endif // SPARSEMATRIX_H
