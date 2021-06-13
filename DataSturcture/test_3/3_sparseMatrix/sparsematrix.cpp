#include "sparsematrix.h"

triple& triple::operator=(triple &tri){
    this->col = tri.col;
    this->row = tri.row;
    this->value = tri.value;
    return *this;
}

sparseMatrix::sparseMatrix()
{
    maxSize = 16;   //4*4
    size = 0;
    cols = 4;
    rows = 4;
    data = new triple[maxSize];
}

sparseMatrix::sparseMatrix(sparseMatrix &spa){
    this->rows = spa.rows;
    this->cols = spa.cols;
    this->maxSize = spa.maxSize;
    data = new triple[maxSize];
    for(int i=0; i<size; ++i){
        data[i].col = spa.data[i].col;
        data[i].row = spa.data[i].row;
        data[i].value = spa.data[i].value;
    }
}

sparseMatrix sparseMatrix::transpose(){
    sparseMatrix tra;    //�Ըñ���в���
    tra.cols = this->cols;
    tra.rows = this->rows;
    tra.size = this->size;
    tra.maxSize = this->maxSize;
    if(size>0){
        int a = 0;
        for(int i=0; i<cols; ++i)   //����ɨ��
            for(int j=0; j<size; ++j)   //�ҵ�i����Ԫ��
                if(data[j].col == i){
                    //����ת��
                    tra.data[a].row = i;
                    tra.data[a].col = data[j].row;
                    tra.data[a].value = data[j].value;
                    a++;
                }
    }
    return tra;
}

sparseMatrix sparseMatrix::add(sparseMatrix &spa){
    sparseMatrix s;
    if(this->cols!=spa.cols||this->rows!=spa.rows){
        printf("����ƥ��");
        exit(0);
    }
    s.cols = this->cols;
    s.rows = this->rows;
    s.maxSize = this->maxSize;
    s.size = 0;
    int index_this, index_spa;
    int i,j;
    for(i=0,j=0; i<size&&j<spa.size; ){
        index_this = cols*(data[i].row) + data[i].col;
        index_spa = cols*(spa.data[j].row) + spa.data[j].col;

        //data[i]��spa.data[j]ǰ--����
        if(index_this < index_spa){
            s.data[s.size] = data[i];
            i++;
        }
        //data[i]��spa.data[j]��--����
        else if(index_this > index_spa){
            s.data[s.size] = spa.data[j];
            j++;
        }
        //data[i]��spa.data[j]λ����ͬ--���
        else{
            s.data[s.size] = data[i];
            s.data[s.size].value = data[i].value + spa.data[j].value;
            i++;
            j++;
        }
    s.size++;
    }
    //����ʣ��Ԫ��
    for( ; i<this->size; ++i){
        s.data[s.size] = data[i];
        s.size++;
    }
    for( ; j<spa.size; ++j){
        s.data[s.size] = spa.data[j];
        s.size++;
    }
    return s;
}

void sparseMatrix::output(){
    for(int i=0; i<cols; ++i){
        for(int j=0; j<rows; ++j){
            int flag = 0;   //��¼�Ƿ�Ϊ������
            for(int k=0; k<size; ++k){
                if(data[k].row==j && data[k].col==i){
                    printf("%d ",data[k].value);
                    flag = 1;
                }
            }
            if(flag == 0)
                printf("0 ");
        }
        printf("\n");
    }
}
