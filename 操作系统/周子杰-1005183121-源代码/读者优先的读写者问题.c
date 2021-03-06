/*
读者优先
测试数据：
1 R 3 5
2 W 4 5
3 R 5 2
4 R 6 5
5 W 7 3
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <pthread.h>
#include <semaphore.h>
#include <string.h>
#include <unistd.h>

//semaphores
sem_t wrt, mutex;
int readCount;

struct data
{
    int id;
    int opTime;
    int lastTime;
};

//读者
void *Reader(void *param)
{
    int id = ((struct data *)param)->id;
    int lastTime = ((struct data *)param)->lastTime;
    int opTime = ((struct data *)param)->opTime;

    sleep(opTime);
    printf("线程 %d: 等待读\n", id);
    sem_wait(&mutex);
    readCount++;
    if (readCount == 1)
        sem_wait(&wrt);
    sem_post(&mutex);

    printf("线程 %d: 开始读\n", id);
    /* reading is performed */
    sleep(lastTime);
    printf("线程 %d: 结束读\n", id);

    sem_wait(&mutex);
    readCount--;
    if (readCount == 0)
        sem_post(&wrt);
    sem_post(&mutex);
    pthread_exit(0);
}

//写者
void *Writer(void *param)
{
    int id = ((struct data *)param)->id;
    int lastTime = ((struct data *)param)->lastTime;
    int opTime = ((struct data *)param)->opTime;

    sleep(opTime);
    printf("线程 %d: 等待写\n", id);
    sem_wait(&wrt);

    printf("线程 %d: 开始写\n", id);
    /* writing is performed */
    sleep(lastTime);
    printf("线程 %d: 结束写\n", id);

    sem_post(&wrt);
    pthread_exit(0);
}

int main()
{
    //pthread
    pthread_t tid; // the thread identifier

    pthread_attr_t attr; //set of thread attributes

    /* get the default attributes */
    pthread_attr_init(&attr);

    //initial the semaphores
    sem_init(&mutex, 0, 1);
    sem_init(&wrt, 0, 1);
    readCount = 0;

    int id = 0;
    while (scanf("%d", &id) != EOF)
    {

        char role;    //producer or consumer
        int opTime;   //operating time
        int lastTime; //run time

        scanf("%c%d%d", &role, &opTime, &lastTime);
        struct data *d = (struct data *)malloc(sizeof(struct data));

        d->id = id;
        d->opTime = opTime;
        d->lastTime = lastTime;

        if (role == 'R')
        {
            printf("创建 %d 线程: 读者\n", id);
            pthread_create(&tid, &attr, Reader, d);
        }
        else if (role == 'W')
        {
            printf("创建 %d 线程: 写者\n", id);
            pthread_create(&tid, &attr, Writer, d);
        }
    }

    //信号量销毁
    sem_destroy(&mutex);
    sem_destroy(&wrt);

    return 0;
}