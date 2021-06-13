#include <iostream>

using namespace std;
int flag=0;

//�������У���ķ��ұ� С�ķ����
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

//��������
void quickSort(int a[],int front, int rear){
    if(front<rear){
        int empty = adjust(a,front,rear);
        flag++;
        printf("��%d������, ����Ϊ: ",flag);
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
