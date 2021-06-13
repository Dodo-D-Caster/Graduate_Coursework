#include <iostream>
using namespace std;
const int p = 13;

int H(int key){
    return key%p;
}

//�����ϣ��
void HashTable(int a[], int key){
    int index = H(key);
    while(a[index]!=0){
        index++;
        if(index==12)
            index = 0;
    }
    a[index]=key;
}

//���� �����±�
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
    int a[12] = {0};    //0��Ϊ��
    for(int i=0; i<12; ++i)
        a[i]=0;
    int b[11] = {16,74,60,43,54,90,46,31,29,88,77};

    //�����ϣ��
    for(int i=0; i<11; ++i){
        HashTable(a,b[i]);
    }
    cout<<"���������ϣ��ɹ�"<<endl;

    //���ҹؼ���Ϊ29�ļ�¼
    int index29 = search(a,29);
    cout<<"29��a["<<index29<<"]"<<endl;

    //ɾ��77���ٽ������
    int index77 = search(a,77);
    a[index77] = 0;
    HashTable(a,77);
    cout<<"77�����ϣ��ɹ�"<<endl;
}
