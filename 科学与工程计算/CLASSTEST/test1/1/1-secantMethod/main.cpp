//ʵ��һ��һ���ҽط�
//x[k+1]=x[k]-f(x[k])/(f(x[k])-f(x[k-1]))*(x[k]-x[k-1])

#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

//f(x)=x^2-3x+2-e^x
double f(double x){
    return x*x-3*x+2-exp(x);
}

int main()
{
    double x[100]={0};
    x[0]=0;     //���Ƹ�
    x[1]=1;     //���Ƹ�
    int k=1;    //����

    cout<<"x0: "<<setprecision(10)<<x[0]<<endl;

    while(fabs(x[k]-x[k-1])>=1e-8){ //���þ���
        cout<<"x"<<k<<": "<<setprecision(10)<<x[k]<<endl;
        x[k+1]=x[k]-f(x[k])/(f(x[k])-f(x[k-1]))*(x[k]-x[k-1]);
        k++;
    }
    cout<<"x"<<k<<": "<<setprecision(10)<<x[k]<<endl;
    return 0;
}
