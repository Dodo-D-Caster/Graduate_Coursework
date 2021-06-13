#ifndef LIST_H
#define LIST_H

#include <iostream>

//���ýṹ��ʽ
//��������
struct LinkNode{
    char data;
    LinkNode * next;
    LinkNode(LinkNode * p = NULL){next = p;}
    LinkNode(char &d, LinkNode * p = NULL){
        data = d;
        next = p;
    }
};

//������
class List
{
private:
    LinkNode * head;   //ͷ���
    LinkNode * last;    //ָ����β - ����β�巨

public:
    List(){head = new LinkNode;} //����
    ~List(){makeEmpty();}   //�������ͷţ�
    void makeEmpty();   //��Ϊ�ձ�
    void insertData(char &d); //β�巨����Ԫ��
    LinkNode * getHead(){return head;}  //��ȡͷ���
    int listLength();   //��ȡ����
    bool isEmpty(); //�ж��Ƿ�Ϊ��
    char getDataByNum(int n); //��ȡ��n��Ԫ��
    int getNumByData(char &d);    //��ȡԪ��d��λ��
    LinkNode * locate(int n);   //���ص�n��Ԫ�ص�ַ
    bool insertDataByNum(int n, char &d);   //�ڵ�n��Ԫ�ص�λ���ϲ���d
    bool deleteDataByNum(int n);  //ɾ����n��Ԫ��
    void outputList();  //���������
    List & operator = (List & L);
};

#endif // LIST_H
