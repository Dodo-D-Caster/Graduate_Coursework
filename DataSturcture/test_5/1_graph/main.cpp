#include <iostream>

using namespace std;
const int n = 6;  //点数

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

    //创建邻接矩阵
    int b[n][n] = {0};
    for(int i=0; i<n; ++i){
        arcNode *tmp = aTable.v[i].head;  //记录头结点
        while(tmp!=NULL){
            b[i][tmp->indexNext] = tmp->w;
            tmp = tmp->next;
        }
    }
    cout<<endl;
    cout<<"邻接矩阵创建完成"<<endl<<endl;

    //输出
    cout<<"邻接矩阵: "<<endl;
    for(int i=0; i<n; ++i){
        for(int j=0; j<n; ++j)
            cout<<b[i][j]<<" ";
        cout<<endl;
    }
    cout<<endl;




}
