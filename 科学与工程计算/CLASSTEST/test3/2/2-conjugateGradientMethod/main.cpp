//ʵ����(2)������ �����ݶȷ�

#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

//�жϾ��� ||x[k]-x[k-1]||2 < 1e-6
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
    //����
    for(int m=2; m<=10; ++m){
        cout<<"���̽�����"<<m<<endl;

        double a[100][100];
        double b[100]={0};

        for(int i=0; i<m; ++i)
            for(int j=0; j<m; ++j){
                a[i][j]=1.0/(i+j+1);
                b[i]+=a[i][j];
            }

        double x[100]={0};  //xk ������ֵ
        double y[100]={0};  //xk-1 ����ǰһ��xk �����ʵĳ�ֵʹ�þ��Ȳ������ж�����
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
        bool jd2=0;  //�����ж�������

        while(judge(m,x,y)){
            //y�洢��һ��x��ֵ
            for(int i=0; i<m; ++i)
                y[i]=x[i];

            //����alpha ����������������  alpha=(rT*r)/(pT*A*p)
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

            //����x (���½�) x=x+alpha*p
            for(int i=0; i<m; ++i)
                x[i]=x[i]+alpha*p[i];

            //����r2  r2=r
            for(int i=0; i<m; ++i)
                r2[i]=r[i];

            //����r�����²в�������   r=r-alpha*A*p
            for(int i=0; i<m; ++i){
                double sum=0;
                for(int j=0; j<m; ++j)
                    sum+=a[i][j]*p[j];
                r[i]=r[i]-alpha*sum;
            }

            //����beta    beta=(rT*r)/(r2T*r2)
            double sum4=0;
            double sum5=0;
            for(int i=0; i<m; ++i){
                sum4+=r[i]*r[i];
                sum5+=r2[i]*r2[i];
            }
            beta=1.0*sum4/sum5;

            //����p���µ���������   p=r+beta*p
            for(int i=0; i<m; ++i)
                p[i]=r[i]+beta*p[i];

            n++;

            //�ж�������
            bool jd=1;
            for(int i=0; i<m; ++i)
                if(fabs(x[i])<1000)
                    jd=0;
            if(jd){
                jd2=1;
                break;
            }
        }
        //���
        if(jd2){
            cout<<"������"<<endl;
            cout<<endl;
        }
        else{
            cout<<"������ֵ��xT={0";
            for(int i=1; i<m; ++i)
                cout<<",0";
            cout<<"}"<<endl;
            cout<<"������ֵ��xT={"<<x[0];
            for(int i=1; i<m; ++i)
                cout<<","<<x[i];
            cout<<"}"<<endl;
            cout<<"����������"<<n<<endl;
            cout<<endl;
        }
    }
    return 0;
}
