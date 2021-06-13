#ifndef SEQLIST_H
#define SEQLIST_H

#include <iostream>

class seqList
{
private:
    char *data = new char[100]; //���Ԫ�ص�����
    int last=-1;   //���һ��Ԫ��λ��(��0��ʼ)

public:
    seqList(){}  //����
    ~seqList(){delete [] data;} //�������ͷţ�
    void insertData(char d); //β�巨����Ԫ��
    int listLength();   //��ȡ����
    bool isEmpty(); //�ж��Ƿ�Ϊ��
    char getDataByNum(int n); //��ȡ��n��Ԫ��
    int getNumByData(char d);    //��ȡԪ��d��λ��
    void insertDataByNum(int n, char d);   //�ڵ�n��Ԫ�ص�λ���ϲ���d
    void deleteDataByNum(int n);  //ɾ����n��Ԫ��
    void outputList();  //���������
};

#endif // SEQLIST_H
