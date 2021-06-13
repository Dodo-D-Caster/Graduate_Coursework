#include "list.h"

void List::makeEmpty(){
    head->next = head;
}

void List::insertData(char &d){
    circNode * newNode;

    if(isEmpty()){
        head = new circNode;
        last = head;
    }
    newNode = new circNode(d);
    last->next = newNode;
    last = newNode;
    last->next = head;
}

int List::listLength(){
    circNode *p = head->next;
    int i = 0;
    while(p->next != head){
        p = p->next;
        i++;
    }
    return i;
}

bool List::isEmpty(){
    return head->next == head;
}

char List::getDataByNum(int n){
    if(n<=0||n>listLength())
        return 0;   //δ�ҵ�
    circNode *p = head;
    while(n--){
        p = p->next;
    }
    return p->data;
}

int List::getNumByData(char &d){
    circNode *p = head->next;
    int i = 0;
    while(p->next != head){
        if(p->data == d) break;
        else p = p->next;
        i++;
    }
    if(i>listLength())
        return 0;   //δ�ҵ�
    return i;
}

circNode * List::locate(int n){
    if(n<0||n>listLength())
        return NULL;
    circNode *p = head;
    for(int i=0; i<n; ++i){
        p = p->next;
    }
    return p;
}

bool List::insertDataByNum(int n, char &d){
//    if(n<=0||n>listLength()+1)
//        printf("��������ʵ�λ��");
    circNode *p = locate(n);
    if(p == NULL){
        //printf("����ʧ��");
        return false;
    }
    circNode *newNode = new circNode(d);
    newNode->next = p->next;
    p->next = newNode;
    if(n == listLength()){
        last = newNode;
        last->next = head;
    }
    //printf("����ɹ�");
    return true;
}

bool List::deleteDataByNum(int n){
    if(n<=0||n>listLength()){
        //printf("��������ʵ�λ��");
        return false;
    }
    circNode *p = locate(n-1);
    circNode *del = p->next;

    if(n == listLength()){
        last = p;
        last->next = head;
    }

    p->next = del->next;
    delete del;
    //printf("ɾ���ɹ�");
    return true;
}

void List::outputList(){
    circNode *p = head;
    for(int i=0; i<=listLength(); ++i){
        printf("%c ",p->next->data);
        p = p->next;
    }
}

List& List::operator=(List & L){
    char value;
    circNode * s = L.getHead();
    circNode * d = head = new circNode;
    while(s->next != NULL){
        value = s->next->data;
        d->next = new circNode(value);
        d = d->next;
        s = s->next;
    }
    d->next = NULL;
    return * this;
}
