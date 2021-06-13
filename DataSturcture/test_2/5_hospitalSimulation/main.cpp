#include <iostream>
#include "queue.h"
using namespace std;

void menu(Queue Q){
    cout<<"菜单:"<<endl
        <<"1.排队"<<endl
        <<"2.就诊"<<endl
        <<"3.查看排队"<<endl
        <<"4.不再排队，余下依次就诊"<<endl
        <<"5.下班"<<endl;
    while(true){
        int choice;
        cout<<"请输入要选择的操作: ";
        cin>>choice;
        switch (choice) {
        case 1:{
            printf("请输入病历号: ");
            int blh;   //病历号
            cin>>blh;
            Q.enQueue(blh);
            break;
        }
        case 2:{
            Q.deQueue();
            break;
        }
        case 3:{
            printf("从对首到队尾所有的排队病人的病历号为: \n");
            Q.outputQueue();
            cout<<endl;
            break;
        }
        case 4:{
            printf("从对首到队尾所有的排队病人的病历号为: \n");
            Q.outputQueue();
            cout<<endl;
            for(int i=0; i<=Q.getSize(); ++i)
                Q.deQueue();
            if(Q.isEmpty())
                cout<<"已全部就诊"<<endl;
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
