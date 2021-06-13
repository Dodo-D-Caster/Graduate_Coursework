#include <iostream>

using namespace std;

//直接插入排序法
void insertSort(int a[], int k){
    for(int i=1; i<k; ++i){
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
    }
}

//希尔排序
void shellSort(int a[],int n){
    int gap = n;
    int flag = 0;   //次数
    //int NN = n/3+1;
    do{
        gap = gap/3+1;  //间隔
        for(int i=0; i<gap; ++i){
            //int b[NN]={0};  //存放分组后的数组
            int b[10]={0};  //存放分组后的数组
            int k=0;
            //分组
            for(int j=i; j<n; j+=gap,k++)
                b[k]=a[j];
             //对分组后的序列进行排序
            insertSort(b,k);
            k=0;
            for(int j=i; j<n; j+=gap,k++)
                a[j]=b[k];
        }
        flag++;
        printf("第%d次排序, 序列为: ",flag);
        for(int m=0; m<n; ++m)
            cout<<a[m]<<" ";
        cout<<endl;
    }while(gap>1);
}

int main()
{
    int a[10] = {9,8,7,6,5,4,3,2,1,0};
    shellSort(a,10);
}
