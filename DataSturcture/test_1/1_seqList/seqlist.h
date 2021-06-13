#ifndef SEQLIST_H
#define SEQLIST_H

#include <iostream>

class seqList
{
private:
    char *data = new char[100]; //存放元素的数组
    int last=-1;   //最后一个元素位置(从0开始)

public:
    seqList(){}  //构建
    ~seqList(){delete [] data;} //析构（释放）
    void insertData(char d); //尾插法插入元素
    int listLength();   //获取长度
    bool isEmpty(); //判断是否为空
    char getDataByNum(int n); //获取第n个元素
    int getNumByData(char d);    //获取元素d的位置
    void insertDataByNum(int n, char d);   //在第n个元素的位置上插入d
    void deleteDataByNum(int n);  //删除第n个元素
    void outputList();  //输出整个表
};

#endif // SEQLIST_H
