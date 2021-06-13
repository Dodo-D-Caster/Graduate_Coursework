#include <iostream>
using namespace std;
const int n=9;

bool isAllVisited(int visit[]){
    for(int i=0; i<n; ++i)
        if(visit[i]==0)
            return false;
    return true;
}

int main()
{
    int time[n];    //访问次序
    int visit[n] = {0}; //是否访问
    int v[n] = {0,0,2,1,1,3,1,2,3}; //入度
    int j=0;
    while(!isAllVisited(visit)){
    for(int i=0; i<n; ++i){
        if(v[i]==0 && visit[i]==0){
            time[j]=i;
            j++;
            visit[i] = 1;
            //遇到如下点 则相应入度减少
            switch (i) {
            case 0:{
                v[2]--;
                v[3]--;
                break;
            }
            case 1:{
                v[2]--;
                v[4]--;
                break;
            }
            case 2:{
                v[5]--;
                break;
            }
            case 3:{
                v[5]--;
                break;
            }
            case 4:{
                v[5]--;
                break;
            }
            case 5:{
                v[6]--;
                v[7]--;
                v[8]--;
                break;
            }
            case 6:{
                v[7]--;
                v[8]--;
                break;
            }
            case 7:{
                v[8]--;
                break;
            }
            default:
                break;
            }
        }else
            i++;
    }
    }
    for(int i=0; i<n; ++i)
        cout<<"v"<<time[i]+1<<" ";
    cout<<endl;
}
