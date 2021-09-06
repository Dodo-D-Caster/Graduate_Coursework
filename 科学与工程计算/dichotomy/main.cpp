#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;
double f(double x){
    return exp(x)+10*x-2;
}
int main()
{
    double a,b,x,xt;
    // （a,b）区间内 求 函数f 的根
    int i=1;
    a=0;
    b=1;
    x=0.5;
    while(fabs(x-xt)>0.0001){ // 0.001 为精度
        cout<<"k:"<<i<<"\t"<<fixed<<setw(8)<<" a:"<<a<<"\t b:"<<b<<"\t x:"<<x<<"\t f(x):"<<f(x)<<endl;
        xt=x;
        if(f(x)<0){
            a=x;
            x=(b+x)/2;
        }
        else if(f(x)>0){
            b=x;
            x=(a+x)/2;
        }
        i++;
    }
    cout<<"k:"<<i<<"\t"<<fixed<<setw(8)<<" a:"<<a<<"\t b:"<<b<<"\t x:"<<x<<"\t f(x):"<<f(x)<<endl;
    return 0;
}

