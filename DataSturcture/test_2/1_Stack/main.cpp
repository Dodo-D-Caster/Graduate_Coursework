#include <iostream>
#include "stack.h"

int main()
{
    //初始化栈S
    Stack S;

    //判断栈S是否非空
    if(S.isEmpty()){
        printf("栈为空\n");
    }else{
        printf("栈非空\n");
    }

    //依次进栈
    char a='a',b='b',c='c',d='d',e='e';
    S.push(a);
    S.push(b);
    S.push(c);
    S.push(d);
    S.push(e);

    //输出栈的长度
    printf("栈的长度为: %d\n",S.getSize());

    //输出从栈顶到栈底的元素,同时也是出栈序列
    S.outputStack();

    //释放栈
    S.makeEmpty();
    S.~Stack();
}
