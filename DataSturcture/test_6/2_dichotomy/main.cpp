#include <iostream>

using namespace std;

//���ַ� �����±�
int dichotomy(int a[],int length,int x){
    int front=0, rear=length-1;
    int mid = (rear+front)/2;
    while(front <= rear){
        if(a[mid] > x){
            rear = mid+1;
        }else if(a[mid] < x){
            front = mid-1;
        }else{
            return mid;
        }
    }
}

int main()
{
    int a[10] = {1,2,3,4,5,6,7,8,9,10};
    int x = 5;
    int location = dichotomy(a,10,x)+1;
    printf("%d�ڵ�%d��",x,location);

}

