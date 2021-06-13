#include "queue.h"

Queue::Queue(){
    maxSize = 50;
    front = 0;
    rear = 0;
    data = new int[maxSize];
}

void Queue::enQueue(int d){
    if(isFull()){
        printf("��������\n");
    }else{
        data[rear] = d;
        rear = (rear+1)%maxSize;
        printf("%d�Ų�����ӳɹ�\n",d);
    }
}

void Queue::deQueue(){
    if(isEmpty()){
        printf("����Ϊ��\n");
    }else{
        printf("%d�Ų��˳��ӳɹ�\n",data[front]);
        front = (front+1)%maxSize;
    }
}

bool Queue::isFull(){
    return (rear+1)%maxSize == front;
}

bool Queue::isEmpty(){
    return rear ==front;
}

int Queue::getSize(){
    return (rear-front+maxSize)%maxSize;
}

void Queue::outputQueue(){
    for(int i=front; i!=rear; ++i){
        i = i%maxSize;
        printf("%d ",data[i]);
    }
}
