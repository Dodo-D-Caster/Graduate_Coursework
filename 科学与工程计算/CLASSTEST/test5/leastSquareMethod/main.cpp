//实验五 最小二乘数法

#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

//f(x)
double f(double x){
    return 1.0/(1+25*x*x);
}

//选取基函数
double phi(int i, double x){
    return pow(x,i);
}

//计算 S(x)
//x: 要求的节点  m:拟合函数次数
double s(int m, double a[], double x){
    double sum=0;
    for(int i=0; i<=m; ++i)
        sum+=a[i]*phi(i,x);
    return sum;
}


//对比用，代码在实验四基础上修改
////////////////////////////////////////////////////////////////////////
//f'(x)
double f_(double x){
    return -50*x/((1+25*x*x)*(1+25*x*x));
}

//三次样条插值函数 S(x)
//i表示 si(x)
//x_表示 -0.95~0.95的插值节点
double s2(int i, double x[], double m[], double y[], double h, double x_){
    return m[i-1]*(x[i]-x_)*(x[i]-x_)*(x[i]-x_)/(6*h)
            +m[i]*(x_-x[i-1])*(x_-x[i-1])*(x_-x[i-1])/(6*h)
            +(y[i-1]-m[i-1]/6*h*h)*(x[i]-x_)/h
            +(y[i]-m[i]/6*h*h)*(x_-x[i-1])/h;
}

//Lagrange插值法 l(x)
//n表示 ln(x)
//x_表示插值节点
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
//////////////////////////////////////////////////////////////////////////

//计算法方程 共轭梯度法
/////////////////////////////////////////////////////////////////////////
//判断精度 ||x[k]-x[k-1]||2 < 1e-6
bool judge(int m, double x[], double y[]) {
    double dx[100], tmp, sum=0;
    for(int i=0; i<=m; ++i){
        dx[i]=x[i]-y[i];
        sum+=dx[i]*dx[i];
    }
    tmp=sqrt(sum);

    if(tmp>=1e-6)
        return 1;
    else
        return 0;
}
////////////////////////////////////////////////////////////////////////////

int main(){
    //节点个数
    for(int n=2; n<=20; ++n){
        cout<<"n="<<n<<endl;

        double x[100]={0};  //x 等距节点
        double x_[100]={0}; //x_ 要求的节点
        double y[100]={0};  //y 节点值
        for(int i=0; i<=n; ++i){
            x[i]=-1+2.0*i/n;
            y[i]=f(x[i]);
        }

        for(int i=0; i<n; ++i)
            x_[i]=(x[i]+x[i+1])/2;

        //法方程
        double a[100][100];
        double b[100]={0};
        double af[100]={0};

        int m[2]={3,4}; //拟合函数次数
        for(int mi=0; mi<2; ++mi){
            cout<<"拟合函数次数："<<m[mi]<<endl;

            //a, b, af 清0
            for(int i=0; i<=m[mi]; ++i){
                for(int j=0; j<=m[mi]; ++j)
                    a[i][j]=0;
                b[i]=0;
                af[i]=0;
            }

            for(int i=0; i<=m[mi]; ++i){
                for(int j=0; j<=m[mi]; ++j){
                    for(int k=0; k<=n; ++k)
                        a[i][j]+=phi(i,x[k])*phi(j,x[k]);
                }
                for(int k=0; k<=n; ++k)
                    b[i]+=y[k]*phi(i,x[k]);
            }

            //计算法方程 共轭梯度法
            /////////////////////////////////////////////////////////////////////////
            double xf[100]={0};  //xk 并赋初值
            double yf[100]={0};  //xk-1 保存前一个xk 赋合适的初值使得精度不满足判断条件
            for(int i=0; i<=m[mi]; ++i)
                yf[i]=1;

            double r[100]={0};
            double p[100]={0};
            double alpha=0;
            double r2[100]={0};
            double betaf=0;

            //r=b-Ax  p=r
            for(int i=0; i<=m[mi]; ++i){
                r[i]=b[i]-0;
                p[i]=r[i];
            }

            bool jd2=0;  //用于判断收敛性

            while(judge(m[mi],xf,yf)){
                //yf存储上一个x的值
                for(int i=0; i<=m[mi]; ++i)
                    yf[i]=xf[i];

                //计算alpha （计算搜索步长）  alpha=(rT*r)/(pT*A*p)
                double sum1=0;
                double sum2=0;
                double sum3=0;
                for(int i=0; i<=m[mi]; ++i){
                    sum1+=r[i]*r[i];
                    sum2=0;
                    for(int j=0; j<=m[mi]; ++j)
                        sum2+=p[j]*a[j][i];
                    sum3+=sum2*p[i];
                }
                alpha=1.0*sum1/sum3;

                //计算x (更新解) x=x+alpha*p
                for(int i=0; i<=m[mi]; ++i)
                    xf[i]=xf[i]+alpha*p[i];

                //计算r2  r2=r
                for(int i=0; i<=m[mi]; ++i)
                    r2[i]=r[i];

                //计算r（更新残差向量）   r=r-alpha*A*p
                for(int i=0; i<=m[mi]; ++i){
                    double sum=0;
                    for(int j=0; j<=m[mi]; ++j)
                        sum+=a[i][j]*p[j];
                    r[i]=r[i]-alpha*sum;
                }

                //计算beta    beta=(rT*r)/(r2T*r2)
                double sum4=0;
                double sum5=0;
                for(int i=0; i<=m[mi]; ++i){
                    sum4+=r[i]*r[i];
                    sum5+=r2[i]*r2[i];
                }
                betaf=1.0*sum4/sum5;

                //计算p（新的搜索方向）   p=r+beta*p
                for(int i=0; i<=m[mi]; ++i)
                    p[i]=r[i]+betaf*p[i];

                //判断收敛性
                bool jd=1;
                for(int i=0; i<=m[mi]; ++i)
                    if(fabs(xf[i])<1000)
                        jd=0;
                if(jd){
                    jd2=1;
                    break;
                }
            }
            //输出
            if(jd2){
                cout<<"法方程不收敛"<<endl;
            }
            else{
                for(int i=0; i<=m[mi]; ++i){
                    af[i]=xf[i];
                }
            }
            /////////////////////////////////////////////////////////////////////////


            //(与拉格朗日插值法与三次样条插值法)对比用，代码在实验四基础上修改
            ///////////////////////////////////////////////////////////////////////
            //三次样条插值
            double h=2.0/n;   //h=2/N
            double lambda=0.5;  //由于等距节点 lambda=h/(h+h)=1/2
            double mu=0.5;      //mu=1-lambda=1/2
            int ci=2;

            double d[100]={0};
            //由于等距节点 求 d[1]-d[19] 的值
            for(int i=1; i<n; ++i)
                d[i]=3.0/(h*h)*(y[i+1]-2*y[i]+y[i-1]);

            //解 n-1阶 三对角方程组
            //采用 追赶法    第三章1-64   a=mu b=c c=lambda x=m f=d
            double a2[100]={0};
            double b2[100]={0};
            double c[100]={0};

            for(int i=1; i<=n-1; ++i){
                a2[i]=mu;
                b2[i]=ci;
                c[i]=lambda;
            }
            a2[1]=0;
            c[n-1]=0;

            //计算 beta[i] 的递推公式
            double beta[100]={0};
            beta[1]=c[1]/b2[1];
            for(int i=2; i<=n-2; ++i)
                beta[i]=c[i]/(b2[i]-a2[i]*beta[i-1]);

            //解 Ly=f
            double yi[100]={0};
            yi[1]=d[1]/b2[1];
            for(int i=2; i<=n-1; ++i)
                yi[i]=(d[i]-a2[i]*yi[i-1])/(b2[i]-a2[i]*beta[i-1]);

            //解 Ux=y
            double m2[100]={0};   //这里的 m 即 追赶法中要求解的 x
            m2[n-1]=yi[n-1];
            for(int i=n-2; i>=1; --i)
                m2[i]=yi[i]-beta[i]*m2[i+1];

            //带入端点条件计算端点值
            m2[0]=(6*((y[1]-y[0])/h-f_(-1))/h-m2[1])/2;
            m2[n]=(6*(f_(-1)-(y[n]-y[n-1])/h)/h-m2[n-1])/2;

            double sn[100]={0};
            for(int i=1; i<=n; ++i)
                sn[i-1]=s2(i,x,m2,y,h,x_[i-1]);

            double x2[100];
            for(int i=0; i<=n/2; ++i)
                x2[i]=1-2.0/(n/2)*i;

            //Lagrange插值法 第五章1-16
            double ln_[100]={0};
            int n_=n/2; //计算 Ln_
            for(int i=1; i<=n; ++i)
                ln_[i-1]=l(n_,x2,x_[i-1]);
            ///////////////////////////////////////////////////////////////////////

            //输出
            cout<<"x\t\t\tf(x)\t\t\ts(x)\t\t\tS"<<n<<"(x)\t\t\tL"<<n/2<<"(x)\n";
            for(int i=0; i<n; ++i)
                cout<<fixed<<setprecision(7)<<x_[i]<<"\t\t"<<f(x_[i])<<"\t\t"
                    <<s(m[mi],af,x_[i])<<"\t\t"<<sn[i]<<"\t\t"<<ln_[i]<<endl;
            cout<<endl;
        }

    }
    return 0;
}
