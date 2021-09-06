 //实验四 三次样条插值

#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

//f(x)
double f(double x){
    return 1.0/(1+25*x*x);
}

//f'(x)
double f_(double x){
    return -50*x/((1+25*x*x)*(1+25*x*x));
}

//三次样条插值函数 S(x)
//i表示 si(x)
//x_表示 -0.95~0.95的插值节点
double s(int i, double x[], double m[], double y[], double h, double x_){
    return m[i-1]*(x[i]-x_)*(x[i]-x_)*(x[i]-x_)/(6*h)
            +m[i]*(x_-x[i-1])*(x_-x[i-1])*(x_-x[i-1])/(6*h)
            +(y[i-1]-m[i-1]/6*h*h)*(x[i]-x_)/h
            +(y[i]-m[i]/6*h*h)*(x_-x[i-1])/h;
}

//Lagrange插值法 l(x)
//n表示 ln(x)
//x_表示 -0.95~0.95的插值节点
double l(int n, double x[], double x_){
    double sum=0;
    for(int k=0; k<n; ++k){
        double product=1;
        for(int i=0; i<n; ++i){
            if(i!=k)
                product*=(x_-x[i])/(x[k]-x[i]);
        }
        sum+=f(x[k])*product;
    }
    return sum;
}

int main(){
    double x[21]={0};   //x 等距节点
    double y[21]={0};
    for(int i=0; i<=20; ++i){
        x[i]=-1+0.1*i;
        y[i]=f(x[i]);
    }

    double h=0.1;   //h=2/N N=20 则 h=0.1
    double lambda=0.5;  //由于等距节点 lambda=h/(h+h)=1/2
    double mu=0.5;      //mu=1-lambda=1/2
    int ci=2;

    double d[21]={0};
    //由于等距节点 求 d[1]-d[19] 的值
    for(int i=1; i<=19; ++i){
        d[i]=3.0/(h*h)*(y[i+1]-2*y[i]+y[i-1]);
    }

    //解 n-1阶 三对角方程组
    //采用 追赶法    第三章1-64   a=mu b=c c=lambda x=m f=d
    double a[21]={0};
    double b[21]={0};
    double c[21]={0};

    for(int i=1; i<=19; ++i){
        a[i]=mu;
        b[i]=ci;
        c[i]=lambda;
    }
    a[1]=0;
    c[19]=0;

    //计算 beta[i] 的递推公式
    double beta[21]={0};
    beta[1]=c[1]/b[1];
    for(int i=2; i<=18; ++i)
        beta[i]=c[i]/(b[i]-a[i]*beta[i-1]);

    //解 Ly=f
    double yi[21]={0};
    yi[1]=d[1]/b[1];
    for(int i=2; i<=19; ++i)
        yi[i]=(d[i]-a[i]*yi[i-1])/(b[i]-a[i]*beta[i-1]);

    //解 Ux=y
    double m[21]={0};   //这里的 m 即 追赶法中要求解的 x
    m[19]=yi[19];
    for(int i=18; i>=1; --i)
        m[i]=yi[i]-beta[i]*m[i+1];

    //带入端点条件计算端点值
    m[0]=(6*((y[1]-y[0])/h-f_(-1))/h-m[1])/2;
    m[20]=(6*(f_(-1)-(y[20]-y[19])/h)/h-m[19])/2;

    double x_[21]={0};
    for(int i=1; i<=20; ++i)
        x_[i]=-1.05+0.1*i;

    double s20[21]={0};
    for(int i=1; i<=20; ++i)
        s20[i]=s(i,x,m,y,h,x_[i]);

    double x2[11];
    for(int i=0; i<=10; ++i)
        x2[i]=1-0.2*i;

    //Lagrange插值法 第五章1-16
    double l10[21]={0};
    for(int n=1; n<=20; ++n)
        l10[n]=l(10,x2,x_[n]);

    //输出
    cout<<"x\t\t\tf(x)\t\t\tS20(x)\t\t\tL10(x)\n";
    for(int i=1; i<=20; ++i)
        cout<<fixed<<setprecision(7)<<x_[i]<<"\t\t"<<f(x_[i])<<"\t\t"<<s20[i]<<"\t\t"<<l10[i]<<"\n";

    return 0;
}
