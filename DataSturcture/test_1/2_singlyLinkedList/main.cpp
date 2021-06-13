#include <iostream>
#include "list.h"

int main()
{
    //��ʼ��������H
    List H;

    //β�巨����
    char a='a',b='b',c='c',d='d',e='e',f='f';
    H.insertData(a);
    H.insertData(b);
    H.insertData(c);
    H.insertData(d);
    H.insertData(e);

    //�������
    printf("������ĳ���Ϊ: %d\n",H.listLength());

    //�ж�Ϊ��
    bool isempty = H.isEmpty();
    if(isempty)
        printf("������Ϊ��\n");
    else
        printf("������Ϊ��\n");

    //���������Ԫ��
    char d3 = H.getDataByNum(3);
    if(d3 == 0)
        printf("��ѡ����ȷ��λ��\n");
    else
        printf("������Ԫ��Ϊ: %c\n",d3);

    //���Ԫ��d��λ��
    int nd = H.getNumByData(d);
    if(nd == 0)
        printf("δ�ҵ���Ԫ��\n");
    else
        printf("��Ԫ������λ��Ϊ: %d\n",nd);

    //�ڵ��ĸ�Ԫ��λ���ϲ���fԪ��
    if(H.insertDataByNum(4,f))
        printf("����ɹ�\n");
    else
        printf("����ʧ��\n");

    //ɾ��������Ԫ��
    if(H.deleteDataByNum(3))
        printf("ɾ���ɹ�\n");
    else
        printf("ɾ��ʧ��\n");

    //���ȫ��
    H.outputList();

    //�ͷ�
    H.~List();
}
