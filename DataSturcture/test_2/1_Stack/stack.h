#ifndef STACK_H
#define STACK_H

#include <iostream>

class Stack
{
private:
    char *data;
    int maxSize;   //栈最大容量
    int top;    //栈中元素数量 指向栈顶
    void overflow();

public:
    Stack();    //构建
    ~Stack(){delete [] data;}   //析构
    void push(char d);  //入栈
    void pop(); //出栈
    char getpop();  //获取栈顶元素
    bool isEmpty(); //判断栈空
    bool isFull();  //判断栈满
    int getSize();  //获取栈长
    void makeEmpty();   //清空栈
    void outputStack();  //输出栈(从栈顶到栈底)
};

#endif // STACK_H
