//实验三(1)（二） SOR

#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

//判断精度 ||x[k]-x[k-1]||2 < 1e-6
bool judge(double x[], double y[]) {
    double x1, x2, x3, x4, tmp;
    x1=y[0]-x[0];
    x2=y[1]-x[1];
    x3=y[2]-x[2];
    x4=y[3]-x[3];
    tmp=sqrt(x1*x1+x2*x2+x3*x3+x4*x4);

    if(tmp>=1e-6)
        return 1;
    else
        return 0;
}

int main() {
    double a[4][4];
    double b[4];
    double w[3]={1,1.25,1.5};

    a[0][0]=10;	a[0][1]=-7;         a[0][2]=0;	a[0][3]=1;  b[0]=8;
    a[1][0]=-3;	a[1][1]=2.099999;	a[1][2]=6;  a[1][3]=2;  b[1]=5.900001;
    a[2][0]=5;	a[2][1]=-1;         a[2][2]=5;  a[2][3]=-1; b[2]=5;
    a[3][0]=2;  a[3][1]=1;          a[3][2]=0;  a[3][3]=2;  b[3]=1;

    int k=0; //对w的三个给定值分别求解
    while(k!=3){
        cout<<"w="<<w[k]<<endl;
        k++;

        double x[4]={0,0,0,0};  //xk 并赋初值
        double y[4]={1,1,1,1};  //xk-1 保存前一个xk 赋合适的初值使得精度不满足判断条件

        int n=0;    //记录迭代次数

        while (judge(x,y)) {
            //y存储上一个x的值
            for (int i=0; i<4; ++i)
                y[i] = x[i];

            for (int i=0; i<4; ++i){
                double sum=0;
                for(int j=0; j<4; ++j)
                    if(j!=i)
                        sum+=a[i][j]*x[j];

                x[i]=(1-w[k-1])*x[i]+1.0*w[k-1]*(b[i]-sum)/a[i][i];
            }

            n++;

            //判断收敛性
            if(fabs(x[0])>1000&&fabs(x[1])>1000&&fabs(x[2])>1000&&fabs(x[3])>1000)
                break;
        }
        //输出
        if(fabs(x[0])>1000&&fabs(x[1])>1000&&fabs(x[2])>1000&&fabs(x[3])>1000){
            cout<<"不收敛"<<endl;
            cout<<endl;
        }
        else{
            cout<<"迭代初值：xT={0,0,0,0}"<<endl;
            cout<<"迭代终值：xT={"<<x[0]<<","<<x[1]<<","<<x[2]<<","<<x[3]<<"}"<<endl;
            cout<<"迭代次数："<<n<<endl;
            cout<<endl;
        }
    }
    return 0;
}
