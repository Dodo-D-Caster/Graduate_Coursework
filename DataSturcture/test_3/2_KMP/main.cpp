#include <iostream>
//using namespace std;
int next[100];

//����ƥ�����
int KMP(std::string s, std::string t){
    int ls = s.size();
    int lt = t.size();
    int i=0,j=0;
    int flag = 0;   //��¼ƥ��ɹ�����
    while(i<ls){
        //ʧ������� ��������
        if(j==-1 || s[i]==t[j]){
            i++;
            j++;
        }else
            j = next[j];
        //����ɹ�ƥ��,����������һ��ƥ��
        if(j == lt){
            flag++;
            printf("��%d��ƥ��,ƥ���ʼ�±�Ϊ%d\n",flag,i-lt);
            std::cout<<i<<" "<<j<<std::endl;
            i = i-lt+1;
            j=0;
        }
    }
    return flag;
}

void getNext(std::string t){
    int l = t.size();
    next[0] = -1;  //��ʼ��
    int i=0, j=-1;
    for(i=0; i<l; ){
        //һֱ����jֱ��t[i]==t[j]��j��С��-1
        if(j==-1 || t[i]==t[j]){
            i++;
            j++;
            next[i] = j;
        }else
            j = next[j];
    }
}

int main(){
    std::string s = "aaabbdaabbde";
    std::string t = "aabbd";
    getNext(t);
    int time = KMP(s,t);
    printf("��%d��ƥ��ɹ�",time);
}
