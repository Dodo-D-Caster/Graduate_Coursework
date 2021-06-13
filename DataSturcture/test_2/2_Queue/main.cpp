#include <iostream>
#include "queue.h"

int main()
{
    //初始化栈Q
    Queue Q;

    //判断栈Q是否非空
    if(Q.isEmpty()){
        printf("队列为空\n");
    }else{
        printf("队列非空\n");
    }

    //依次入队
    char a='a',b='b',c='c';
    Q.enQueue(a);
    Q.enQueue(b);
    Q.enQueue(c);

    //出队一个元素并输出该元素
    Q.deQueue();

    //输出元素个数
    printf("队列元素个数为: %d\n",Q.getSize());

    //依次入队
    char d='d',e='e',f='f';
    Q.enQueue(d);
    Q.enQueue(e);
    Q.enQueue(f);

    //输出队列
    Q.outputQueue();

    //释放队列
    Q.~Queue();

}
