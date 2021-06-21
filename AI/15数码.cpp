#include <iostream>
#include <stack>
#include <vector>
#include <algorithm>
#include <time.h>
#include <math.h>
#define ROW 4
#define COL 4
using namespace std;

//操作集F 这里就是四个方向
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
    //d和p都是用来计算状态评价值f的

public:
    int direction = 0; // 记录方向
    int s[ROW][COL];
    State *father = NULL; // 记录父节点

    State(){};

    // 初始化
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

    // 判断是否到目标状态
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

    // 计算深度
    void setD(int t[ROW][COL])
    {
        d += 1;
        setP(t);
    }

    // 计算最短距离之和
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
        //上一步不是向下移
        if (direction != S)
        {
            int temp;
            direction = N; //这步是向上移
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
        //上一步不是向上移
        if (direction != N)
        {
            int temp;
            direction = S; //这步是向下移
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
        //上一步不是向右移
        if (direction != E)
        {
            int temp;
            direction = W; //这步是向左移
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
        //上一步不是向左移
        if (direction != W)
        {
            int temp;
            direction = E; //这步是向右移
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
        // cout << "D值为：" << d << "    ";
        // cout << "P值为：" << p << "    ";
        // cout << "状态评价值f为：" << f << endl;
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
        this->start.father = NULL; // 设置初始节点
        this->start.setS0(-1, 0);
        this->start.setD(end.s);
        open.push_back(this->start);
    }

    // 打印open表
    void printOpen()
    {
        for (vector<State>::iterator it = open.begin(); it != open.end(); it++)
            it->show();
    }

    // 打印close表
    void printClose()
    {
        for (vector<State>::iterator it = close.begin(); it != close.end(); it++)
            it->show();
    }

    // 判断是否在open表
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

    // 判断是否在close表
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
            if (open.empty()) // open表为空查询失败
                return false;
            State p = open.front();
            close.push_back(p); // 将估值最小的元素加入close表
            // 判断是否为目标状态
            if (p.compare(t))
            {
                printf("初始状态到达目标状态总循环次数：%d\n", count);
                return true;
            }
            open.erase(open.begin()); // 从open表弹出估值最小的元素
            State temp = p;
            // 上移
            if (temp.up(t))
            {
                temp.father = &close.back();
                if (ifInOpen(temp) == 0 && ifInClose(temp) == 0)
                    open.push_back(temp);
            }
            temp = p;
            // 下移
            if (temp.down(t))
            {
                temp.father = &close.back();
                if (ifInOpen(temp) == 0 && ifInClose(temp) == 0)
                    open.push_back(temp);
            }
            temp = p;
            // 左移
            if (temp.left(t))
            {
                temp.father = &close.back();
                if (ifInOpen(temp) == 0 && ifInClose(temp) == 0)
                    open.push_back(temp);
            }
            temp = p;
            // 右移
            if (temp.right(t))
            {
                temp.father = &close.back();
                if (ifInOpen(temp) == 0 && ifInClose(temp) == 0)
                    open.push_back(temp);
            }
            reverse(open.begin(), open.end()); // 对open表进行排序
            sort(open.begin(), open.end());
        }
    }

    // 输出结果
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
    int start[ROW][COL] = {{5, 1, 2, 4}, {9, 6, 3, 8}, {13, 10, 7, 11}, {0, 14, 15, 12}}; //初始状态集S
    int end[ROW][COL] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 0}}; //目标状态集G

    State s(start, end);
    State g(end, end);
    AStar a(s, g);
    vector<State> res;
    clock_t st,et;
    st = clock();
    a.fun(end);
    et = clock();
    printf("耗时：%fms\n变化过程：\n",(double)et-(double)st);
    // s.show();
    a.output();
    return 0;
}