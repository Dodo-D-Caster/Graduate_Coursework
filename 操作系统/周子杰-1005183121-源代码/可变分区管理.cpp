/*
�������ݣ�
ѭ���״���Ӧ�㷨��
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

�����Ӧ�㷨��
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

int pos, n, Size; //����λ��,��������,��С�ָ��С

//����
struct List
{
    int id;          //���з������
    int startAdress; //���з����׵�ַ
    int room;        //�ռ�
    int state;       //״̬��0Ϊ�գ�1Ϊδ����2Ϊ����
} L[2000];

//��ҵ
struct Task
{
    int id;          //��ҵ���
    int room;        //��ҵ�ռ�
    int startAdress; //��ҵ��ʼ��ַ
} T[2000];

bool cmp(List a, List b)
{
    return a.room < b.room;
}

//�������
void print()
{
    int i;
    printf("|---------------------------------------------------------------|\n");
    printf("|         ������     ����ʼַ     ������С     ����״̬         |\n");
    printf("|---------------------------------------------------------------|\n");
    for (i = 1; i <= n; i++)
    {
        printf("|         %3d         %3d          %3d          %3d             |\n",
               L[i].id, L[i].startAdress, L[i].room, L[i].state);
        printf("|---------------------------------------------------------------|\n");
    }
}

//�����ڴ�
void recycle()
{
    printf("������Ҫ�ͷ�ռ�ÿռ��������ţ�\n");
    int l;              //Ҫ���յ�������
    int f1 = 0, f2 = 0; //f1�ж��Ƿ����ڽӿ�������f2�ж��Ƿ����ڽӿ�����
    int p1, p2;         //p1�������ڽӵķ�����ţ�p2�������ڽӵķ������
    cin >> l;           //�������
    for (int i = 1; i <= n; i++)
    {
        //��i������������¶ˣ����ڽӿ�����
        //��ʼ��ַ��������¶��ڽ�
        if (T[l].startAdress == L[i].startAdress + L[i].room)
        {
            f1 = 1;
            p1 = i;
        }
        //��i������������϶ˣ����ڽӿ�����
        //ĩβ��ַ��������϶��ڽ�
        if (T[l].startAdress + T[l].room == L[i].startAdress)
        {
            f2 = 1;
            p2 = i;
        }
    }

    //���1�����ڽӿ�����
    if (f1 == 1 && f2 == 0)
    {
        L[p1].room = L[p1].room + T[l].room;
    }

    //���2�����ڽӿ�����
    else if (f1 == 0 && f2 == 1)
    {
        L[p2].room = L[p2].room + T[l].room;
        L[p2].startAdress = T[l].startAdress;
    }

    //���3�����¶��ڽӿ����������������϶�Ϊһ
    else if (f1 == 1 && f2 == 1)
    {
        L[p1].room = L[p1].room + T[l].room + L[p2].room;
        //����������ǰ��
        for (int j = p1 + 1; j <= n; j++)
            L[j].id--;
        n--; //������-1
    }

    //���4�����¶����ڽӿ�������һ��������Ϊ��������
    else if (f1 == 0 && f2 == 0)
    {
        int temp;
        //�ҵ�����������ĵ�һ������
        for (int j = 1; j <= n; j++)
        {
            if (L[j].startAdress > T[l].startAdress + T[l].room) //ʵ���ϴ���T[l].startAdress�Ϳ���
            {
                temp = j;
                break;
            }
        }
        //����ķ�����ź���
        for (int j = temp; j <= n; j++)
            L[j].id++;
        n++; //������+1
        L[temp].id = temp;
        L[temp].room = T[l].room;
        L[temp].startAdress = T[l].startAdress;
        L[temp].state = 0;
    }
    cout << "�ڴ������ϣ�" << endl;
}

//ѭ���״���Ӧ�㷨
//�ӵ�ǰλ�ò���ɨ��
void NF()
{
    cout << "ѡ�����'ѭ���״���Ӧ�㷨'�����ڴ����\n"
         << endl;
    int tmp;
    pos = 1; //��ʼ�ӵ�һ����������
    while (1)
    {
        cout << "      *******************************************" << endl;
        cout << "      1: �����ڴ�             2: �����ڴ�        " << endl;
        cout << endl;
        cout << "      3: �鿴���з�����       0: �˳�       " << endl;
        cout << "      *******************************************" << endl;
        cout << "���������Ĳ��� ��";
        cin >> tmp;
        int k = 0;

        //�����ڴ�
        if (tmp == 1)
        {
            k++;
            printf("�������%d����ҵռ�ÿռ��С��\n", k);
            cin >> T[k].room; //��ҵ�ռ�
            T[k].id = k;
            int num = 0;
            for (int i = pos;; i++)
            {
                num++;
                if (num > n)
                {
                    printf("��ҵ�����ڴ�ռ���󣬿��з�����������Ҫ���ڴ����ʧ��!\n");
                    break;
                }

                //ģ��ѭ���б�
                if (i > n)
                {
                    i = 1;
                    continue;
                }

                //��i�������ݵ��¸���ҵ������ʣ��ռ䣬�����
                if ((L[i].state == 0 || L[i].state == 1) && L[i].room >= T[i].room)
                {
                    //��һ�������ʣ��ռ������С�ָ��С
                    if (L[i].room - T[k].room > Size)
                    {
                        L[i].startAdress = L[i].startAdress + T[k].room;
                        L[i].room = L[i].room - T[k].room;
                        L[i].state = 1;
                        T[k].startAdress = L[i].startAdress - T[k].room;
                        printf("�ڴ����ɹ���\n��ҵ����ռ�Ϊ%d\n��ʼ��ַΪ%d\n", T[k].room, T[k].startAdress);
                        break;
                    }
                    //�ڶ��������ʣ��ռ�С����С�ָ��С
                    else
                    {
                        L[i].startAdress = L[i].startAdress + Size;
                        L[i].room = L[i].room - Size;
                        L[i].state = 2;
                        T[k].startAdress = L[i].startAdress - Size;
                        printf("�ڴ����ɹ���\n��ҵ����ռ�Ϊ%d\n��ʼ��ַΪ%d\n", L[i].room, T[k].startAdress);
                        break;
                    }
                }
                //���������ܷ��¸���ҵ
                else if (L[i].state = 0 && L[i].room - T[k].room == Size)
                {
                    L[i].state = 2;
                    T[k].startAdress = L[i].startAdress;
                    printf("�ڴ����ɹ���\n��ҵ����ռ�Ϊ%d\n��ʼ��ַΪ%d\n", T[k].room, T[k].startAdress);
                    break;
                }
            }
        }

        //�����ڴ�
        else if (tmp == 2)
        {
            recycle();
        }

        //�鿴�ڴ�
        else if (tmp == 3)
            print();

        //�˳�
        else if (tmp == 0)
            return;
        else
        {
            printf("�����������������룡\n");
            continue;
        }
    }
}

//�����Ӧ�㷨
//����������С�������˳��
void BF()
{
    cout << "ѡ�����'�����Ӧ�㷨'�����ڴ����\n"
         << endl;
    sort(L + 1, L + n + 1, cmp);
    int tmp;
    while (1)
    {
        cout << "      *******************************************" << endl;
        cout << "      1: �����ڴ�             2: �����ڴ�        " << endl;
        cout << endl;
        cout << "      3: �鿴���з�����       0: �˳�       " << endl;
        cout << "      *******************************************" << endl;
        cout << "���������Ĳ��� ��";
        cin >> tmp;
        int k = 0; //��ҵ���
        if (tmp == 1)
        {
            k++;
            printf("�������%d����ҵռ�ÿռ��С��\n", k);
            cin >> T[k].room;
            T[k].id = k;
            int i;
            for (i = 1; i <= n; i++)
            {
                //ģ��ѭ���б�
                if (i > n)
                {
                    i = 1;
                    continue;
                }

                //��i�������ݵ��¸���ҵ������ʣ��ռ䣬�����
                if ((L[i].state == 0 || L[i].state == 1) && L[i].room >= T[i].room)
                {
                    //��һ�������ʣ��ռ������С�ָ��С
                    if (L[i].room - T[k].room > Size)
                    {
                        L[i].startAdress = L[i].startAdress + T[k].room;
                        L[i].room = L[i].room - T[k].room;
                        L[i].state = 1;
                        T[k].startAdress = L[i].startAdress - T[k].room;
                        printf("�ڴ����ɹ���\n��ҵ����ռ�Ϊ%d\n��ʼ��ַΪ%d\n", T[k].room, T[k].startAdress);
                        break;
                    }
                    //�ڶ��������ʣ��ռ�С����С�ָ��С
                    else
                    {
                        L[i].startAdress = L[i].startAdress + Size;
                        L[i].room = L[i].room - Size;
                        L[i].state = 2;
                        T[k].startAdress = L[i].startAdress - Size;
                        printf("�ڴ����ɹ���\n��ҵ����ռ�Ϊ%d\n��ʼ��ַΪ%d\n", L[i].room, T[k].startAdress);
                        break;
                    }
                }
                //���������ܷ��¸���ҵ
                else if (L[i].state = 0 && L[i].room - T[k].room == Size)
                {
                    L[i].state = 2;
                    T[k].startAdress = L[i].startAdress;
                    printf("�ڴ����ɹ���\n��ҵ����ռ�Ϊ%d\n��ʼ��ַΪ%d\n", T[k].room, T[k].startAdress);
                    break;
                }
            }
            if (i > n)
            {
                printf("��ҵ�����ڴ�ռ���󣬿��з�����������Ҫ���ڴ����ʧ��!\n");
                break;
            }
        }

        //�����ڴ�
        else if (tmp == 2)
        {
            recycle();
            sort(L + 1, L + n + 1, cmp); //����
        }

        //�鿴�ڴ�
        else if (tmp == 3)
            print();

        //�˳�
        else if (tmp == 0)
            return;
        else
        {
            printf("�����������������룡\n");
            continue;
        }
    }
}

int main()
{
loop1:
    pos = 1;
    printf("��������з��������������\n");
    cin >> n;
    printf("������ÿ�����з����ķ�����С������ʼַ\n");
    for (int i = 1; i <= n; i++)
    {
        printf("�������%d����������Ϣ��\n", i);
        cin >> L[i].room >> L[i].startAdress;
        L[i].id = i;
        L[i].state = 0;
    }
    printf("������ϣ���ǰ���з�����״̬Ϊ��\n");
    print();
    printf("�����벻���и��ʣ��ռ�Ĵ�С��\n");
    cin >> Size;
loop2:
    printf("ѡ���ڴ������㷨��1.ѭ���״���Ӧ�㷨  2.�����Ӧ�㷨  3.���±༭���з�����  4.�˳� \n");
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
        printf("������������������!\n");
        goto loop2;
    }
}