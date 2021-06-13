#include "stack.h"

Stack::Stack(){
    top = -1;
    maxSize = 50;
    data = new char[maxSize];
}

void Stack::overflow(){
    char * newStack = new char[maxSize+50];
    for(int i=0; i<=top; ++i){
        newStack[i] = data[i];
    }
    delete [] data;
    data = newStack;
}

bool Stack::isFull(){
    return top == maxSize-1;
}

bool Stack::isEmpty(){
    return top == -1;
}

void Stack::push(char d){
    if(isFull())
        overflow();
    data[++top] = d;
    printf("%c��ջ�ɹ�\n",d);
}

void Stack::pop(){
    if(isEmpty()){
        printf("ջΪ��\n");
    }else{
    top--;
    printf("%c��ջ�ɹ�\n",data[top+1]);
    }
}

int Stack::getSize(){
    return top+1;
}

void Stack::makeEmpty(){
    top = -1;
}

void Stack::outputStack(){
    for(int i=top; i>=0; --i){
        printf("%c ",data[i]);
    }
}
