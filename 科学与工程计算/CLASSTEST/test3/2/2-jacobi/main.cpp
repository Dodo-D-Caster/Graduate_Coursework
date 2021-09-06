//ʵ����(2)��һ�� �ſɱ�

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

int main(){
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

        int n=0;    //��¼��������
        bool jd2=0;  //�����ж�������

        while (judge(m,x,y)) {
            //y�洢��һ��x��ֵ
            for (int i=0; i<m; ++i)
                y[i] = x[i];

            for (int i=0; i<m; ++i){
                double sum=0;
                for(int j=0; j<m; ++j)
                    if(j!=i)
                        sum+=a[i][j]*y[j];

                x[i]=1.0*(b[i]-sum)/a[i][i];
            }

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
