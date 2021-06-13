#include "seqlist.h"

void seqList::insertData(char d){
    *(data+last+1)=d;
    last++;
}

int seqList::listLength(){
    return last+1;
}

bool seqList::isEmpty(){
    return last == -1;
}

char seqList::getDataByNum(int n){
    if(n>last+1||n<=0)
        return 0;   //表示未找到
    return *(data+n-1);
}

int seqList::getNumByData(char d){
    for(int i=0; i<=last; ++i)
        if(*(data+i) == d)
            return i+1;
    return 0;   //表示未找到
}

void seqList::insertDataByNum(int n, char d){
    if(n>=last+1||n<=0)
        printf("请输入合适的位置\n");
    else{
        for(int i=last; i>=n-1; --i)
            *(data+i+1)=*(data+i);
        data[n-1]=d;
        last++;
    }
}

void seqList::deleteDataByNum(int n){
    if(n>=last+1||n<=0)
        printf("请输入合适的位置\n");
    else{
        for(int i=n-1; i<=last; ++i)
            *(data+i)=*(data+i+1);
        last--;
    }
}

void seqList::outputList(){
    for(int i=0; i<=last; ++i)
        printf("%c ",*(data+i));
}
