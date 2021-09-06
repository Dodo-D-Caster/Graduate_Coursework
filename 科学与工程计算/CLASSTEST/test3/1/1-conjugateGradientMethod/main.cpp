//实验三(1)（三） 共轭梯度法

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

int main()
{
    double a[4][4];
    double b[4];

    a[0][0]=10;	a[0][1]=-7;         a[0][2]=0;	a[0][3]=1;  b[0]=8;
    a[1][0]=-3;	a[1][1]=2.099999;	a[1][2]=6;  a[1][3]=2;  b[1]=5.900001;
    a[2][0]=5;	a[2][1]=-1;         a[2][2]=5;  a[2][3]=-1; b[2]=5;
    a[3][0]=2;  a[3][1]=1;          a[3][2]=0;  a[3][3]=2;  b[3]=1;

    double x[4]={0,0,0,0};  //xk 并赋初值
    double y[4]={1,1,1,1};  //xk-1 保存前一个xk 赋合适的初值使得精度不满足判断条件

    double r[4]={0};
    double p[4]={0};
    double alpha=0;
    double r2[4]={0};
    double beta=0;

    //r=b-Ax  p=r
    for(int i=0; i<4; ++i){
        r[i]=b[i]-0;
        p[i]=r[i];
    }

    int n=0;

    while(judge(x,y)){
        //y存储上一个x的值
        for(int i=0; i<4; ++i)
            y[i]=x[i];

        //计算alpha （计算搜索步长）  alpha=(rT*r)/(pT*A*p)
        double sum1=0;
        double sum2=0;
        double sum3=0;
        for(int i=0; i<4; ++i){
            sum1+=r[i]*r[i];
            sum2=0;
            for(int j=0; j<4; ++j)
                sum2+=p[j]*a[j][i];
            sum3+=sum2*p[i];
        }
        alpha=1.0*sum1/sum3;

        //计算x (更新解) x=x+alpha*p
        for(int i=0; i<4; ++i)
            x[i]=x[i]+alpha*p[i];

        //计算r2  r2=r
        for(int i=0; i<4; ++i)
            r2[i]=r[i];

        //计算r（更新残差向量）   r=r-alpha*A*p
        for(int i=0; i<4; ++i){
            double sum=0;
            for(int j=0; j<4; ++j)
                sum+=a[i][j]*p[j];
            r[i]=r[i]-alpha*sum;
        }

        //计算beta    beta=(rT*r)/(r2T*r2)
        double sum4=0;
        double sum5=0;
        for(int i=0; i<4; ++i){
            sum4+=r[i]*r[i];
            sum5+=r2[i]*r2[i];
        }
        beta=1.0*sum4/sum5;

        //计算p（新的搜索方向）   p=r+beta*p
        for(int i=0; i<4; ++i)
            p[i]=r[i]+beta*p[i];

        n++;

        //判断收敛性
        if(fabs(x[0])>1000&&fabs(x[1])>1000&&fabs(x[2])>1000&&fabs(x[3])>1000)
            break;
    }
    //输出
    if(fabs(x[0])>1000&&fabs(x[1])>1000&&fabs(x[2])>1000&&fabs(x[3])>1000)
        cout<<"不收敛"<<endl;
    else{
        cout<<"迭代初值：xT={0,0,0,0}"<<endl;
        cout<<"迭代终值：xT={"<<x[0]<<","<<x[1]<<","<<x[2]<<","<<x[3]<<"}"<<endl;
        cout<<"迭代次数："<<n<<endl;
        cout<<endl;
    }
    return 0;
}
