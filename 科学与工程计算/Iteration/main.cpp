#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

// xk+1 = f(xk)
double f(double x){
    //return x-(x*x*x-3*x-1)/(3*x*x-3);
    return (2-exp(x))/10;
}

int main()
{
    double x,xt;
    //xt ���� xk-1
    int k;
    k=0; //����
    x=0; //��x=x0

    while(true){
        cout<<"k:"<<k<<"\t"<<"x"<<k<<":"<<x<<endl;
        xt=x;
        x=f(x);
        k++;
        if(fabs(x-xt)<0.00005){
            cout<<"k:"<<k<<"\t"<<"x"<<k<<":"<<x<<endl;
            break;
        }
    }
}
