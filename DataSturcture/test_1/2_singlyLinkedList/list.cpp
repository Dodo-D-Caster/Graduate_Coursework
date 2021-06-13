#include "list.h"

void List::makeEmpty(){
    LinkNode *p;
    while(head->next != NULL){
        p = head->next;
        head->next = p->next;
        delete p;
    }
}

void List::insertData(char &d){
    LinkNode * newNode; //Ҫ������½��
    if(isEmpty()){
        head = new LinkNode;
        last = head;
    }
    newNode = new LinkNode(d);
    last->next = newNode;
    last = newNode;
}

int List::listLength(){
    LinkNode *p = head->next;
    int i = 0;
    while(p != NULL){
        p = p->next;
        i++;
    }
    return i;
}

bool List::isEmpty(){
    return head->next == NULL;
}

char List::getDataByNum(int n){
    if(n<=0||n>listLength())
        return 0;   //δ�ҵ�
    LinkNode *p = head;
    while(n--){
        p = p->next;
    }
    return p->data;
}

int List::getNumByData(char &d){
    LinkNode *p = head->next;
    int i = 0;
    while(p != NULL){
        if(p->data == d) break;
        else p = p->next;
        i++;
    }
    if(i>listLength())
        return 0;   //δ�ҵ�
    return i;
}

LinkNode * List::locate(int n){
    if(n<0||n>listLength())
        return NULL;
    LinkNode *p = head;
    for(int i=0; i<n; ++i){
        p = p->next;
    }
    return p;
}

bool List::insertDataByNum(int n, char &d){
//    if(n<=0||n>listLength()+1)
//        printf("��������ʵ�λ��");
    LinkNode *p = locate(n);
    if(p == NULL){
        //printf("����ʧ��");
        return false;
    }
    LinkNode *newNode = new LinkNode(d);
    newNode->next = p->next;
    p->next = newNode;
    //printf("����ɹ�");
    return true;
}

bool List::deleteDataByNum(int n){
    if(n<=0||n>listLength()){
        //printf("��������ʵ�λ��");
        return false;
    }
    LinkNode *p = locate(n-1);
    LinkNode *del = p->next;
    p->next = del->next;
    delete del;
    //printf("ɾ���ɹ�");
    return true;
}

void List::outputList(){
    LinkNode *p = head;
    for(int i=0; i<listLength(); ++i){
        printf("%c ",p->next->data);
        p = p->next;
    }
}

List& List::operator=(List & L){
    char value;
    LinkNode * s = L.getHead();
    LinkNode * d = head = new LinkNode;
    while(s->next != NULL){
        value = s->next->data;
        d->next = new LinkNode(value);
        d = d->next;
        s = s->next;
    }
    d->next = NULL;
    return * this;
}
