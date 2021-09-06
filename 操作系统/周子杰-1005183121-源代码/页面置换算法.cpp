/*
测试数据:
20 3
7 0 1 2 0 3 0 4 2 3 0 3 2 1 2 0 1 7 0 1

12 3
2 3 2 1 5 2 4 5 3 2 5 2
*/
#include <iostream>
#include <set>
#include <algorithm>
#include <cstring>
#include <cmath>
#define N 200
using namespace std;

int n;        //页面引用号个数
int m;        //物理块数目
int page[N];  //页号
int block[N]; //物理块，内存

//最近最久未使用算法
void lru()
{
    //初始化
    int page_lack = 0;
    memset(block, -1, sizeof(block));

    //循环
    for (int i = 1; i <= n; ++i)
    {
        printf("当前需访问的页面为%d\n", page[i]);
        int j;
        int max_dist = 0, p;

        for (j = 1; j <= m; ++j)
        {
            //页面在内存中,放到第一个，其余后移
            if (block[j] == page[i])
            {
                printf("%d已在内存中，提升到第一个\n", page[i]);
                int tmp = block[j];
                for (int tp = j; tp >= 2; --tp)
                    block[tp] = block[tp - 1];
                block[1] = tmp;
                break;
            }
            //不在内存，插入第一个，其他后移
            else if (block[j] == -1)
            {
                for (int tp = j; tp >= 2; --tp)
                    block[tp] = block[tp - 1];
                block[1] = page[i];
                printf(" %d不在内存，放入\n", page[i]);
                page_lack++;
                break;
            }
        }

        //页面不在内存中-页面替换，其他右移，插入第一个
        if (j > m)
        {
            printf("%d不在内存，放入，页面%d被替换\n", page[i], block[m]);
            for (int tp = m; tp >= 2; --tp)
                block[tp] = block[tp - 1];
            block[1] = page[i];
            page_lack++;
        }

        //输出内存中页面加载情况
        for (int k = 1; k <= m; ++k)
            cout << block[k] << "\t";
        cout << endl
             << endl;
    }

    //输出缺页次数
    cout << endl
         << "缺页次数：" << page_lack << endl;
}

//先进先出页面置换算法
void fifo()
{
    //初始化
    int page_lack = 0;
    memset(block, -1, sizeof(block));

    //循环
    for (int i = 1; i <= n; ++i)
    {
        printf("当前需访问的页面为%d\n", page[i]);
        int j;
        int max_dist = 0, p;

        for (j = 1; j <= m; ++j)
        {
            //页面在内存中
            if (block[j] == page[i])
            {
                printf("%d已在内存中，不变\n", page[i]);
                break;
            }
            //不在内存，插入第一个，其他后移
            else if (block[j] == -1)
            {
                for (int tp = j; tp >= 2; --tp)
                    block[tp] = block[tp - 1];
                block[1] = page[i];
                printf("%d不在内存，放入\n",  page[i]);
                page_lack++;
                break;
            }
        }

        //页面不再内存中-页面替换，其他右移，插入第一个
        if (j > m)
        {
            printf("%d不在内存，放入，页面%d被替换\n", page[i], block[m]);
            for (int tp = m; tp >= 2; --tp)
                block[tp] = block[tp - 1];
            block[1] = page[i];
            page_lack++;
        }

        //输出内存中页面加载情况
        for (int k = 1; k <= m; ++k)
            cout << block[k] << "\t";
        cout << endl
             << endl;
    }

    //输出缺页次数
    cout << endl
         << "缺页次数：" << page_lack << endl;
}

bool changed[N]; //修改位
bool visited[N]; //访问位

//判断页面是否已经被修改
bool change()
{
    if (rand() % 2)
    {
        printf("该页面被修改!\n");
        return true;
    }
    else
        return false;
}

//检测页号是否在内存中并把访问位置1，修改位根据情况置1或0
bool inblock(int num)
{
    for (int i = 1; i <= m; i++)
    {
        if (page[num] == block[i])
        {
            if (change())
            {
                changed[i] = 1;
                visited[i] = 1;
            }
            else
            {
                visited[i] = 1;
                changed[i] = 0;
            }
            return true;
        }
    }
    return false;
}

int Search()
{
    int j;
    for (j = 1; j <= m; j++)
    {
        //1类：最佳淘汰页
        if (visited[j] == 0 && changed[j] == 0)
            return j;
    }
    for (j = 1; j <= m; j++)
    {
        //2类
        if (visited[j] == 0 && changed[j] == 1)
            return j;
        visited[j] == 0;
    }
    for (j = 1; j <= m; j++)
    {
        visited[j] = 0;
    }
    return Search();
}

void improved_Clock()
{
    memset(block, -1, sizeof(block));
    memset(visited, 0, sizeof(visited));
    memset(changed, 0, sizeof(changed));
    int j;
    int page_lack = 0;
    for (int i = 1; i <= n; i++)
    {
        printf("当前需访问的页面为%d\n", page[i]);
        if (inblock(i)) ///页面已存在于内存中
        {
            printf("%d已在内存中，不变\n",page[i]);
        }

        //页面未存在于内存中并且内存已满
        else if (block[m] != -1)
        {
            j = Search();
            block[j] = page[i];
            visited[j] = 1;
            page_lack++;
        }

        //内存未满，并且页面未存在于内存中
        else
        {
            for (int k = 1; k <= m; k++)
            {
                if(block[k] == -1)
                {
                    block[k] = page[i];
                    page_lack++;
                    break;
                }
            }
        }
        for (int k = 1; k <= m; ++k)
            cout << block[k] << "\t";
        cout << endl
             << endl;
    }

    //输出缺页次数
    cout << endl
         << "缺页次数：" << page_lack << endl;
}

int main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; ++i)
    {
        cin >> page[i];
    }

    cout << "----------------------------------------------------------------" << endl;
    cout << "LRU算法:\n";
    lru();
    cout << "----------------------------------------------------------------" << endl;
    cout << "FIFO算法:\n";
    fifo();
    cout << "----------------------------------------------------------------" << endl;
    cout << "改进的CLOCK算法:\n";
    improved_Clock();
    cout << "----------------------------------------------------------------" << endl;
    return 0;
}