#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

// xk+1 = f(xk)
double f(double x,double x2){
    return x-(((x*x*x-3*x-1)/((x*x*x-3*x-1)-(x2*x2*x2-3*x2-1)))*(x-x2));
}

int main()
{
    double x,x2,xt;
    //x ´æ´¢ xk
    //x2 ´æÖü xk-1
    //xt ÔÝ´æ xk-1
    int k;
    k=1; //¼ÆÊý
    x=1.9; //Áîx=x1
    x2=2; //Áîx2=x0
    while(true){
        cout<<"k:"<<k<<"\t"<<"x"<<k<<":"<<x<<endl;
        xt=x;
        x=f(x,x2);
        x2=xt;
        k++;
        if(fabs(x-x2)<0.00005){
            cout<<"k:"<<k<<"\t"<<"x"<<k<<":"<<x<<endl;
            break;
        }
    }
    return 0;
}
