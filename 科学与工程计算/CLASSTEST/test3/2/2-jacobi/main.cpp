//实验三(2)（一） 雅可比

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

int main(){
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

        int n=0;    //记录迭代次数
        bool jd2=0;  //用于判断收敛性

        while (judge(m,x,y)) {
            //y存储上一个x的值
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
