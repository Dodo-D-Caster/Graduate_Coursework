#include <iostream>
#include "stack"
using namespace std;
const int n = 6;  //点数
bool visit[n] = {0};    //标记是否被访问

//边结点
typedef struct arcNode{
    int indexNext;   //另一个顶点位置
    int w=0;  //权重
    arcNode *next = NULL;  //下一条边
    arcNode(){}
    arcNode(int num, int w):indexNext(num),w(w),next(NULL){}
}arcNode;

//点结点
struct vNode{
    int num=0;    //顶点编号 v1对应0
    struct arcNode *head = NULL;  //边的头结点
};

//邻接表
struct table{
    int numArc=0;   //边数
    vNode v[n];   //顶点头结点
    int arcNum;    //边数
    void insertV(int i, int n){
        v[i].num = n;
        v[i].head = NULL;
    }
    void insertArc(int v1, int v2, int w){
        if(v1>=0&&v1<n&&v2>=0&&v2<n){
            arcNode *q,*p = v[v1].head;
            q = new arcNode;
            //顺着链找合适的插入位置
            while(p!=NULL){
                if(p->indexNext == v2){
                    cout<<"边已存在\n";
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
            //cout<<"加入边成功！\n";
        }
    }

};

//visit[] 清0
void makeVisit_0(){
    for(int i=0; i<n; ++i)
        visit[i] = 0;
}

//深度优先算法遍历DFS 递归
void DFS_recersion(table G, int i){
    arcNode *p;
    cout<<"v"<<G.v[i].num+1<<" ";
    visit[i] = 1;
    for(p=G.v[i].head; p!=NULL; p=p->next){
        if(!visit[p->indexNext])
            DFS_recersion(G,p->indexNext);
    }
}

//深度优先算法遍历DFS 非递归
void DFS_NONrecersion(table G, int i){
    stack<arcNode *> s;
    int size = 0;
    arcNode *p = G.v[i].head;

    cout<<"v"<<G.v[i].num+1<<" ";
    visit[i] = 1;   //已访问
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

//广度优先遍历BFS
void BFS(table G, int i){
    for(int j=0; j<n; ++i){
        if(visit[j]==0){
            cout<<"v"<<j+1<<" ";
            visit[j] = 1;
        }
        arcNode *tmp = G.v[i].head;  //记录头结点
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
    // a[i][j] 表示 v(i+1) 到v(j+1) 的权
    int a[n][n] = {0};

    //创建邻接矩阵
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

    //输出
    cout<<"邻接矩阵: "<<endl;
    for(int i=0; i<n; ++i){
        for(int j=0; j<n; ++j)
            cout<<a[i][j]<<" ";
        cout<<endl;
    }
    cout<<endl;

    //创建邻接表
    table aTable;
    aTable.arcNum = 10; //设置边数
    //为顶点编号
    for(int i=0; i<n; ++i){
        aTable.insertV(i,i);
    }

    //创建邻接表
    for(int i=0; i<n; ++i){
        for(int j=0; j<n; ++j){
            if(a[i][j] != 0){
                aTable.insertArc(i,j,a[i][j]);
            }
        }
    }
    cout<<"邻接表创建完成"<<endl<<endl;

    //输出
    cout<<"邻接表: \n";
    for(int i=0; i<n; ++i){
        cout<<"v"<<i+1<<":  ";
        arcNode *tmp = aTable.v[i].head;  //记录头结点
        while(tmp!=NULL){
            cout<<"w:"<<tmp->w<<" ";
            cout<<"v"<<tmp->indexNext+1<<"  ";
            tmp = tmp->next;
        }
        cout<<endl;
    }
    cout<<endl;

    //从顶点V1开始的深度优先遍历序列序列（递归算法）
    makeVisit_0();
    cout<<"从顶点V1开始的深度优先遍历序列序列（递归算法）: \n";
    DFS_recersion(aTable,0);
    cout<<endl;

    //从顶点V1开始的深度优先遍历序列序列（非递归算法）
    makeVisit_0();
    cout<<"从顶点V1开始的深度优先遍历序列序列（非递归算法）: \n";
    DFS_NONrecersion(aTable,0);
    cout<<endl;

    //从顶点v1开始的广度优先遍历序列
    makeVisit_0();
    cout<<"从顶点v1开始的广度优先遍历序列: \n";
    BFS(aTable,0);
    cout<<endl;






}
