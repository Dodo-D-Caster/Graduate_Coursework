#include <iostream>
#include "seqlist.h"

int main()
{
    //��ʼ��˳���L
    seqList L;

    //β�巨����
    L.insertData('a');
    L.insertData('b');
    L.insertData('c');
    L.insertData('d');
    L.insertData('e');

    //�������
    printf("˳���ĳ���Ϊ: %d\n",L.listLength());

    //�ж�Ϊ��
    bool isempty = L.isEmpty();
    if(isempty)
        printf("˳���Ϊ��\n");
    else
        printf("˳���Ϊ��\n");

    //���������Ԫ��
    char d3 = L.getDataByNum(3);
    if(d3 == 0)
        printf("��ѡ����ȷ��λ��\n");
    else
        printf("������Ԫ��Ϊ: %c\n",d3);

    //���Ԫ��d��λ��
    int nd = L.getNumByData('d');
    if(nd == 0)
        printf("δ�ҵ���Ԫ��\n");
    else
        printf("��Ԫ������λ��Ϊ: %d\n",nd);

    //�ڵ��ĸ�Ԫ��λ���ϲ���fԪ��
    L.insertDataByNum(4,'f');

    //ɾ��������Ԫ��
    L.deleteDataByNum(3);

    //���ȫ��
    L.outputList();

    //�ͷ�
    L.~seqList();
}
