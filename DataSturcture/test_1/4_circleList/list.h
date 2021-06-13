#ifndef CIRCLINK_H
#define CIRCLINK_H

#include <iostream>

struct circNode{
    char data;
    circNode * next;
    circNode(circNode *link = NULL){
        next = link;
    }
    circNode(char d, circNode *link = NULL){
        data = d;
        next = link;
    }
};

class List
{
private:
    circNode *head, *last;

public:
    List(){head = new circNode; head->next = head;}
    ~List(){makeEmpty();}   //�������ͷţ�
    void makeEmpty();   //��Ϊ�ձ�
    void insertData(char &d); //β�巨����Ԫ��
    circNode * getHead(){return head;}  //��ȡͷ���
    int listLength();   //��ȡ����
    bool isEmpty(); //�ж��Ƿ�Ϊ��
    char getDataByNum(int n); //��ȡ��n��Ԫ��
    int getNumByData(char &d);    //��ȡԪ��d��λ��
    circNode * locate(int n);   //���ص�n��Ԫ�ص�ַ
    bool insertDataByNum(int n, char &d);   //�ڵ�n��Ԫ�ص�λ���ϲ���d
    bool deleteDataByNum(int n);  //ɾ����n��Ԫ��
    void outputList();  //���������
    List & operator = (List & L);
};

#endif // CIRCLINK_H
