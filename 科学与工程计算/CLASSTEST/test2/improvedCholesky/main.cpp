//实验二
//改进的Cholesky方法

#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

int main()
{  
    double h[101][101]; //h 希尔伯特矩阵
    double x[101]={1};  //x hn*x=bn
    double x_[101]={0}; //x_ 所求值
    double dx[101]={0}; //吊塔x x_-x
    double b[101]={0};  //b bn=hn*x
    double l[101][101]; //L
    double d[101]={0};  //D
    double c[101][101]; //c
    double y[101]={0};  //y
    double r[101]={0};  //r

    //h 希尔伯特矩阵 和 x 赋值
    //实际使用从h[1][1]开始
    for(int i=1; i<=100; ++i){
        for(int j=1; j<=100; ++j)
            h[i][j]=1.0/(i+j-1);
        x[i]=1;
    }

    int n=2;    //初始阶数
    while(n<=100){
        //为b清0
        for(int i=1; i<=n; ++i)
            b[i]=0;

        //b bn=hn*x 赋值
        for(int i=1; i<=n; ++i)
            for(int j=1; j<=n; ++j)
                b[i]+=h[i][j];

        d[1]=h[1][1];

        //分解A=L*D*LT
        for(int i=2; i<=n; ++i){
            //(1)
            for(int j=1; j<=i-1; ++j){
                double sum=0; //累加 c[i][k]*l[j][k]

                c[i][j]=h[i][j];
                for(int k=1; k<=j-1; ++k)
                    sum+=c[i][k]*l[j][k];

                c[i][j]=h[i][j]-sum;
                l[i][j]=c[i][j]/d[j];
            }

            //(2)
            d[i]=h[i][i];
            for(int k=1; k<=i-1; ++k)
                d[i]-=c[i][k]*l[i][k];
        }

        //解 h*x=b
        //(1)解 L*y=b
        y[1]=b[1];
        for(int i=2; i<=n; ++i){
            double sum=0;   //累加 l[i][k]*y[k]
            for(int k=1; k<=i-1; ++k)
                sum+=l[i][k]*y[k];

            y[i]=b[i]-sum;
        }

        //(2)解 LT*x=D^-1*y
        x_[n]=y[n]/d[n];
        for(int i=n-1; i>=1; --i){
            double sum=0;   //累加 l[k][i]*x[k]
            for(int k=i+1; k<=n; ++k)
                sum+=l[k][i]*x[k];

            x_[i]=y[i]/d[i]-sum;
        }

        //rn=bn-Hn*x_
        for(int i=1; i<=n; ++i){
            double sum=0;   //存贮 Hi*x
            for(int j=1; j<=n; ++j)
                sum+=h[i][j]*x_[i];

            r[i]=b[i]-sum;
        }

        //dx=x_-x
        for(int i=1; i<=n; ++i)
            dx[i]=x_[i]-x[i];

        //输出
        //n x_
        cout<<"n: "<<n<<"\tx_T={";
        for(int i=1; i<=n-1; ++i)
            cout<<x_[i]<<",";
        cout<<x_[n]<<"}"<<endl;

        //r
        cout<<endl<<"\trT={";
        for(int i=1; i<=n-1; ++i)
            cout<<r[i]<<",";
        cout<<r[n]<<"}"<<endl;

        //dx
        cout<<endl<<"\tdx={";
        for(int i=1; i<=n-1; ++i)
            cout<<dx[i]<<",";
        cout<<dx[n]<<"}"<<endl;

        cout<<endl;

        //判断条件 x_有没有有效数字
        bool judge=1;
        for(int i=1; i<=n; ++i){
            if(fabs(x_[i]-x[i])>0.5){
                judge=0;
                break;
            }
        }
        if(judge==1)
            ++n;
        else{
            cout<<"当n="<<n<<"时，x_连一位有效数字也没有";
            break;
        }
    }
    return 0;
}

