#include <iostream>
using namespace std;
const int p = 13;

int H(int key){
    return key%p;
}

//存入哈希表
void HashTable(int a[], int key){
    int index = H(key);
    while(a[index]!=0){
        index++;
        if(index==12)
            index = 0;
    }
    a[index]=key;
}

//查找 返回下标
int search(int a[], int d){
    int index = H(d);
    while(a[index]!=d){
        index++;
        if(index==12)
            index = 0;
    }
    return index;
}

int main()
{
    int a[12] = {0};    //0记为空
    for(int i=0; i<12; ++i)
        a[i]=0;
    int b[11] = {16,74,60,43,54,90,46,31,29,88,77};

    //存入哈希表
    for(int i=0; i<11; ++i){
        HashTable(a,b[i]);
    }
    cout<<"各数存入哈希表成功"<<endl;

    //查找关键字为29的记录
    int index29 = search(a,29);
    cout<<"29在a["<<index29<<"]"<<endl;

    //删除77，再将其插入
    int index77 = search(a,77);
    a[index77] = 0;
    HashTable(a,77);
    cout<<"77存入哈希表成功"<<endl;
}
