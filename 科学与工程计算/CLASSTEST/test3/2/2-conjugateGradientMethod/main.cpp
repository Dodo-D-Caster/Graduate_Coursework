//实验三(2)（三） 共轭梯度法

#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

//判断精度 ||x[k]-x[k-1]||2 < 1e-6
bool judge(int m, double x[], double y[]) {
    double dx[100], tmp, sum=0;
    for(int i=0; i<m; ++i){
        dx[i]=x[i]-y[i];
        sum+=dx[i]*dx[i];
    }
    tmp=sqrt(sum);

    if(tmp>=1e-6)
        return 1;
    else
        return 0;
}

int main()
{
    //阶数
    for(int m=2; m<=10; ++m){
        cout<<"方程阶数："<<m<<endl;

        double a[100][100];
        double b[100]={0};

        for(int i=0; i<m; ++i)
            for(int j=0; j<m; ++j){
                a[i][j]=1.0/(i+j+1);
                b[i]+=a[i][j];
            }

        double x[100]={0};  //xk 并赋初值
        double y[100]={0};  //xk-1 保存前一个xk 赋合适的初值使得精度不满足判断条件
        for(int i=0; i<m; ++i)
            y[i]=1;

        double r[100]={0};
        double p[100]={0};
        double alpha=0;
        double r2[100]={0};
        double beta=0;

        //r=b-Ax  p=r
        for(int i=0; i<m; ++i){
            r[i]=b[i]-0;
            p[i]=r[i];
        }

        int n=0;
        bool jd2=0;  //用于判断收敛性

        while(judge(m,x,y)){
            //y存储上一个x的值
            for(int i=0; i<m; ++i)
                y[i]=x[i];

            //计算alpha （计算搜索步长）  alpha=(rT*r)/(pT*A*p)
            double sum1=0;
            double sum2=0;
            double sum3=0;
            for(int i=0; i<m; ++i){
                sum1+=r[i]*r[i];
                sum2=0;
                for(int j=0; j<m; ++j)
                    sum2+=p[j]*a[j][i];
                sum3+=sum2*p[i];
            }
            alpha=1.0*sum1/sum3;

            //计算x (更新解) x=x+alpha*p
            for(int i=0; i<m; ++i)
                x[i]=x[i]+alpha*p[i];

            //计算r2  r2=r
            for(int i=0; i<m; ++i)
                r2[i]=r[i];

            //计算r（更新残差向量）   r=r-alpha*A*p
            for(int i=0; i<m; ++i){
                double sum=0;
                for(int j=0; j<m; ++j)
                    sum+=a[i][j]*p[j];
                r[i]=r[i]-alpha*sum;
            }

            //计算beta    beta=(rT*r)/(r2T*r2)
            double sum4=0;
            double sum5=0;
            for(int i=0; i<m; ++i){
                sum4+=r[i]*r[i];
                sum5+=r2[i]*r2[i];
            }
            beta=1.0*sum4/sum5;

            //计算p（新的搜索方向）   p=r+beta*p
            for(int i=0; i<m; ++i)
                p[i]=r[i]+beta*p[i];

            n++;

            //判断收敛性
            bool jd=1;
            for(int i=0; i<m; ++i)
                if(fabs(x[i])<1000)
                    jd=0;
            if(jd){
                jd2=1;
                break;
            }
        }
        //输出
        if(jd2){
            cout<<"不收敛"<<endl;
            cout<<endl;
        }
        else{
            cout<<"迭代初值：xT={0";
            for(int i=1; i<m; ++i)
                cout<<",0";
            cout<<"}"<<endl;
            cout<<"迭代终值：xT={"<<x[0];
            for(int i=1; i<m; ++i)
                cout<<","<<x[i];
            cout<<"}"<<endl;
            cout<<"迭代次数："<<n<<endl;
            cout<<endl;
        }
    }
    return 0;
}
