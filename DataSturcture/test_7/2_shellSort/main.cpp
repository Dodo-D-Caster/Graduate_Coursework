#include <iostream>

using namespace std;

//ֱ�Ӳ�������
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

//ϣ������
void shellSort(int a[],int n){
    int gap = n;
    int flag = 0;   //����
    //int NN = n/3+1;
    do{
        gap = gap/3+1;  //���
        for(int i=0; i<gap; ++i){
            //int b[NN]={0};  //��ŷ���������
            int b[10]={0};  //��ŷ���������
            int k=0;
            //����
            for(int j=i; j<n; j+=gap,k++)
                b[k]=a[j];
             //�Է��������н�������
            insertSort(b,k);
            k=0;
            for(int j=i; j<n; j+=gap,k++)
                a[j]=b[k];
        }
        flag++;
        printf("��%d������, ����Ϊ: ",flag);
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
