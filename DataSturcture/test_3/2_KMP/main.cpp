#include <iostream>
//using namespace std;
int next[100];

//返回匹配次数
int KMP(std::string s, std::string t){
    int ls = s.size();
    int lt = t.size();
    int i=0,j=0;
    int flag = 0;   //记录匹配成功次数
    while(i<ls){
        //失配则回溯 相等则继续
        if(j==-1 || s[i]==t[j]){
            i++;
            j++;
        }else
            j = next[j];
        //如果成功匹配,继续进行下一次匹配
        if(j == lt){
            flag++;
            printf("第%d次匹配,匹配初始下标为%d\n",flag,i-lt);
            std::cout<<i<<" "<<j<<std::endl;
            i = i-lt+1;
            j=0;
        }
    }
    return flag;
}

void getNext(std::string t){
    int l = t.size();
    next[0] = -1;  //初始化
    int i=0, j=-1;
    for(i=0; i<l; ){
        //一直回溯j直到t[i]==t[j]或j减小到-1
        if(j==-1 || t[i]==t[j]){
            i++;
            j++;
            next[i] = j;
        }else
            j = next[j];
    }
}

int main(){
    std::string s = "aaabbdaabbde";
    std::string t = "aabbd";
    getNext(t);
    int time = KMP(s,t);
    printf("共%d次匹配成功",time);
}
