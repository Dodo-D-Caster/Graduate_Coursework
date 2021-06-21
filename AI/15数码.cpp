#include <iostream>
#include <stack>
#include <vector>
#include <algorithm>
#include <time.h>
#include <math.h>
#define ROW 4
#define COL 4
using namespace std;

//������F ��������ĸ�����
enum direction
{
    N = 0,
    S = 1,
    W = 2,
    E = 3
};

class State
{
private:
    int state = 0;
    int d = 0;
    int p = 0;
    int f = 0;
    //d��p������������״̬����ֵf��

public:
    int direction = 0; // ��¼����
    int s[ROW][COL];
    State *father = NULL; // ��¼���ڵ�

    State(){};

    // ��ʼ��
    State(int s[ROW][COL], int t[ROW][COL], int state = 0)
    {
        memcpy(this->s, s, sizeof(int) * ROW * COL);
        this->state = state;
        father = NULL;
    };

    void setS0(int d, int f)
    {
        this->d = d;
        this->f = f;
    }

    // �ж��Ƿ�Ŀ��״̬
    bool compare(int t[ROW][COL])
    {
        int sum = 0;
        for (int i = 0; i < ROW; i++)
            for (int j = 0; j < COL; j++)
            {
                if (s[i][j] == t[i][j])
                    sum++;
            }
        if (sum == 16)
            return true;
        else
            return false;
    }

    void setS(int s[ROW][COL])
    {
        memcpy(this->s, s, sizeof(int) * ROW * COL);
    }

    // �������
    void setD(int t[ROW][COL])
    {
        d += 1;
        setP(t);
    }

    // ������̾���֮��
    void setP(int t[ROW][COL])
    {
        int count = 0;
        for (int i = 0; i < ROW; i++)
            for (int j = 0; j < COL; j++)
            {
                for (int m = 0; m < ROW; m++)
                    for (int k = 0; k < COL; k++)
                    {
                        if (s[i][j] == t[m][k] && s[i][j] != 0)
                        {
                            count += abs(i - m) + abs(j - k);
                        }
                    }
            }
        p = count;
        setF();
    }

    void setF()
    {
        f = getP() + getD();
    }

    int getF()
    {
        return f;
    }

    int getD()
    {
        return d;
    }

    int getP()
    {
        return p;
    }

    bool up(int t[ROW][COL])
    {
        //��һ������������
        if (direction != S)
        {
            int temp;
            direction = N; //�ⲽ��������
            for (int i = 0; i < ROW; i++)
            {
                for (int j = 0; j < COL; j++)
                {
                    if (s[i][j] == 0 && i - 1 >= 0)
                    {
                        temp = s[i][j];
                        s[i][j] = s[i - 1][j];
                        s[i - 1][j] = temp;
                        setD(t);
                        return true;
                        break;
                    }
                }
            }
        }
        setD(t);
        return false;
    }

    bool down(int t[ROW][COL])
    {
        //��һ������������
        if (direction != N)
        {
            int temp;
            direction = S; //�ⲽ��������
            for (int i = 0; i < ROW; i++)
            {
                for (int j = 0; j < COL; j++)
                {
                    if (s[i][j] == 0 && i + 1 < ROW)
                    {
                        temp = s[i][j];
                        s[i][j] = s[i + 1][j];
                        s[i + 1][j] = temp;
                        setD(t);
                        return true;
                        break;
                    }
                }
            }
        }
        setD(t);
        return false;
    }

    bool left(int t[ROW][COL])
    {
        //��һ������������
        if (direction != E)
        {
            int temp;
            direction = W; //�ⲽ��������
            for (int i = 0; i < ROW; i++)
            {
                for (int j = 0; j < COL; j++)
                {
                    if (s[i][j] == 0 && j - 1 >= 0)
                    {
                        temp = s[i][j];
                        s[i][j] = s[i][j - 1];
                        s[i][j - 1] = temp;
                        setD(t);
                        return true;
                        break;
                    }
                }
            }
        }
        setD(t);
        return false;
    }

    bool right(int t[ROW][COL])
    {
        //��һ������������
        if (direction != W)
        {
            int temp;
            direction = E; //�ⲽ��������
            for (int i = 0; i < ROW; i++)
            {
                for (int j = 0; j < COL; j++)
                {
                    if (s[i][j] == 0 && j + 1 < COL)
                    {
                        temp = s[i][j];
                        s[i][j] = s[i][j + 1];
                        s[i][j + 1] = temp;
                        setD(t);
                        return true;
                        break;
                    }
                }
            }
        }
        setD(t);
        return false;
    }

    bool operator<(const State &temp) const
    {
        return f < temp.f;
    }

    void show()
    {
        for (int i = 0; i < ROW; i++)
        {
            for (int j = 0; j < COL; j++)
            {
                cout << s[i][j] << '\t';
                if (j == COL - 1)
                    cout << endl;
            }
        }
        // cout << "DֵΪ��" << d << "    ";
        // cout << "PֵΪ��" << p << "    ";
        // cout << "״̬����ֵfΪ��" << f << endl;
        cout << endl;
    }
};

class AStar
{
private:
    vector<State> open;
    vector<State> close;
    State start;
    State end;
    int count = 0;

public:
    AStar(State start, State end)
    {
        this->start = start;
        this->end = end;
        open.reserve(1000);
        close.reserve(1000);
        this->start.father = NULL; // ���ó�ʼ�ڵ�
        this->start.setS0(-1, 0);
        this->start.setD(end.s);
        open.push_back(this->start);
    }

    // ��ӡopen��
    void printOpen()
    {
        for (vector<State>::iterator it = open.begin(); it != open.end(); it++)
            it->show();
    }

    // ��ӡclose��
    void printClose()
    {
        for (vector<State>::iterator it = close.begin(); it != close.end(); it++)
            it->show();
    }

    // �ж��Ƿ���open��
    bool ifInOpen(State temp)
    {
        int i = 0;
        vector<State>::iterator it;
        for (it = open.begin(); it != open.end(); it++)
        {
            if (temp.compare(it[0].s) && temp.getF() < it[0].getF())
            {
                open.erase(open.begin() + i);
                open.push_back(temp);
                return true;
            }
            i++;
        }
        return false;
    }

    // �ж��Ƿ���close��
    bool ifInClose(State temp)
    {
        int i = 0;
        vector<State>::iterator it;
        for (it = close.begin(); it != close.end(); it++)
        {
            if (temp.compare(it[0].s) && temp.getF() < it[0].getF())
            {
                close.erase(close.begin() + i);
                open.push_back(temp);
                return true;
            }
            i++;
        }
        return false;
    }

    bool fun(int t[ROW][COL])
    {
        while (true)
        {
            ++count;
            if (open.empty()) // open��Ϊ�ղ�ѯʧ��
                return false;
            State p = open.front();
            close.push_back(p); // ����ֵ��С��Ԫ�ؼ���close��
            // �ж��Ƿ�ΪĿ��״̬
            if (p.compare(t))
            {
                printf("��ʼ״̬����Ŀ��״̬��ѭ��������%d\n", count);
                return true;
            }
            open.erase(open.begin()); // ��open������ֵ��С��Ԫ��
            State temp = p;
            // ����
            if (temp.up(t))
            {
                temp.father = &close.back();
                if (ifInOpen(temp) == 0 && ifInClose(temp) == 0)
                    open.push_back(temp);
            }
            temp = p;
            // ����
            if (temp.down(t))
            {
                temp.father = &close.back();
                if (ifInOpen(temp) == 0 && ifInClose(temp) == 0)
                    open.push_back(temp);
            }
            temp = p;
            // ����
            if (temp.left(t))
            {
                temp.father = &close.back();
                if (ifInOpen(temp) == 0 && ifInClose(temp) == 0)
                    open.push_back(temp);
            }
            temp = p;
            // ����
            if (temp.right(t))
            {
                temp.father = &close.back();
                if (ifInOpen(temp) == 0 && ifInClose(temp) == 0)
                    open.push_back(temp);
            }
            reverse(open.begin(), open.end()); // ��open���������
            sort(open.begin(), open.end());
        }
    }

    // ������
    void output()
    {
        State *p = new State;
        stack<State> s;
        *p = close.back();
        for (; p != NULL; p = p->father)
        {
            s.push(*p);
        }
        while (!s.empty())
        {
            State k = s.top();
            k.show();
            s.pop();
        }
    }
};

int main()
{
    int start[ROW][COL] = {{5, 1, 2, 4}, {9, 6, 3, 8}, {13, 10, 7, 11}, {0, 14, 15, 12}}; //��ʼ״̬��S
    int end[ROW][COL] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 0}}; //Ŀ��״̬��G

    State s(start, end);
    State g(end, end);
    AStar a(s, g);
    vector<State> res;
    clock_t st,et;
    st = clock();
    a.fun(end);
    et = clock();
    printf("��ʱ��%fms\n�仯���̣�\n",(double)et-(double)st);
    // s.show();
    a.output();
    return 0;
}