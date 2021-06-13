#include <iostream>

using namespace std;
const int n = 6;  //����

//�߽��
typedef struct arcNode{
    int indexNext;   //��һ������λ��
    int w=0;  //Ȩ��
    arcNode *next = NULL;  //��һ����
    arcNode(){}
    arcNode(int num, int w):indexNext(num),w(w),next(NULL){}
}arcNode;

//����
struct vNode{
    int num=0;    //������ v1��Ӧ0
    struct arcNode *head = NULL;  //�ߵ�ͷ���
};

//�ڽӱ�
struct table{
    int numArc=0;   //����
    vNode v[n];   //����ͷ���
    int arcNum;    //����
    void insertV(int i, int n){
        v[i].num = n;
        v[i].head = NULL;
    }
    void insertArc(int v1, int v2, int w){
        if(v1>=0&&v1<n&&v2>=0&&v2<n){
            arcNode *q,*p = v[v1].head;
            q = new arcNode;
            //˳�����Һ��ʵĲ���λ��
            while(p!=NULL){
                if(p->indexNext == v2){
                    cout<<"���Ѵ���\n";
                    return;
                }
                q = p;
                p = p->next;
            }
            p = new arcNode;
            q->next = p;
            if(v[v1].head == NULL)
                v[v1].head = p;
            p->indexNext = v2;
            p->w = w;
            p->next = NULL;
            //cout<<"����߳ɹ���\n";
        }
    }

};

int main()
{
    // a[i][j] ��ʾ v(i+1) ��v(j+1) ��Ȩ
    int a[n][n] = {0};

    //�����ڽӾ���
    a[0][1] = 5;
    a[0][3] = 7;
    a[1][2] = 4;
    a[2][0] = 8;
    a[2][5] = 9;
    a[3][2] = 5;
    a[3][5] = 6;
    a[4][3] = 5;
    a[5][0] = 3;
    a[5][4] = 1;

    //���
    cout<<"�ڽӾ���: "<<endl;
    for(int i=0; i<n; ++i){
        for(int j=0; j<n; ++j)
            cout<<a[i][j]<<" ";
        cout<<endl;
    }
    cout<<endl;

    //�����ڽӱ�
    table aTable;
    aTable.arcNum = 10; //���ñ���
    //Ϊ������
    for(int i=0; i<n; ++i){
        aTable.insertV(i,i);
    }

    //�����ڽӱ�
    for(int i=0; i<n; ++i){
        for(int j=0; j<n; ++j){
            if(a[i][j] != 0){
                aTable.insertArc(i,j,a[i][j]);
            }
        }
    }
    cout<<"�ڽӱ������"<<endl<<endl;

    //���
    cout<<"�ڽӱ�: \n";
    for(int i=0; i<n; ++i){
        cout<<"v"<<i+1<<":  ";
        arcNode *tmp = aTable.v[i].head;  //��¼ͷ���
        while(tmp!=NULL){
            cout<<"w:"<<tmp->w<<" ";
            cout<<"v"<<tmp->indexNext+1<<"  ";
            tmp = tmp->next;
        }
        cout<<endl;
    }

    //�����ڽӾ���
    int b[n][n] = {0};
    for(int i=0; i<n; ++i){
        arcNode *tmp = aTable.v[i].head;  //��¼ͷ���
        while(tmp!=NULL){
            b[i][tmp->indexNext] = tmp->w;
            tmp = tmp->next;
        }
    }
    cout<<endl;
    cout<<"�ڽӾ��󴴽����"<<endl<<endl;

    //���
    cout<<"�ڽӾ���: "<<endl;
    for(int i=0; i<n; ++i){
        for(int j=0; j<n; ++j)
            cout<<b[i][j]<<" ";
        cout<<endl;
    }
    cout<<endl;




}
