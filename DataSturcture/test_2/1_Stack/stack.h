#ifndef STACK_H
#define STACK_H

#include <iostream>

class Stack
{
private:
    char *data;
    int maxSize;   //ջ�������
    int top;    //ջ��Ԫ������ ָ��ջ��
    void overflow();

public:
    Stack();    //����
    ~Stack(){delete [] data;}   //����
    void push(char d);  //��ջ
    void pop(); //��ջ
    char getpop();  //��ȡջ��Ԫ��
    bool isEmpty(); //�ж�ջ��
    bool isFull();  //�ж�ջ��
    int getSize();  //��ȡջ��
    void makeEmpty();   //���ջ
    void outputStack();  //���ջ(��ջ����ջ��)
};

#endif // STACK_H
