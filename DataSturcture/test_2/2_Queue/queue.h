#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>

//循环队列
class Queue
{
private:
    int front, rear;    //队头、队尾
    char * data;    //队列
    int maxSize;    //最大容量

public:
    Queue();    //构造
    ~Queue(){delete [] data;}   //析构
    void enQueue(char d);   //将d入队
    void deQueue(); //出队
    bool isEmpty(); //判断队空
    bool isFull();  //判断队满
    int getSize();  //获取队长
    void outputQueue(); //输出栈
};

#endif // QUEUE_H
