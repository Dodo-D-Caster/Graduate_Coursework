#include <iostream>
#include "queue.h"
using namespace std;

void menu(Queue Q){
    cout<<"�˵�:"<<endl
        <<"1.�Ŷ�"<<endl
        <<"2.����"<<endl
        <<"3.�鿴�Ŷ�"<<endl
        <<"4.�����Ŷӣ��������ξ���"<<endl
        <<"5.�°�"<<endl;
    while(true){
        int choice;
        cout<<"������Ҫѡ��Ĳ���: ";
        cin>>choice;
        switch (choice) {
        case 1:{
            printf("�����벡����: ");
            int blh;   //������
            cin>>blh;
            Q.enQueue(blh);
            break;
        }
        case 2:{
            Q.deQueue();
            break;
        }
        case 3:{
            printf("�Ӷ��׵���β���е��ŶӲ��˵Ĳ�����Ϊ: \n");
            Q.outputQueue();
            cout<<endl;
            break;
        }
        case 4:{
            printf("�Ӷ��׵���β���е��ŶӲ��˵Ĳ�����Ϊ: \n");
            Q.outputQueue();
            cout<<endl;
            for(int i=0; i<=Q.getSize(); ++i)
                Q.deQueue();
            if(Q.isEmpty())
                cout<<"��ȫ������"<<endl;
            break;
        }
        case 5:{
            Q.~Queue();
            exit(0);
        }
        default:
            break;
        }
    }
}

int main()
{
    Queue Q;
    menu(Q);
}
