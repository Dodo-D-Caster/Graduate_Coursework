#include <iostream>
using namespace std;

int main(){
    int data[100][100];
    int rows,cols;
    printf("��������������: ");
    scanf("%d",&rows);
    printf("��������������: ");
    scanf("%d",&cols);

    for(int i=0; i<rows; ++i)
        for(int j=0; j<cols; ++j)
            cin>>data[i][j];

    for(int i=0; i<rows; ++i){
        int minRow = data[i][0];
        int minRowJ = 0;
        for(int j=0; j<cols; ++j)
            if(data[i][j]<minRow){
                minRow = data[i][j];
                minRowJ = j;
            }
        int flag = 1;
        for(int k=0; k<rows; ++k){
            if(data[k][minRowJ]>minRow){
                flag = 0;
                break;
            }
        }
        if(flag)
            printf("��%d�е�%d�е�Ԫ��%dΪ����",i+1,minRowJ+1,minRow);
        else
            continue;
    }
}
