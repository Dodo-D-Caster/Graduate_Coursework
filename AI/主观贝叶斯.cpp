#include <iostream>
using namespace std;

double P(double L, double P_H)
{
    return (L*P_H)/((L-1)*P_H+1);
}

void subjective_bayes(double P_H, double LS, double LN, int i)
{
    double P_HE;
    if(LN==1)
    {
        //��ʱE�Ĳ����ڶ�H��Ӱ��
        P_HE = P(LS,P_H);
        printf("P(H%d|E%d)=%f\n",i,i,P_HE);
        printf("����E%d�Ĵ���ʹ��H%dΪ��Ŀ�����������%f��\n\n",i,i,P_HE/P_H);
        return;
    }
    if(LS==1)
    {
        //��ʱE�Ĵ��ڶ�H��Ӱ��
        P_HE = P(LN,P_H);
        printf("P(H%d|!E%d)=%f\n",i,i,P_HE);
        printf("����E%d�Ĳ�����ʹ��H%dΪ��Ŀ�����������%f��\n\n",i,i,P_H/P_HE);
        return;
    }
    else
    {
        //����Ӱ��
        P_HE = P(LS,P_H);
        printf("P(H%d|E%d)=%f\n",i,i,P_HE);
        printf("����E%d�Ĵ���ʹ��H%dΪ��Ŀ�����������%f��\n",i,i,P_HE/P_H);
        P_HE = P(LN,P_H);
        printf("P(H%d|!E%d)=%f\n",i,i,P_HE);
        printf("����E%d�Ĳ�����ʹ��H%dΪ��Ŀ�����������%f��\n\n",i,i,P_H/P_HE);
        return;
    }
}

int main()
{
    //��������
    double P_H[3] = {0.03, 0.05, 0.3}, 
        LS[3] = {10,20,1}, 
        LN[3] = {1,1,0.002};
    for(int i=0; i<3; ++i)
        subjective_bayes(P_H[i],LS[i],LN[i],i+1);
    //�Ա�����
    subjective_bayes(0.5,10,0.002,4);
    return 0;
}