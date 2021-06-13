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
    ~List(){makeEmpty();}   //析构（释放）
    void makeEmpty();   //置为空表
    void insertData(char &d); //尾插法插入元素
    circNode * getHead(){return head;}  //获取头结点
    int listLength();   //获取长度
    bool isEmpty(); //判断是否为空
    char getDataByNum(int n); //获取第n个元素
    int getNumByData(char &d);    //获取元素d的位置
    circNode * locate(int n);   //返回第n个元素地址
    bool insertDataByNum(int n, char &d);   //在第n个元素的位置上插入d
    bool deleteDataByNum(int n);  //删除第n个元素
    void outputList();  //输出整个表
    List & operator = (List & L);
};

#endif // CIRCLINK_H
