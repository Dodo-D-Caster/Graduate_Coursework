/*
�������ݣ�
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
    int pid;       //����id
    int totaltime; //Ҫ������ʱ��
    int waittime;  //�ȴ�ʱ��
    int runtime;   //����ʱ��
} pcb[100];

int n;  //����״̬���̸���
int m;  //����״̬���̸���
int t;  //�ͷ���Դʱ��
int tt; //ʱ��Ƭ��С

//��ת��
void RR()
{
    for (int i = 0; i < n; ++i)
        printf("����%d��ʼ״̬��\t����ʱ��:%d\t��Ҫʱ��:%d\t�ȴ�ʱ��:%d\n", pcb[i].pid, pcb[i].runtime, pcb[i].totaltime, pcb[i].waittime);

    int count = 0;      //ʱ��Ƭ����
    int wastedTime = 0; //CPU��תʱ��
    int cn = 0;         //��ǰ���еĽ���

    while (n > 0 || m > 0)
    {
        //����һ����������
        if (count % t == 0 && m > 0)
        {
            printf("��������%d������\n", pcb[n].pid);
            n++;
            m--;
        }

        //�жϿ�ת
        if (n == 0 && m != 0)
        {
            count++;
            wastedTime += tt;
            for (int i = 0; i < m; ++i)
                pcb[i].waittime += tt;
            continue;
        }

        //ģ��ѭ������
        if (cn == n - 1)
        {
            cn = 0;
        }

        //��ǰ��������
        count++;
        pcb[cn].runtime += tt;
        //������̵ȴ�ʱ��+1
        for (int i = 0; i < n; ++i)
        {
            if (i != cn)
                pcb[i].waittime += tt;
        }
        printf("��%dƬʱ��: ����%d����\t����ʱ��:%d\t��Ҫʱ��:%d\t�ȴ�ʱ��:%d\n", count, pcb[cn].pid, pcb[cn].runtime, pcb[cn].totaltime, pcb[cn].waittime);

        //�ж��Ƿ����
        if (pcb[cn].runtime >= pcb[cn].totaltime)
        {
            int wt = tt * (pcb[cn].runtime - pcb[cn].totaltime);
            wastedTime += tt;
            for (int i = 0; i < m + n; ++i)
                pcb[i].waittime += tt;
            printf("��%dƬʱ��: ����%d����\n", count, pcb[cn].pid);
            //�ͷ�pcb[cn]
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

    printf("CPU������ = (��ʱ��-�˷�ʱ��) / ��ʱ�� * 100% = %.2f%", (1.0 * count * tt - 1.0 * wastedTime) / (1.0 * count * tt) * 100);
}

int main()
{
    printf("����״̬���̸��� ����״̬���̸��� �ͷ���Դʱ��t ʱ��Ƭ��Сtt\n");
    scanf("%d%d%d%d", &n, &m, &t, &tt);

    for (int i = 0; i < n; ++i)
    {
        printf("����״̬���̵Ľ��̺� ��Ҫʱ�� : ");
        scanf("%d %d", &pcb[i].pid, &pcb[i].totaltime);
        pcb[i].runtime = 0;
        pcb[i].waittime = 0;
    }
    for (int i = n; i < n + m; ++i)
    {
        printf("����״̬���̵Ľ��̺� ��Ҫʱ�� : ");
        scanf("%d %d", &pcb[i].pid, &pcb[i].totaltime);
        pcb[i].runtime = 0;
        pcb[i].waittime = 0;
    }

    RR();
    return 0;
}
