/*
��������:
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

int n;        //ҳ�����úŸ���
int m;        //�������Ŀ
int page[N];  //ҳ��
int block[N]; //����飬�ڴ�

//������δʹ���㷨
void lru()
{
    //��ʼ��
    int page_lack = 0;
    memset(block, -1, sizeof(block));

    //ѭ��
    for (int i = 1; i <= n; ++i)
    {
        printf("��ǰ����ʵ�ҳ��Ϊ%d\n", page[i]);
        int j;
        int max_dist = 0, p;

        for (j = 1; j <= m; ++j)
        {
            //ҳ�����ڴ���,�ŵ���һ�����������
            if (block[j] == page[i])
            {
                printf("%d�����ڴ��У���������һ��\n", page[i]);
                int tmp = block[j];
                for (int tp = j; tp >= 2; --tp)
                    block[tp] = block[tp - 1];
                block[1] = tmp;
                break;
            }
            //�����ڴ棬�����һ������������
            else if (block[j] == -1)
            {
                for (int tp = j; tp >= 2; --tp)
                    block[tp] = block[tp - 1];
                block[1] = page[i];
                printf(" %d�����ڴ棬����\n", page[i]);
                page_lack++;
                break;
            }
        }

        //ҳ�治���ڴ���-ҳ���滻���������ƣ������һ��
        if (j > m)
        {
            printf("%d�����ڴ棬���룬ҳ��%d���滻\n", page[i], block[m]);
            for (int tp = m; tp >= 2; --tp)
                block[tp] = block[tp - 1];
            block[1] = page[i];
            page_lack++;
        }

        //����ڴ���ҳ��������
        for (int k = 1; k <= m; ++k)
            cout << block[k] << "\t";
        cout << endl
             << endl;
    }

    //���ȱҳ����
    cout << endl
         << "ȱҳ������" << page_lack << endl;
}

//�Ƚ��ȳ�ҳ���û��㷨
void fifo()
{
    //��ʼ��
    int page_lack = 0;
    memset(block, -1, sizeof(block));

    //ѭ��
    for (int i = 1; i <= n; ++i)
    {
        printf("��ǰ����ʵ�ҳ��Ϊ%d\n", page[i]);
        int j;
        int max_dist = 0, p;

        for (j = 1; j <= m; ++j)
        {
            //ҳ�����ڴ���
            if (block[j] == page[i])
            {
                printf("%d�����ڴ��У�����\n", page[i]);
                break;
            }
            //�����ڴ棬�����һ������������
            else if (block[j] == -1)
            {
                for (int tp = j; tp >= 2; --tp)
                    block[tp] = block[tp - 1];
                block[1] = page[i];
                printf("%d�����ڴ棬����\n",  page[i]);
                page_lack++;
                break;
            }
        }

        //ҳ�治���ڴ���-ҳ���滻���������ƣ������һ��
        if (j > m)
        {
            printf("%d�����ڴ棬���룬ҳ��%d���滻\n", page[i], block[m]);
            for (int tp = m; tp >= 2; --tp)
                block[tp] = block[tp - 1];
            block[1] = page[i];
            page_lack++;
        }

        //����ڴ���ҳ��������
        for (int k = 1; k <= m; ++k)
            cout << block[k] << "\t";
        cout << endl
             << endl;
    }

    //���ȱҳ����
    cout << endl
         << "ȱҳ������" << page_lack << endl;
}

bool changed[N]; //�޸�λ
bool visited[N]; //����λ

//�ж�ҳ���Ƿ��Ѿ����޸�
bool change()
{
    if (rand() % 2)
    {
        printf("��ҳ�汻�޸�!\n");
        return true;
    }
    else
        return false;
}

//���ҳ���Ƿ����ڴ��в��ѷ���λ��1���޸�λ���������1��0
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
        //1�ࣺ�����̭ҳ
        if (visited[j] == 0 && changed[j] == 0)
            return j;
    }
    for (j = 1; j <= m; j++)
    {
        //2��
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
        printf("��ǰ����ʵ�ҳ��Ϊ%d\n", page[i]);
        if (inblock(i)) ///ҳ���Ѵ������ڴ���
        {
            printf("%d�����ڴ��У�����\n",page[i]);
        }

        //ҳ��δ�������ڴ��в����ڴ�����
        else if (block[m] != -1)
        {
            j = Search();
            block[j] = page[i];
            visited[j] = 1;
            page_lack++;
        }

        //�ڴ�δ��������ҳ��δ�������ڴ���
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

    //���ȱҳ����
    cout << endl
         << "ȱҳ������" << page_lack << endl;
}

int main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; ++i)
    {
        cin >> page[i];
    }

    cout << "----------------------------------------------------------------" << endl;
    cout << "LRU�㷨:\n";
    lru();
    cout << "----------------------------------------------------------------" << endl;
    cout << "FIFO�㷨:\n";
    fifo();
    cout << "----------------------------------------------------------------" << endl;
    cout << "�Ľ���CLOCK�㷨:\n";
    improved_Clock();
    cout << "----------------------------------------------------------------" << endl;
    return 0;
}