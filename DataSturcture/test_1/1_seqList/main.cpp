#include <iostream>
#include "seqlist.h"

int main()
{
    //初始化顺序表L
    seqList L;

    //尾插法插入
    L.insertData('a');
    L.insertData('b');
    L.insertData('c');
    L.insertData('d');
    L.insertData('e');

    //输出长度
    printf("顺序表的长度为: %d\n",L.listLength());

    //判断为空
    bool isempty = L.isEmpty();
    if(isempty)
        printf("顺序表为空\n");
    else
        printf("顺序表不为空\n");

    //输出第三个元素
    char d3 = L.getDataByNum(3);
    if(d3 == 0)
        printf("请选择正确的位置\n");
    else
        printf("第三个元素为: %c\n",d3);

    //输出元素d的位置
    int nd = L.getNumByData('d');
    if(nd == 0)
        printf("未找到该元素\n");
    else
        printf("该元素所在位置为: %d\n",nd);

    //在第四个元素位置上插入f元素
    L.insertDataByNum(4,'f');

    //删除第三个元素
    L.deleteDataByNum(3);

    //输出全部
    L.outputList();

    //释放
    L.~seqList();
}
