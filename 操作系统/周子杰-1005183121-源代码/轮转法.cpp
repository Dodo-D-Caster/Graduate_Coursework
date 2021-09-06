/*
测试数据：
1 8 3 2
1 1
2 2
3 1
4 3
5 2
6 5
7 1
8 3
9 4
*/
#include <stdio.h>
#include <stdlib.h>

struct PCB
{
    int pid;       //进程id
    int totaltime; //要求运行时间
    int waittime;  //等待时间
    int runtime;   //服务时间
} pcb[100];

int n;  //就绪状态进程个数
int m;  //阻塞状态进程个数
int t;  //释放资源时间
int tt; //时间片大小

//轮转法
void RR()
{
    for (int i = 0; i < n; ++i)
        printf("进程%d初始状态：\t服务时间:%d\t需要时间:%d\t等待时间:%d\n", pcb[i].pid, pcb[i].runtime, pcb[i].totaltime, pcb[i].waittime);

    int count = 0;      //时间片个数
    int wastedTime = 0; //CPU空转时间
    int cn = 0;         //当前运行的进程

    while (n > 0 || m > 0)
    {
        //唤醒一个阻塞进程
        if (count % t == 0 && m > 0)
        {
            printf("阻塞进程%d被唤醒\n", pcb[n].pid);
            n++;
            m--;
        }

        //判断空转
        if (n == 0 && m != 0)
        {
            count++;
            wastedTime += tt;
            for (int i = 0; i < m; ++i)
                pcb[i].waittime += tt;
            continue;
        }

        //模拟循环队列
        if (cn == n - 1)
        {
            cn = 0;
        }

        //当前进程运行
        count++;
        pcb[cn].runtime += tt;
        //其余进程等待时间+1
        for (int i = 0; i < n; ++i)
        {
            if (i != cn)
                pcb[i].waittime += tt;
        }
        printf("第%d片时间: 进程%d运行\t服务时间:%d\t需要时间:%d\t等待时间:%d\n", count, pcb[cn].pid, pcb[cn].runtime, pcb[cn].totaltime, pcb[cn].waittime);

        //判断是否完成
        if (pcb[cn].runtime >= pcb[cn].totaltime)
        {
            int wt = tt * (pcb[cn].runtime - pcb[cn].totaltime);
            wastedTime += tt;
            for (int i = 0; i < m + n; ++i)
                pcb[i].waittime += tt;
            printf("第%d片时间: 进程%d结束\n", count, pcb[cn].pid);
            //释放pcb[cn]
            for (int i = cn; i < n + m; ++i)
            {
                pcb[i].pid = pcb[i + 1].pid;
                pcb[i].runtime = pcb[i + 1].runtime;
                pcb[i].totaltime = pcb[i + 1].totaltime;
                pcb[i].waittime = pcb[i + 1].waittime;
            }
            n--;
        }
    }

    printf("CPU利用率 = (总时间-浪费时间) / 总时间 * 100% = %.2f%", (1.0 * count * tt - 1.0 * wastedTime) / (1.0 * count * tt) * 100);
}

int main()
{
    printf("就绪状态进程个数 阻塞状态进程个数 释放资源时间t 时间片大小tt\n");
    scanf("%d%d%d%d", &n, &m, &t, &tt);

    for (int i = 0; i < n; ++i)
    {
        printf("就绪状态进程的进程号 需要时间 : ");
        scanf("%d %d", &pcb[i].pid, &pcb[i].totaltime);
        pcb[i].runtime = 0;
        pcb[i].waittime = 0;
    }
    for (int i = n; i < n + m; ++i)
    {
        printf("阻塞状态进程的进程号 需要时间 : ");
        scanf("%d %d", &pcb[i].pid, &pcb[i].totaltime);
        pcb[i].runtime = 0;
        pcb[i].waittime = 0;
    }

    RR();
    return 0;
}
