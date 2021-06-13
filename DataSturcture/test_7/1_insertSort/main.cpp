#include <iostream>
using namespace std;

//直接插入排序法
void insertSort(int a[],int n){
    int flag = 0;
    for(int i=1; i<n; ++i){
        int j = i-1;
        while(a[i]<a[j]&&j!=-1){
            j--;
        }
        j++;
        int tmp = a[i];
        for(int k=i-1; k>=j; --k){
            a[k+1] = a[k];
        }
        a[j] = tmp;
        flag++;
        printf("第%d次排序, 序列为: ",flag);
        for(int m=0; m<n; ++m)
            cout<<a[m]<<" ";
        cout<<endl;
    }
}

int main()
{
    int a[11] = {9,8,7,6,5,4,3,2,1,0};
    insertSort(a,10);
}
