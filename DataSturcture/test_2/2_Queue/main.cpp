#include <iostream>
#include "queue.h"

int main()
{
    //��ʼ��ջQ
    Queue Q;

    //�ж�ջQ�Ƿ�ǿ�
    if(Q.isEmpty()){
        printf("����Ϊ��\n");
    }else{
        printf("���зǿ�\n");
    }

    //�������
    char a='a',b='b',c='c';
    Q.enQueue(a);
    Q.enQueue(b);
    Q.enQueue(c);

    //����һ��Ԫ�ز������Ԫ��
    Q.deQueue();

    //���Ԫ�ظ���
    printf("����Ԫ�ظ���Ϊ: %d\n",Q.getSize());

    //�������
    char d='d',e='e',f='f';
    Q.enQueue(d);
    Q.enQueue(e);
    Q.enQueue(f);

    //�������
    Q.outputQueue();

    //�ͷŶ���
    Q.~Queue();

}
