#include <stdio.h>
#include <process.h>
#define N 10

//����ִ�����������ѵı���
int in = 0, out = 0;

//�߳̽����ı�־
int flg_pro = 0, flg_con = 0;

//mutex�������ź�����ʵ���̶߳Ի���صĻ�����ʣ�
//empty��full����Դ�ź������ֱ��ʾ������пջ���غ�������ص�����(ע���ֵ���������ߵĽǶ�)
int mutex = 1, empty = N, full = 0;

//��ӡ����
void print(char c)
{
    printf("%c    һ��������%d����Դ��������%d����Դ��������%d����Դ\n", c, in, out, full);
}

//����ĳ����Դ
void wait(int *x)
{
    while ((*x) <= 0)
        ;
    (*x)--;
}

//�ͷ�ĳ����Դ
void signal(int *x)
{
    (*x)++;
}

//������
void produce(void *a)
{
    while (1)
    {
        printf("��ʼ����������\n");
        wait(&empty); //����һ���������������������̷߳���
        wait(&mutex);
        printf("��������������\n");

        in++;

        signal(&mutex);
        signal(&full); //full��һ�����������ߣ����������߿�������

        printf("��������������\n");
        print('p');

        Sleep(200);
        if (flg_pro == 1)
        {
            _endthread();
        }
    }
}

//������
void consumer(void *a)
{
    while (1)
    {
        printf("��ʼ����������\n");
        wait(&full);
        wait(&mutex);
        printf("��������������\n");

        out++;

        signal(&mutex);
        signal(&empty);
        printf("�������ѡ�����\n");
        print('c');

        Sleep(200);
        if (flg_con == 1)
        {
            _endthread();
        }
    }
}

//������
int main()
{
    _beginthread(consumer, 0, NULL);
    _beginthread(produce, 0, NULL);
    //�ܵ�ִ��ʱ��Ϊ1����
    Sleep(10000);
    flg_pro = flg_con = 1;
    system("pause");
    return 0;
}