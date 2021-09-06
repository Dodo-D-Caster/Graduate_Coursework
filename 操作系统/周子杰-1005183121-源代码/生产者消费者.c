#include <stdio.h>
#include <process.h>
#define N 10

//代表执行生产和消费的变量
int in = 0, out = 0;

//线程结束的标志
int flg_pro = 0, flg_con = 0;

//mutex：互斥信号量，实现线程对缓冲池的互斥访问；
//empty和full：资源信号量，分别表示缓冲池中空缓冲池和满缓冲池的数量(注意初值，从生产者的角度)
int mutex = 1, empty = N, full = 0;

//打印测试
void print(char c)
{
    printf("%c    一共生产了%d个资源，消费了%d个资源，现在有%d个资源\n", c, in, out, full);
}

//请求某个资源
void wait(int *x)
{
    while ((*x) <= 0)
        ;
    (*x)--;
}

//释放某个资源
void signal(int *x)
{
    (*x)++;
}

//生产者
void produce(void *a)
{
    while (1)
    {
        printf("开始阻塞生产者\n");
        wait(&empty); //申请一个缓冲区，看有无其他线程访问
        wait(&mutex);
        printf("结束阻塞生产者\n");

        in++;

        signal(&mutex);
        signal(&full); //full加一，唤醒消费者，告诉消费者可以消费

        printf("结束生产。。。\n");
        print('p');

        Sleep(200);
        if (flg_pro == 1)
        {
            _endthread();
        }
    }
}

//消费者
void consumer(void *a)
{
    while (1)
    {
        printf("开始阻塞消费者\n");
        wait(&full);
        wait(&mutex);
        printf("结束阻塞消费者\n");

        out++;

        signal(&mutex);
        signal(&empty);
        printf("结束消费。。。\n");
        print('c');

        Sleep(200);
        if (flg_con == 1)
        {
            _endthread();
        }
    }
}

//主函数
int main()
{
    _beginthread(consumer, 0, NULL);
    _beginthread(produce, 0, NULL);
    //总的执行时间为1分钟
    Sleep(10000);
    flg_pro = flg_con = 1;
    system("pause");
    return 0;
}