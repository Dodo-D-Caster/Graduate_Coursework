//ʵ���
//�Ľ���Cholesky����

#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

int main()
{  
    double h[101][101]; //h ϣ�����ؾ���
    double x[101]={1};  //x hn*x=bn
    double x_[101]={0}; //x_ ����ֵ
    double dx[101]={0}; //����x x_-x
    double b[101]={0};  //b bn=hn*x
    double l[101][101]; //L
    double d[101]={0};  //D
    double c[101][101]; //c
    double y[101]={0};  //y
    double r[101]={0};  //r

    //h ϣ�����ؾ��� �� x ��ֵ
    //ʵ��ʹ�ô�h[1][1]��ʼ
    for(int i=1; i<=100; ++i){
        for(int j=1; j<=100; ++j)
            h[i][j]=1.0/(i+j-1);
        x[i]=1;
    }

    int n=2;    //��ʼ����
    while(n<=100){
        //Ϊb��0
        for(int i=1; i<=n; ++i)
            b[i]=0;

        //b bn=hn*x ��ֵ
        for(int i=1; i<=n; ++i)
            for(int j=1; j<=n; ++j)
                b[i]+=h[i][j];

        d[1]=h[1][1];

        //�ֽ�A=L*D*LT
        for(int i=2; i<=n; ++i){
            //(1)
            for(int j=1; j<=i-1; ++j){
                double sum=0; //�ۼ� c[i][k]*l[j][k]

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

        //�� h*x=b
        //(1)�� L*y=b
        y[1]=b[1];
        for(int i=2; i<=n; ++i){
            double sum=0;   //�ۼ� l[i][k]*y[k]
            for(int k=1; k<=i-1; ++k)
                sum+=l[i][k]*y[k];

            y[i]=b[i]-sum;
        }

        //(2)�� LT*x=D^-1*y
        x_[n]=y[n]/d[n];
        for(int i=n-1; i>=1; --i){
            double sum=0;   //�ۼ� l[k][i]*x[k]
            for(int k=i+1; k<=n; ++k)
                sum+=l[k][i]*x[k];

            x_[i]=y[i]/d[i]-sum;
        }

        //rn=bn-Hn*x_
        for(int i=1; i<=n; ++i){
            double sum=0;   //���� Hi*x
            for(int j=1; j<=n; ++j)
                sum+=h[i][j]*x_[i];

            r[i]=b[i]-sum;
        }

        //dx=x_-x
        for(int i=1; i<=n; ++i)
            dx[i]=x_[i]-x[i];

        //���
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

        //�ж����� x_��û����Ч����
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
            cout<<"��n="<<n<<"ʱ��x_��һλ��Ч����Ҳû��";
            break;
        }
    }
    return 0;
}

