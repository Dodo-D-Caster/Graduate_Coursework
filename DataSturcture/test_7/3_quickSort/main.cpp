#include <iostream>

using namespace std;
int flag=0;

//调整序列，大的放右边 小的放左边
int adjust(int a[], int front, int rear){
    int i=front, j=rear;
    int x = a[front];
    while(i<j){
        while(a[j]>=x && i<j)
            j--;
        a[i] = a[j];
        while(a[i]<=x && i<j)
            i++;
        a[j] = a[i];
    }
    a[i] = x;
    return i;
}

//快速排序
void quickSort(int a[],int front, int rear){
    if(front<rear){
        int empty = adjust(a,front,rear);
        flag++;
        printf("第%d次排序, 序列为: ",flag);
        for(int m=0; m<10; ++m)
            cout<<a[m]<<" ";
        cout<<endl;
        quickSort(a,front,empty-1);
        quickSort(a,empty+1,rear);
    }
}

int main()
{
    int a[11] = {9,8,7,6,5,4,3,2,1,0};
    quickSort(a,0,9);
}
