//实验一（二）二分法
//f(x)=x^3-x-1
//f(1)=-1<0
//f(2)=5>0
//由此 有根区间(a,b)确定为(1,2)

#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

//f(x)=x^3-x-1
double f(double x){
    return x*x*x-x-1;
}

int main(){
    double a=1;     //(a,b)赋初值为(1,2)
    double b=2;
    double x=1.5;   //x=(a+b)/2
    double xt=0;    //xt用来存储上一个x
    int k=0;        //k用来计数
    while(fabs(f(x)-f(xt))>=1e-8){ //设置精度
        cout<<"k:"<<k<<"\t"<<fixed<<setprecision(10)
            <<" a:"<<a<<"\t b:"<<b<<"\t x:"<<x<<"\t f(x):"<<f(x)
            <<endl;
        xt=x;
        if(f(x)<0){
            a=x;
            x=(b+x)/2;
        }
        else if(f(x)>0){
            b=x;
            x=(a+x)/2;
        }
        k++;
    }
    return 0;
}

