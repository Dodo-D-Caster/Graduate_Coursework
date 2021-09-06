//实验六 龙贝格

#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

//f(x)
double f(double x){
    if(x==0.0)
        return 1;
    else
        return sin(x)/x;
}

//Tn
//Tn=(b-a)/2n*(f(a)+2*sum[j=1~n-1]f(xj)+f(b))
double Tn(int i){
    //a=0, b=1, 则 b-a=1
    double h=1.0/pow(2,i);
    double sum=0;
    for(int j=1; j<pow(2,i); ++j)
        sum+=2*f(h*j);
    sum+=f(0)+f(1);
    return h/2.0*sum;
}

//Sn
double Sn(int n, double T[]){
    return T[n+1]+(T[n+1]-T[n])/3.0;
}

//Cn
double Cn(int n, double S[]){
    return S[n+1]+(S[n+1]-S[n])/15.0;
}

//Rn
double Rn(int n, double C[]){
    return C[n+1]+(C[n+1]-C[n])/63.0;
}

int main(){
    double T[100]={0};
    double S[100]={0};
    double C[100]={0};
    double R[100]={0};

    //Tn
    //T[0]=T_1 T[1]=T_2 T[2]=T_4 T[3]=T_8 T[4]=T_16
    //预处理到 T_16
    for(int i=0; i<5; ++i){   //
        T[i]=Tn(i);
    }

    //Sn
    //S[0]=S_1 S[1]=S_2 S[2]=S_4 S[3]=S_8
    //预处理到 S_8
    for(int n=0; n<4; ++n)
        S[n]=Sn(n,T);

    //Cn
    //C[0]=C_1 C[1]=C_2 C[2]=C_4
    //预处理到 C_4
    for(int n=0; n<3; ++n)
        C[n]=Cn(n,S);

    //Rn
    //R[0]=R_1 R[1]=R_2
    //预处理到 R_2
    for(int n=0; n<2; ++n)
        R[n]=Rn(n,C);

    int n=1;    //记录R[n]的长度 可推 C[n]长度为n+1 S[n]长度为n+2 T[n]长度为n+3
    while(fabs(R[n]-R[n-1])>=1e-5){
        n++;
        T[n+3]=Tn(n+3);
        S[n+2]=Sn(n+2,T);
        C[n+1]=Cn(n+1,S);
        R[n]=Rn(n,C);
    }

    //输出
    int k[100]={0};
    for(int i=0; i<100; ++i)
        k[i]=i;
    cout<<"k\tT_2^k\t\t\tS_2^(k-1)\t\tC_2^(k-2)\t\tR_2^(k-3)\n";
    cout<<fixed<<setprecision(7);
    cout<<k[0]<<"\t"<<T[0]<<endl;
    cout<<k[1]<<"\t"<<T[1]<<"\t\t"<<S[0]<<endl;
    cout<<k[2]<<"\t"<<T[2]<<"\t\t"<<S[1]<<"\t\t"<<C[0]<<endl;
    cout<<k[3]<<"\t"<<T[3]<<"\t\t"<<S[2]<<"\t\t"<<C[1]<<"\t\t"<<R[0]<<endl;
    for(int i=4; i<=n+3; ++i)
        cout<<k[i]<<"\t"<<T[i]<<"\t\t"<<S[i-1]<<"\t\t"<<C[i-2]<<"\t\t"<<R[i-3]<<endl;

    return 0;
}
