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
        //此时E的不存在对H无影响
        P_HE = P(LS,P_H);
        printf("P(H%d|E%d)=%f\n",i,i,P_HE);
        printf("由于E%d的存在使得H%d为真的可能性增加了%f倍\n\n",i,i,P_HE/P_H);
        return;
    }
    if(LS==1)
    {
        //此时E的存在对H无影响
        P_HE = P(LN,P_H);
        printf("P(H%d|!E%d)=%f\n",i,i,P_HE);
        printf("由于E%d的不存在使得H%d为真的可能性削弱了%f倍\n\n",i,i,P_H/P_HE);
        return;
    }
    else
    {
        //都有影响
        P_HE = P(LS,P_H);
        printf("P(H%d|E%d)=%f\n",i,i,P_HE);
        printf("由于E%d的存在使得H%d为真的可能性增加了%f倍\n",i,i,P_HE/P_H);
        P_HE = P(LN,P_H);
        printf("P(H%d|!E%d)=%f\n",i,i,P_HE);
        printf("由于E%d的不存在使得H%d为真的可能性削弱了%f倍\n\n",i,i,P_H/P_HE);
        return;
    }
}

int main()
{
    //例题数据
    double P_H[3] = {0.03, 0.05, 0.3}, 
        LS[3] = {10,20,1}, 
        LN[3] = {1,1,0.002};
    for(int i=0; i<3; ++i)
        subjective_bayes(P_H[i],LS[i],LN[i],i+1);
    //自编数据
    subjective_bayes(0.5,10,0.002,4);
    return 0;
}