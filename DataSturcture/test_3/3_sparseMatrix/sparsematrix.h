#ifndef SPARSEMATRIX_H
#define SPARSEMATRIX_H

#include <iostream>

//三元组类 <row, col, value>
struct triple
{
    int row, col;   //行号，列号
    int value; //元素
    //构造
    triple(){}
    triple(int row, int col, int value){
        this->col = col;
        this->row = row;
        this->value = value;
    }
    triple &operator = (triple & tri);
};

//三元组表
class sparseMatrix
{
private:
    int rows, cols; //行数，列数
    int size;   //项数
    triple *data = new triple[16];  //每一个三元组
    int maxSize=16;    //最大存储容量

public:
    sparseMatrix(); //构造
    sparseMatrix(sparseMatrix &spa);    //构造
    ~sparseMatrix(){} //析构
    void setData(int row, int col, int value){data[size].col=col; data[size].row=row; data[size].value=value; size++;}   //设置项方式2
    sparseMatrix transpose();   //转置
    sparseMatrix add(sparseMatrix &spa);  //加法
    void output();  //输出
    sparseMatrix & operator = (sparseMatrix & spa); //重写=

};

#endif // SPARSEMATRIX_H
