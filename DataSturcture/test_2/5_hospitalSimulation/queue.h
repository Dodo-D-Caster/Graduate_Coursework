#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>

//ѭ������
class Queue
{
private:
    int front, rear;    //��ͷ����β
    int * data;    //����
    int maxSize;    //�������

public:
    Queue();    //����
    ~Queue(){delete [] data;}   //����
    void enQueue(int d);   //��d���
    void deQueue(); //����
    bool isEmpty(); //�ж϶ӿ�
    bool isFull();  //�ж϶���
    int getSize();  //��ȡ�ӳ�
    void outputQueue(); //���ջ
};

#endif // QUEUE_H
