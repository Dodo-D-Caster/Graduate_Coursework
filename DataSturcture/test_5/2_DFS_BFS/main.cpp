#include <iostream>
#include "stack"
using namespace std;
const int n = 6;  //����
bool visit[n] = {0};    //����Ƿ񱻷���

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

//visit[] ��0
void makeVisit_0(){
    for(int i=0; i<n; ++i)
        visit[i] = 0;
}

//��������㷨����DFS �ݹ�
void DFS_recersion(table G, int i){
    arcNode *p;
    cout<<"v"<<G.v[i].num+1<<" ";
    visit[i] = 1;
    for(p=G.v[i].head; p!=NULL; p=p->next){
        if(!visit[p->indexNext])
            DFS_recersion(G,p->indexNext);
    }
}

//��������㷨����DFS �ǵݹ�
void DFS_NONrecersion(table G, int i){
    stack<arcNode *> s;
    int size = 0;
    arcNode *p = G.v[i].head;

    cout<<"v"<<G.v[i].num+1<<" ";
    visit[i] = 1;   //�ѷ���
    size++;

    s.push(p);
    int j=0;

    while(size<6){
        bool flag = 1;
        while(p->indexNext<6&&p->indexNext>=0){
            if(visit[p->indexNext]==0){
                cout<<"v"<<G.v[p->indexNext].num+1<<" ";
                visit[p->indexNext] = 1;
                p = G.v[p->indexNext].head;
                size++;
                flag = 0;
                break;
            }
            p = p->next;
        }
        if(flag){
            p = s.top();
            s.pop();
        }
    }
}

//������ȱ���BFS
void BFS(table G, int i){
    for(int j=0; j<n; ++i){
        if(visit[j]==0){
            cout<<"v"<<j+1<<" ";
            visit[j] = 1;
        }
        arcNode *tmp = G.v[i].head;  //��¼ͷ���
        while(tmp!=NULL){
            if(visit[tmp->indexNext]==0){
                cout<<"v"<<tmp->indexNext+1<<" ";
                visit[tmp->indexNext] = 1;
            }
            tmp = tmp->next;
        }
    }
}

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
    cout<<endl;

    //�Ӷ���V1��ʼ��������ȱ����������У��ݹ��㷨��
    makeVisit_0();
    cout<<"�Ӷ���V1��ʼ��������ȱ����������У��ݹ��㷨��: \n";
    DFS_recersion(aTable,0);
    cout<<endl;

    //�Ӷ���V1��ʼ��������ȱ����������У��ǵݹ��㷨��
    makeVisit_0();
    cout<<"�Ӷ���V1��ʼ��������ȱ����������У��ǵݹ��㷨��: \n";
    DFS_NONrecersion(aTable,0);
    cout<<endl;

    //�Ӷ���v1��ʼ�Ĺ�����ȱ�������
    makeVisit_0();
    cout<<"�Ӷ���v1��ʼ�Ĺ�����ȱ�������: \n";
    BFS(aTable,0);
    cout<<endl;






}
