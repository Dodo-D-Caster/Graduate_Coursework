//实验一（一）牛顿下山法
//x1=x0-f(x0)/f'(x0)

#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

//f(x)=x^2-3x+2-e^x
double f(double x){
    return x*x-3*x+2-exp(x);
}

//f'(x)=2x-3-e^x
double f_(double x){
    return 2*x-3-exp(x);
}

int main(){
    double lambda=1.0;  //下山因子

    double x[100]={0};
    x[0]=0;
    x[1]=x[0]-f(x[0])/f_(x[0]);

    //循环并判断精度
    int k=1;
    cout<<"x0: "<<x[0]<<endl;
    while(fabs(x[k]-x[k-1])>=1e-8){ //设置精度
        x[k+1]=x[k]-f(x[k])/f_(x[k]);
        while(fabs(f(x[k+1]))>=fabs(f(x[k]))){
            lambda/=2.0;  //下山因子逐次减半
            x[k+1]=x[k]-lambda*f(x[k])/f_(x[k]);
        }
        cout<<"x"<<k<<": "<<setprecision(10)<<x[k]<<endl;
        k++;
    }
    cout<<"x"<<k<<": "<<setprecision(10)<<x[k]<<endl;
    return 0;
}
