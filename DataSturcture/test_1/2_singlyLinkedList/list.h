#ifndef LIST_H
#define LIST_H

#include <iostream>

//采用结构方式
//链表结点类
struct LinkNode{
    char data;
    LinkNode * next;
    LinkNode(LinkNode * p = NULL){next = p;}
    LinkNode(char &d, LinkNode * p = NULL){
        data = d;
        next = p;
    }
};

//链表类
class List
{
private:
    LinkNode * head;   //头结点
    LinkNode * last;    //指向链尾 - 方便尾插法

public:
    List(){head = new LinkNode;} //构造
    ~List(){makeEmpty();}   //析构（释放）
    void makeEmpty();   //置为空表
    void insertData(char &d); //尾插法插入元素
    LinkNode * getHead(){return head;}  //获取头结点
    int listLength();   //获取长度
    bool isEmpty(); //判断是否为空
    char getDataByNum(int n); //获取第n个元素
    int getNumByData(char &d);    //获取元素d的位置
    LinkNode * locate(int n);   //返回第n个元素地址
    bool insertDataByNum(int n, char &d);   //在第n个元素的位置上插入d
    bool deleteDataByNum(int n);  //删除第n个元素
    void outputList();  //输出整个表
    List & operator = (List & L);
};

#endif // LIST_H
