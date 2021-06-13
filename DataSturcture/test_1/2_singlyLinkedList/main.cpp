#include <iostream>
#include "list.h"

int main()
{
    //初始化单链表H
    List H;

    //尾插法插入
    char a='a',b='b',c='c',d='d',e='e',f='f';
    H.insertData(a);
    H.insertData(b);
    H.insertData(c);
    H.insertData(d);
    H.insertData(e);

    //输出长度
    printf("单链表的长度为: %d\n",H.listLength());

    //判断为空
    bool isempty = H.isEmpty();
    if(isempty)
        printf("单链表为空\n");
    else
        printf("单链表不为空\n");

    //输出第三个元素
    char d3 = H.getDataByNum(3);
    if(d3 == 0)
        printf("请选择正确的位置\n");
    else
        printf("第三个元素为: %c\n",d3);

    //输出元素d的位置
    int nd = H.getNumByData(d);
    if(nd == 0)
        printf("未找到该元素\n");
    else
        printf("该元素所在位置为: %d\n",nd);

    //在第四个元素位置上插入f元素
    if(H.insertDataByNum(4,f))
        printf("插入成功\n");
    else
        printf("插入失败\n");

    //删除第三个元素
    if(H.deleteDataByNum(3))
        printf("删除成功\n");
    else
        printf("删除失败\n");

    //输出全部
    H.outputList();

    //释放
    H.~List();
}
