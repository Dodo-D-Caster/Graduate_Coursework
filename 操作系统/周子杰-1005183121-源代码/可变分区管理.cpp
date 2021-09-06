/*
测试数据：
循环首次适应算法：
5
50 85
32 155
70 275
60 532
10 980
3
1
1
25
3
2
1
3
0

最佳适应算法：
5
50 85
32 155
70 275
60 532
10 980
3
2
1
25
3
2
1
3
0
*/
#include <iostream>
#include <cmath>
#include <stdio.h>
#include <algorithm>
#include <string.h>
using namespace std;

int pos, n, Size; //查找位置,分区数量,最小分割大小

//分区
struct List
{
    int id;          //空闲分区编号
    int startAdress; //空闲分区首地址
    int room;        //空间
    int state;       //状态，0为空，1为未满，2为满；
} L[2000];

//作业
struct Task
{
    int id;          //作业编号
    int room;        //作业空间
    int startAdress; //作业起始地址
} T[2000];

bool cmp(List a, List b)
{
    return a.room < b.room;
}

//输出分区
void print()
{
    int i;
    printf("|---------------------------------------------------------------|\n");
    printf("|         分区号     分区始址     分区大小     分区状态         |\n");
    printf("|---------------------------------------------------------------|\n");
    for (i = 1; i <= n; i++)
    {
        printf("|         %3d         %3d          %3d          %3d             |\n",
               L[i].id, L[i].startAdress, L[i].room, L[i].state);
        printf("|---------------------------------------------------------------|\n");
    }
}

//回收内存
void recycle()
{
    printf("请输入要释放占用空间任务的序号：\n");
    int l;              //要回收的任务编号
    int f1 = 0, f2 = 0; //f1判断是否上邻接空闲区，f2判断是否下邻接空闲区
    int p1, p2;         //p1保存上邻接的分区序号，p2保存下邻接的分区序号
    cin >> l;           //输入序号
    for (int i = 1; i <= n; i++)
    {
        //第i块分区空闲区下端，上邻接空闲区
        //起始地址与空闲区下端邻接
        if (T[l].startAdress == L[i].startAdress + L[i].room)
        {
            f1 = 1;
            p1 = i;
        }
        //第i块分区空闲区上端，下邻接空闲区
        //末尾地址与空闲区上端邻接
        if (T[l].startAdress + T[l].room == L[i].startAdress)
        {
            f2 = 1;
            p2 = i;
        }
    }

    //情况1：上邻接空闲区
    if (f1 == 1 && f2 == 0)
    {
        L[p1].room = L[p1].room + T[l].room;
    }

    //情况2：下邻接空闲区
    else if (f1 == 0 && f2 == 1)
    {
        L[p2].room = L[p2].room + T[l].room;
        L[p2].startAdress = T[l].startAdress;
    }

    //情况3：上下都邻接空闲区，两个分区合二为一
    else if (f1 == 1 && f2 == 1)
    {
        L[p1].room = L[p1].room + T[l].room + L[p2].room;
        //其余分区编号前移
        for (int j = p1 + 1; j <= n; j++)
            L[j].id--;
        n--; //分区数-1
    }

    //情况4：上下都不邻接空闲区，一个分区分为两个分区
    else if (f1 == 0 && f2 == 0)
    {
        int temp;
        //找到排在它后面的第一个分区
        for (int j = 1; j <= n; j++)
        {
            if (L[j].startAdress > T[l].startAdress + T[l].room) //实际上大于T[l].startAdress就可以
            {
                temp = j;
                break;
            }
        }
        //后面的分区编号后移
        for (int j = temp; j <= n; j++)
            L[j].id++;
        n++; //分区数+1
        L[temp].id = temp;
        L[temp].room = T[l].room;
        L[temp].startAdress = T[l].startAdress;
        L[temp].state = 0;
    }
    cout << "内存回收完毕！" << endl;
}

//循环首次适应算法
//从当前位置不断扫描
void NF()
{
    cout << "选择采用'循环首次适应算法'进行内存分配\n"
         << endl;
    int tmp;
    pos = 1; //开始从第一个分区查找
    while (1)
    {
        cout << "      *******************************************" << endl;
        cout << "      1: 分配内存             2: 回收内存        " << endl;
        cout << endl;
        cout << "      3: 查看空闲分区表       0: 退出       " << endl;
        cout << "      *******************************************" << endl;
        cout << "请输入您的操作 ：";
        cin >> tmp;
        int k = 0;

        //分配内存
        if (tmp == 1)
        {
            k++;
            printf("请输入第%d个作业占用空间大小：\n", k);
            cin >> T[k].room; //作业空间
            T[k].id = k;
            int num = 0;
            for (int i = pos;; i++)
            {
                num++;
                if (num > n)
                {
                    printf("作业请求内存空间过大，空闲分区表不能满足要求，内存分配失败!\n");
                    break;
                }

                //模拟循环列表
                if (i > n)
                {
                    i = 1;
                    continue;
                }

                //第i个分区容得下该作业，且有剩余空间，则放入
                if ((L[i].state == 0 || L[i].state == 1) && L[i].room >= T[i].room)
                {
                    //第一种情况：剩余空间大于最小分割大小
                    if (L[i].room - T[k].room > Size)
                    {
                        L[i].startAdress = L[i].startAdress + T[k].room;
                        L[i].room = L[i].room - T[k].room;
                        L[i].state = 1;
                        T[k].startAdress = L[i].startAdress - T[k].room;
                        printf("内存分配成功！\n作业申请空间为%d\n起始地址为%d\n", T[k].room, T[k].startAdress);
                        break;
                    }
                    //第二种情况：剩余空间小于最小分割大小
                    else
                    {
                        L[i].startAdress = L[i].startAdress + Size;
                        L[i].room = L[i].room - Size;
                        L[i].state = 2;
                        T[k].startAdress = L[i].startAdress - Size;
                        printf("内存分配成功！\n作业申请空间为%d\n起始地址为%d\n", L[i].room, T[k].startAdress);
                        break;
                    }
                }
                //分区正好能放下该作业
                else if (L[i].state = 0 && L[i].room - T[k].room == Size)
                {
                    L[i].state = 2;
                    T[k].startAdress = L[i].startAdress;
                    printf("内存分配成功！\n作业申请空间为%d\n起始地址为%d\n", T[k].room, T[k].startAdress);
                    break;
                }
            }
        }

        //回收内存
        else if (tmp == 2)
        {
            recycle();
        }

        //查看内存
        else if (tmp == 3)
            print();

        //退出
        else if (tmp == 0)
            return;
        else
        {
            printf("输入有误，请重新输入！\n");
            continue;
        }
    }
}

//最佳适应算法
//空闲区按从小到大递增顺序
void BF()
{
    cout << "选择采用'最佳适应算法'进行内存分配\n"
         << endl;
    sort(L + 1, L + n + 1, cmp);
    int tmp;
    while (1)
    {
        cout << "      *******************************************" << endl;
        cout << "      1: 分配内存             2: 回收内存        " << endl;
        cout << endl;
        cout << "      3: 查看空闲分区表       0: 退出       " << endl;
        cout << "      *******************************************" << endl;
        cout << "请输入您的操作 ：";
        cin >> tmp;
        int k = 0; //作业序号
        if (tmp == 1)
        {
            k++;
            printf("请输入第%d个作业占用空间大小：\n", k);
            cin >> T[k].room;
            T[k].id = k;
            int i;
            for (i = 1; i <= n; i++)
            {
                //模拟循环列表
                if (i > n)
                {
                    i = 1;
                    continue;
                }

                //第i个分区容得下该作业，且有剩余空间，则放入
                if ((L[i].state == 0 || L[i].state == 1) && L[i].room >= T[i].room)
                {
                    //第一种情况：剩余空间大于最小分割大小
                    if (L[i].room - T[k].room > Size)
                    {
                        L[i].startAdress = L[i].startAdress + T[k].room;
                        L[i].room = L[i].room - T[k].room;
                        L[i].state = 1;
                        T[k].startAdress = L[i].startAdress - T[k].room;
                        printf("内存分配成功！\n作业申请空间为%d\n起始地址为%d\n", T[k].room, T[k].startAdress);
                        break;
                    }
                    //第二种情况：剩余空间小于最小分割大小
                    else
                    {
                        L[i].startAdress = L[i].startAdress + Size;
                        L[i].room = L[i].room - Size;
                        L[i].state = 2;
                        T[k].startAdress = L[i].startAdress - Size;
                        printf("内存分配成功！\n作业申请空间为%d\n起始地址为%d\n", L[i].room, T[k].startAdress);
                        break;
                    }
                }
                //分区正好能放下该作业
                else if (L[i].state = 0 && L[i].room - T[k].room == Size)
                {
                    L[i].state = 2;
                    T[k].startAdress = L[i].startAdress;
                    printf("内存分配成功！\n作业申请空间为%d\n起始地址为%d\n", T[k].room, T[k].startAdress);
                    break;
                }
            }
            if (i > n)
            {
                printf("作业请求内存空间过大，空闲分区表不能满足要求，内存分配失败!\n");
                break;
            }
        }

        //回收内存
        else if (tmp == 2)
        {
            recycle();
            sort(L + 1, L + n + 1, cmp); //排序
        }

        //查看内存
        else if (tmp == 3)
            print();

        //退出
        else if (tmp == 0)
            return;
        else
        {
            printf("输入有误，请重新输入！\n");
            continue;
        }
    }
}

int main()
{
loop1:
    pos = 1;
    printf("请输入空闲分区表分区数量：\n");
    cin >> n;
    printf("请输入每个空闲分区的分区大小，分区始址\n");
    for (int i = 1; i <= n; i++)
    {
        printf("请输入第%d个分区的信息：\n", i);
        cin >> L[i].room >> L[i].startAdress;
        L[i].id = i;
        L[i].state = 0;
    }
    printf("输入完毕，当前空闲分区表状态为：\n");
    print();
    printf("请输入不再切割的剩余空间的大小：\n");
    cin >> Size;
loop2:
    printf("选择内存分配的算法：1.循环首次适应算法  2.最佳适应算法  3.重新编辑空闲分区表  4.退出 \n");
    int tmp;
    cin >> tmp;
    if (tmp == 1)
        NF();
    else if (tmp == 2)
        BF();
    else if (tmp == 3)
    {
        goto loop1;
    }
    else if (tmp == 4)
        return 0;
    else
    {
        printf("输入有误，请重新输入!\n");
        goto loop2;
    }
}