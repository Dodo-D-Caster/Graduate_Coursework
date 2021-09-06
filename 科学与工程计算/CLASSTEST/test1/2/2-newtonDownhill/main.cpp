//实验一（二）牛顿下山法
//x1=x0-f(x0)/f'(x0)

#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

//f(x)=x^3-x-1
double f(double x){
    return x*x*x-x-1;
}

//f'(x)=3x^2-1
double f_(double x){
    return 3*x*x-1;
}

int main(){
    double lambda=1;  //下山因子

    double x[100]={0};
    x[0]=1;
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
