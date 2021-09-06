//实验一（二）弦截法
//x[k+1]=x[k]-f(x[k])/(f(x[k])-f(x[k-1]))*(x[k]-x[k-1])

#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

//f(x)=x^3-x-1
double f(double x){
    return x*x*x-x-1;
}

int main()
{
    double x[100]={0};
    x[0]=1;     //近似根
    x[1]=2;     //近似根
    int k=1;    //计数

    cout<<"x0: "<<setprecision(10)<<x[0]<<endl;

    while(fabs(x[k]-x[k-1])>=1e-8){ //设置精度
        cout<<"x"<<k<<": "<<setprecision(10)<<x[k]<<endl;
        x[k+1]=x[k]-f(x[k])/(f(x[k])-f(x[k-1]))*(x[k]-x[k-1]);
        k++;
    }
    cout<<"x"<<k<<": "<<setprecision(10)<<x[k]<<endl;
    return 0;
}
