#include <iostream>
#include "stack.h"

int main()
{
    //��ʼ��ջS
    Stack S;

    //�ж�ջS�Ƿ�ǿ�
    if(S.isEmpty()){
        printf("ջΪ��\n");
    }else{
        printf("ջ�ǿ�\n");
    }

    //���ν�ջ
    char a='a',b='b',c='c',d='d',e='e';
    S.push(a);
    S.push(b);
    S.push(c);
    S.push(d);
    S.push(e);

    //���ջ�ĳ���
    printf("ջ�ĳ���Ϊ: %d\n",S.getSize());

    //�����ջ����ջ�׵�Ԫ��,ͬʱҲ�ǳ�ջ����
    S.outputStack();

    //�ͷ�ջ
    S.makeEmpty();
    S.~Stack();
}
