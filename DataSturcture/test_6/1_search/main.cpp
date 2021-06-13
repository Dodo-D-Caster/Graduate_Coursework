#include <iostream>

using namespace std;

//顺序查找
//寻找x所在位置，返回下标
int search(int a[],int length,int x){
    for(int i=0; i<length; ++i)
        if(a[i]==x)
            return i;
}

int main()
{
    int a[10] = {3,6,2,10,1,8,5,7,4,9};
    int x = 5;
    int location = search(a,10,x)+1;
    printf("%d在第%d个",x,location);
}
