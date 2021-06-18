#include <windows.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <list>

int menu = 0, submenu1 = 0, submenu2, submenu3, submenu4;

//窗口大小
const int windowWidge = 600, windowHeight = 600;

//设置窗口
void setNewWindow()
{
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); //设置显示模式：单缓冲，RGB模式
    glutInitWindowPosition(600, 100);            //设置窗口位置
    glutInitWindowSize(400, 300);                //设置窗口大小
}

//初始化绘制
void init()
{
    glClearColor(1.0, 1.0, 1.0, 0.0);   //清除颜色设置
    glMatrixMode(GL_PROJECTION);        //设置投影方式
    gluOrtho2D(0.0, 200.0, 0.0, 150.0); //设置画布大小
}

void setPixel(int xCoord, int yCoord)
{
    glBegin(GL_POINTS);
    glVertex2i(xCoord, yCoord);
    glEnd();
}

//---------------------------------------------------------------------------------
//DDA
inline int round(const float a)
{
    return int(a + 0.5);
}

void lineDDA(int x0, int y0, int xEnd, int yEnd)
{
    int dx = xEnd - x0;
    int dy = yEnd - y0;
    int steps, k;
    float xIncrement, yIncrement, x = x0, y = y0;

    if (fabs(dx) > fabs(dy))
        steps = fabs(dx);
    else
        steps = fabs(dy);

    xIncrement = float(dx) / float(steps);
    yIncrement = float(dy) / float(steps);

    setPixel(round(x), round(y));
    for (k = 0; k < steps; ++k)
    {
        x += xIncrement;
        y += yIncrement;
        setPixel(round(x), round(y));
    }
}

//绘制直线
void displayLineDDA()
{
    glClear(GL_COLOR_BUFFER_BIT); //清除颜色
    glColor3f(0.0, 0.4, 0.2);     //设置当前颜色为白色
    lineDDA(0, 0, 180, 180);
    glFlush(); //发送缓冲区
}
//----------------------------------------------------------------------------------

//----------------------------------------------------------------------------------
//中点画线
void lineMidp(int x0, int y0, int x1, int y1)
{
    int a, b, d1, d2, d, x, y;
    a = y0 - y1, b = x1 - x0, d = 2 * a + b;
    d1 = 2 * a, d2 = 2 * (a + b);
    x = x0, y = y0;
    setPixel(x, y);
    while (x < x1)
    {
        if (d < 0)
        {
            x++;
            y++;
            d += d2;
        }
        else
        {
            x++;
            d += d1;
        }
        setPixel(x, y);
    }
    return;
}

//绘制直线
void displayLineMidpoint()
{
    glClear(GL_COLOR_BUFFER_BIT); //清除颜色
    glColor3f(0.0, 0.4, 0.2);     //设置当前颜色为白色
    lineMidp(0, 0, 180, 180);
    glFlush(); //发送缓冲区
}
//----------------------------------------------------------------------------------

//----------------------------------------------------------------------------------
//Bresenham画线

void lineBres(int x0, int y0, int xEnd, int yEnd)
{
    int dx = fabs(xEnd - x0), dy = fabs(yEnd - y0);
    int p = 2 * dy - dx;
    int twoDy = 2 * dy, twoDyMinusDx = 2 * (dy - dx);
    int x, y;

    if (x0 > xEnd)
    {
        x = xEnd;
        y = yEnd;
        xEnd = x0;
    }
    else
    {
        x = x0;
        y = y0;
    }
    setPixel(x, y);
    while (x < xEnd)
    {
        x++;
        if (p < 0)
            p += twoDy;
        else
        {
            y++;
            p += twoDyMinusDx;
        }
        setPixel(x, y);
    }
}

//绘制直线
void displayLineBres()
{
    glClear(GL_COLOR_BUFFER_BIT); //清除颜色
    glColor3f(0.0, 0.4, 0.2);     //设置当前颜色为白色
    lineBres(0, 0, 180, 180);
    glFlush(); //发送缓冲区
}
//----------------------------------------------------------------------------------

//----------------------------------------------------------------------------------
//中点画圆
class screenPt
{
private:
    GLint x, y;

public:
    screenPt() { x = y = 0; }
    void setCoords(GLint xCoordValue, GLint yCoordValue)
    {
        x = xCoordValue;
        y = yCoordValue;
    }
    GLint getx() const { return x; }
    GLint gety() const { return y; }
    void incremetx() { x++; }
    void decrementy() { y--; }
};

void circleMidp(GLint xc, GLint yc, GLint radius)
{
    screenPt circPt;
    GLint p = 1 - radius;
    circPt.setCoords(0, radius);
    void circlePlotPoints(GLint, GLint, screenPt);
    circlePlotPoints(xc, yc, circPt);
    while (circPt.getx() < circPt.gety())
    {
        circPt.incremetx();
        if (p < 0)
            p += 2 * circPt.getx() + 1;
        else
        {
            circPt.decrementy();
            p += 2 * (circPt.getx() - circPt.gety()) + 1;
        }
        circlePlotPoints(xc, yc, circPt);
    }
}

void circlePlotPoints(GLint xc, GLint yc, screenPt circPt)
{
    setPixel(xc + circPt.getx(), yc + circPt.gety());
    setPixel(xc - circPt.getx(), yc + circPt.gety());
    setPixel(xc + circPt.getx(), yc - circPt.gety());
    setPixel(xc - circPt.getx(), yc - circPt.gety());
    setPixel(xc + circPt.gety(), yc + circPt.getx());
    setPixel(xc - circPt.gety(), yc + circPt.getx());
    setPixel(xc + circPt.gety(), yc - circPt.getx());
    setPixel(xc - circPt.gety(), yc - circPt.getx());
}

//绘制圆
void displayCircleMidpoint()
{
    glClear(GL_COLOR_BUFFER_BIT); //清除颜色
    glColor3f(0.0, 0.4, 0.2);     //设置当前颜色为白色
    circleMidp(100, 100, 50);
    glFlush(); //发送缓冲区
}
//----------------------------------------------------------------------------------

//----------------------------------------------------------------------------------
//B样条曲线
bool mouseRightIsDown3B = false;

struct Point3B
{
    int x, y;
    Point3B(){};
    Point3B(int tx, int ty)
    {
        x = tx;
        y = ty;
    }
};

std::vector<Point3B> p;
double getRatio(double t, double a, double b, double c, double d)
{
    return a * pow(t, 3) + b * pow(t, 2) + c * t + d;
}
double caculateSquarDistance(Point3B a, Point3B b)
{
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

int getIndexNearByMouse(int x, int y)
{
    double precision = 200; //精确度
    int index = -1;
    double Min;
    for (int i = 0; i < p.size(); i++)
    {
        double dis = caculateSquarDistance(p[i], Point3B(x, y));
        if (dis < precision)
        {
            if (index == -1)
            {
                index = i;
                Min = dis;
            }
            else if (dis < Min)
            {
                index = i;
                Min = dis;
            }
        }
    }
    return index;
}

void Bspline(Point3B a, Point3B b, Point3B c, Point3B d)
{
    int n = 500;
    double derta = 1.0 / n;
    glPointSize(2);
    glColor3d(0, 0, 0);
    glBegin(GL_LINE_STRIP);
    for (int i = 0; i <= n; i++)
    {
        double t = derta * i;
        double ratio[4];
        ratio[0] = getRatio(t, -1, 3, -3, 1);
        ratio[1] = getRatio(t, 3, -6, 0, 4);
        ratio[2] = getRatio(t, -3, 3, 3, 1);
        ratio[3] = getRatio(t, 1, 0, 0, 0);
        double x = 0, y = 0;
        x += ratio[0] * a.x + ratio[1] * b.x + ratio[2] * c.x + ratio[3] * d.x;
        y += ratio[0] * a.y + ratio[1] * b.y + ratio[2] * c.y + ratio[3] * d.y;
        x /= 6.0;
        y /= 6.0;
        glVertex2d(x, y);
    }
    glEnd();
}

void display3B()
{
    glClear(GL_COLOR_BUFFER_BIT); //清除颜色缓存和深度缓存

    //画点
    glPointSize(5);
    glColor3d(1, 0, 0);
    glBegin(GL_POINTS);
    for (int i = 0; i < p.size(); i++)
        glVertex2d(p[i].x, p[i].y);
    glEnd();

    //画线
    glLineWidth(2);
    glColor3d(0, 1, 0);
    glBegin(GL_LINE_STRIP);
    for (int i = 0; i < p.size(); i++)
        glVertex2d(p[i].x, p[i].y);
    glEnd();

    if (p.size() >= 4)
        for (int i = 0; i < p.size() - 3; i++)
            Bspline(p[i], p[i + 1], p[i + 2], p[i + 3]);

    glFlush();
}
void keyboard3B(unsigned char key, int x, int y)
{
    if (key == 27) //ESC
        exit(0);
    if (key == 8)
    { //退格键
        int index = getIndexNearByMouse(x, y);
        if (index == -1)
            return;
        p.erase(p.begin() + index);
        glutPostRedisplay();
    }
}
void mouse3B(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        Point3B t(x, y);
        p.push_back(t);
        glutPostRedisplay();
    }
    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
        mouseRightIsDown3B = true;
    if (button == GLUT_RIGHT_BUTTON && state == GLUT_UP)
        mouseRightIsDown3B = false;
}

//两个参数：窗口被移动后大小
void Reshape3B(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, w, h, 0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
//----------------------------------------------------------------------------------

//----------------------------------------------------------------------------------
//时钟
//当前时间，时 分 秒
float h = 0.0f;
float m = 0.0f;
float s = 0.0f;

//画时钟的函数
void displayClock(void)
{
    int Width = 600;
    int Height = 600;

    GLfloat PI = 3.1415926f;

    //用当前清除色清除颜色缓冲区，即设定窗口的背景色
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.1f, 0.2f, 0.1f); //设置颜色

    //画表盘
    int cx = Width / 2; //中心点
    int cy = Height / 2;
    int R = 100; // 半径长
    int n = 100;
    int i;
    circleMidp(cx, cy, R); //中点画圆法

    //绘制刻度
    int lines = 60;
    for (i = 0; i < lines; i++)
    {
        //5的倍数的刻度 粗点
        if (i % 5 == 0)
        {
            glLineWidth(3);
            glBegin(GL_LINES);
            glVertex2f(cx + (R - 10) * sin(2 * PI / lines * i), cy + (R - 10) * cos(2 * PI / lines * i));
            glVertex2f(cx + R * sin(2 * PI / lines * i), cy + R * cos(2 * PI / lines * i));
        }
        else
        {
            glLineWidth(2); //其余刻度
            glBegin(GL_LINES);
            glVertex2f(cx + (R - 5) * sin(2 * PI / lines * i), cy + (R - 5) * cos(2 * PI / lines * i));
            glVertex2f(cx + R * sin(2 * PI / lines * i), cy + R * cos(2 * PI / lines * i));
        }
    }

    //绘制时 分 秒针
    int h_len = 60;  //时针长度
    int m_len = 80;  //分针长度
    int s_len = 100; //秒针长度
    float s_Angle = s / 60.0;
    float m_Angle = (m * 60 + s) / 3600.0;
    float h2 = h >= 12 ? (h - 12) : h;
    float h_Angle = (h2 * 60 * 60 + m * 60 + s) / (12 * 60 * 60);

    //时
    glLineWidth(3); //时针宽度
    glBegin(GL_LINES);
    glVertex2f(cx, cy);
    glVertex2f(cx + h_len * sin(2 * PI * h_Angle), cy + h_len * cos(2 * PI * h_Angle));
    glEnd();

    //分
    glLineWidth(2); //分针宽度
    glBegin(GL_LINES);
    glVertex2f(cx, cy);
    glVertex2f(cx + m_len * sin(2 * PI * m_Angle), cy + m_len * cos(2 * PI * m_Angle));
    glEnd();

    //秒
    glLineWidth(1); //秒针宽度
    glBegin(GL_LINES);
    glVertex2f(cx - 2 * 5 * sin(2 * PI * s_Angle), cy - 2 * 5 * cos(2 * PI * s_Angle));
    glVertex2f(cx + (R - 10) * sin(2 * PI * s_Angle), cy + (R - 10) * cos(2 * PI * s_Angle));
    glEnd();

    //刷新
    glFlush();
}

//回调函数，配合定时器使用
void timerFunc(int value)
{
    s += 1;
    int carry1 = 0;
    if (s >= 60)
    {
        s = 0;
        carry1 = 1;
    }
    m += carry1;
    int carry2 = 0;
    if (m >= 60)
    {
        m = 0;
        carry2 = 1;
    }
    h += carry2;
    if (h >= 24)
        h = 0;

    glutPostRedisplay();               //重画
    glutTimerFunc(1000, timerFunc, 1); //每一秒执行一次
}

//初始化：设置背景，获取时间
void initClock(void)
{
    // 设置窗口为白色
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    // 获取本地当前时间
    SYSTEMTIME sys;
    GetLocalTime(&sys);
    h = sys.wHour;
    m = sys.wMinute;
    s = sys.wSecond;
}
//----------------------------------------------------------------------------------

//----------------------------------------------------------------------------------
//小球移动缩放
float angle22 = 0.0f;

void Init22()
{
    GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat mat_shininess[] = {50.0};

    //设置光源位置
    GLfloat light_position[] = {-10.0, 1.0, 20.0, 0.0};
    GLfloat light_position2[] = {1.0, 1.0, 1.0, 0.0};
    GLfloat light_position3[] = {1.0, 10.0, 1.0, 0.0};

    //环境光
    GLfloat lmodel_ambient[] = {0.1, 0.1, 0.1, 1.0};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);

    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_SMOOTH);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);   //指定材质属性
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess); //镜面反射指数

    //设置light0--white
    GLfloat white_light[] = {1.0, 1.0, 1.0, 1.0};      //设置编号、特性、颜色
    glLightfv(GL_LIGHT0, GL_POSITION, light_position); //设置位置
    glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, white_light);
    glEnable(GL_LIGHT0);

    //设置light1--red
    GLfloat red_light[] = {1.0, 0.0, 0.0, 1.0};
    glLightfv(GL_LIGHT1, GL_POSITION, light_position);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, red_light);
    glLightfv(GL_LIGHT1, GL_SPECULAR, red_light);
    glEnable(GL_LIGHT1);

    //设置light2--green
    GLfloat green_light[] = {0.0, 1.0, 0.0, 1.0};
    glLightfv(GL_LIGHT2, GL_POSITION, light_position2);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, green_light);
    glLightfv(GL_LIGHT2, GL_SPECULAR, green_light);
    glEnable(GL_LIGHT2);

    //设置light3--blue
    GLfloat blue_light[] = {0.0, 0.0, 1.0, 1.0};
    glLightfv(GL_LIGHT3, GL_POSITION, light_position3);
    glLightfv(GL_LIGHT3, GL_DIFFUSE, blue_light);
    glLightfv(GL_LIGHT3, GL_SPECULAR, blue_light);
    glEnable(GL_LIGHT3);

    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
}

void Display22()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //	glutSolidSphere(1.0, 100, 50);

    glPushMatrix();
    glRotatef(angle22, 0.0f, 0.0f, 0.0f); //角度+旋转轴
    glTranslatef(1.0f, 0.0f, 0.0f);       //移动
    glutSolidSphere(1.0, 100, 50);        //半径为1, 100条纬线, 50条经线
    glPopMatrix();

    glFlush();
}

void myIdle22()
{
    angle22 += 0.1f;
    if (angle22 >= 360.0f)
    {
        angle22 = 0.0f;
    }
    Display22();
}

void Reshape22(int w, int h)
{
    //使像素矩阵占据整个新窗口
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    //置当前矩阵为投影矩阵
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //改变窗口大小，图形形状保持不变
    if (w <= h)
    {
        glOrtho(-1.5, 1.5, -1.5 * (GLfloat)h / (GLfloat)w, 1.5 * (GLfloat)h / (GLfloat)w, -10.0, 10.0);
    }
    else
    {
        glOrtho(-1.5 * (GLfloat)w / (GLfloat)h, 1.5 * (GLfloat)w / (GLfloat)h, -1.5, 1.5, -10.0, 10.0);
    }

    //模型矩阵
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
//----------------------------------------------------------------------------------

//----------------------------------------------------------------------------------
//Liang-Barsky 线段裁剪算法
class wcPt2D
{

public:
    GLfloat x, y;

public:
    /*
Default Constructor:initalize position 48(0.0,0.0).*/
    wcPt2D()
    {
        x = y = 0.0;
    }

    wcPt2D(GLfloat nx, GLfloat ny) : x(nx), y(ny) {}

    wcPt2D(const wcPt2D &pCopy)
    {
        this->x = pCopy.x;
        this->y = pCopy.y;
    }

    void setCoords(GLfloat xCoord, GLfloat yCoord)
    {
        x = xCoord;
        y = yCoord;
        return;
    }

    wcPt2D &operator=(wcPt2D p2)
    {
        this->x = p2.getx();
        this->y = p2.gety();
        return *this;
    }

    GLfloat getx() const
    {
        return x;
    }
    GLfloat gety() const
    {
        return y;
    }
};

inline GLint round16(const GLfloat a)
{
    return GLint(a + 0.5);
}

GLint clipTest(GLfloat p, GLfloat q, GLfloat *u1, GLfloat *u2)
{
    GLfloat r;
    GLint returnValue = true;
    if (p < 0.0)
    {
        r = q / p;
        if (r > *u2)
        {
            returnValue = false;
        }
        else if (r > *u1)
        {
            *u1 = r;
        }
    }
    else
    {
        if (p > 0.0)
        {
            r = q / p;
            if (r < *u1)
            {
                returnValue = false;
            }
            else if (r < *u2)
            {
                *u2 = r;
            }
        }
        else
        {

            if (q < 0.0)
            {
                returnValue = false;
            }
        }
    }
    return (returnValue);
}

void lineClipLiangBrask(wcPt2D winMin, wcPt2D winMax, wcPt2D p1, wcPt2D p2)
{
    GLfloat u1 = 0.0, u2 = 1.0, dx = p2.getx() - p1.getx(), dy;
    if (clipTest(-dx, p1.getx() - winMin.getx(), &u1, &u2))
    {
        if (clipTest(dx, winMax.getx() - p1.getx(), &u1, &u2))
        {
            dy = p2.gety() - p1.gety();
            if (clipTest(-dy, p1.gety() - winMin.gety(), &u1, &u2))
            {
                if (clipTest(dy, winMax.gety() - p1.gety(), &u1, &u2))
                {
                    if (u2 < 1.0)
                    {
                        p2.setCoords(p1.getx() + u2 * dx, p1.gety() + u2 * dy);
                    }
                    if (u1 > 0.0)
                    {
                        p1.setCoords(p1.getx() + u1 * dx, p1.gety() + u1 * dy);
                    }
                    lineDDA(round16(p1.getx()), round16(p1.gety()), round16(p2.getx()), round16(p2.gety()));
                    //					return 2;
                }
            }
        }
    }

    return;
}

int lineClipLiangBrask(wcPt2D winMin, wcPt2D winMax, wcPt2D p1, wcPt2D p2, wcPt2D pOut[])
{
    GLfloat u1 = 0.0, u2 = 1.0, dx = p2.getx() - p1.getx(), dy;
    if (clipTest(-dx, p1.getx() - winMin.getx(), &u1, &u2))
    {
        if (clipTest(dx, winMax.getx() - p1.getx(), &u1, &u2))
        {
            dy = p2.gety() - p1.gety();
            if (clipTest(-dy, p1.gety() - winMin.gety(), &u1, &u2))
            {
                if (clipTest(dy, winMax.gety() - p1.gety(), &u1, &u2))
                {
                    if (u2 < 1.0)
                    {
                        p2.setCoords(p1.getx() + u2 * dx, p1.gety() + u2 * dy);
                    }
                    if (u1 > 0.0)
                    {
                        p1.setCoords(p1.getx() + u1 * dx, p1.gety() + u1 * dy);
                    }
                    pOut[0] = p1;
                    pOut[1] = p2;
                    return 2;
                }
            }
        }
    }

    return 0;
}

void display16()
{
    glClear(GL_COLOR_BUFFER_BIT);
    //可视化边界:
    const int minX = 100, minY = 100, maxX = 300, maxY = 300;
    glColor3f(1.0, 0.0, 0.0);
    lineDDA(minX, minY, minX, maxY);
    lineDDA(minX, minY, maxX, minY);
    lineDDA(maxX, maxY, minX, maxY);
    lineDDA(maxX, maxY, maxX, minY);

    glColor3f(0.0, 1.0, 0.0);
    GLint n = 5;
    wcPt2D pIn[n];
    pIn[0].setCoords(0, 200);
    pIn[1].setCoords(150, 250);
    pIn[2].setCoords(250, 250);
    pIn[3].setCoords(400, 200);
    pIn[4].setCoords(200, 50);

    for (int i = 0; i < n; ++i)
    {
        lineDDA(pIn[i].x, pIn[i].y, pIn[(i + 1) % n].x, pIn[(i + 1) % n].y);
    }

    wcPt2D pOut[20];
    wcPt2D tempPOut[2];
    int outCount = 0;
    int flag = 0;
    for (int i = 0; i < n; ++i)
    {
        flag = lineClipLiangBrask(wcPt2D(minX, minY), wcPt2D(maxX, maxY), pIn[i], pIn[(i + 1) % n], tempPOut);
        if (flag == 2)
        {
            for (int j = 0; j < 2; ++j)
            {
                pOut[outCount++] = tempPOut[j];
            }
        }
    }

    glColor3f(0.0, 0.0, 1.0);
    int i = 1;
    for (; i <= outCount; ++i)
    {
        lineDDA(pOut[i - 1].x, pOut[i - 1].y, pOut[i % outCount].x, pOut[i % outCount].y);
    }

    glFlush();

    return;
}

//初始化绘制
void init16()
{
    glClearColor(1.0, 1.0, 1.0, 0.0); //清除颜色设置
    glMatrixMode(GL_PROJECTION);      //设置投影方式
    gluOrtho2D(0.0, windowWidge * 1.0, 0.0, windowHeight * 1.0);
    return;
}
//----------------------------------------------------------------------------------

//----------------------------------------------------------------------------------
//Sutherland-Hodgman多边形裁剪算法
const int Left = 0, Right = 1, Bottom = 2, Top = 3; //左右下上 分别裁剪
const GLint nClip = 4;                              //边界边数

//判断点与边界的位置关系
GLint inside(wcPt2D p, int b, wcPt2D wMin, wcPt2D wMax)
{
    switch (b)
    {
    case Left:
        if (p.getx() < wMin.getx())
            return false;
        break;
    case Right:
        if (p.getx() > wMax.getx())
            return false;
        break;
    case Bottom:
        if (p.gety() < wMin.gety())
            return false;
        break;
    case Top:
        if (p.gety() > wMax.gety())
            return false;
        break;
    }
    return true;
}

//判断是否相交
GLint cross(wcPt2D p1, wcPt2D p2, int winEdge, wcPt2D wMin, wcPt2D wMax)
{
    if (inside(p1, winEdge, wMin, wMax) == inside(p2, winEdge, wMin, wMax))
        return false;
    else
        return true;
}

//返回交点
wcPt2D intersect(wcPt2D p1, wcPt2D p2, int winEdge, wcPt2D wMin, wcPt2D wMax)
{
    wcPt2D iPt;
    GLfloat m;

    if (p1.getx() != p2.getx())
    {
        m = (p1.gety() - p2.gety()) / (p1.getx() - p2.getx());
    }
    switch (winEdge)
    {
    case Left:
        iPt.x = wMin.x;
        iPt.y = p2.y + (wMin.x - p2.x) * m;
        break;
    case Right:
        iPt.x = wMax.x;
        iPt.y = p2.y + (wMax.x - p2.x) * m;
        break;
    case Bottom:
        iPt.y = wMin.y;
        if (p1.x != p2.x)
            iPt.x = p2.x + (wMin.y - p2.y) / m;
        else
            iPt.x = p2.x;
        break;
    case Top:
        iPt.y = wMax.y;
        if (p1.x != p2.x)
            iPt.x = p2.x + (wMax.y - p2.y) / m;
        else
            iPt.x = p2.x;
        break;
    default:
        break;
    }
    return iPt;
}

//裁剪点
void clipPoint(wcPt2D p, int winEdge, wcPt2D wMin, wcPt2D wMax, wcPt2D *pOut, int *cnt, wcPt2D first[], wcPt2D *s)
{
    wcPt2D iPt;

    //无交点则保存
    if (first[winEdge].x == 0 && first[winEdge].y == 0)
    {
        first[winEdge] = p;
    }
    else
    {
        //有交点则找到交点并保存
        if (cross(p, s[winEdge], winEdge, wMin, wMax))
        {
            iPt = intersect(p, s[winEdge], winEdge, wMin, wMax);
            if (winEdge < Top)
            {
                clipPoint(iPt, winEdge + 1, wMin, wMax, pOut, cnt, first, s);
            }
            else
            {
                pOut[*cnt] = iPt;
                (*cnt)++;
            }
        }
    }

    s[winEdge] = p;

    //如果点在边内，换下一条边
    if (inside(p, winEdge, wMin, wMax))
    {
        if (winEdge < Top)
            clipPoint(p, winEdge + 1, wMin, wMax, pOut, cnt, first, s);
        else
        {
            pOut[*cnt] = p;
            (*cnt)++;
        }
    }
}

void closeClip(wcPt2D wMin, wcPt2D wMax, wcPt2D *pOut, GLint *cnt, wcPt2D first[], wcPt2D *s)
{
    wcPt2D pt;
    int winEdge;
    for (winEdge = Left; winEdge <= Top; winEdge++)
    {
        if (cross(s[winEdge], first[winEdge], winEdge, wMin, wMax))
        {
            pt = intersect(s[winEdge], first[winEdge], winEdge, wMin, wMax);
            if (winEdge < Top)
            {
                clipPoint(pt, winEdge + 1, wMin, wMax, pOut, cnt, first, s);
            }
            else
            {
                pOut[*cnt] = pt;
                (*cnt)++;
            }
        }
    }
}

//多边形裁剪
GLint polygonClipSuthHodg(wcPt2D wMin, wcPt2D wMax, GLint n, wcPt2D *pIn, wcPt2D *pOut)
{
    wcPt2D first[nClip], s[nClip];
    GLint k, cnt = 0;
    for (k = 0; k < n; k++)
        clipPoint(pIn[k], Left, wMin, wMax, pOut, &cnt, first, s);
    closeClip(wMin, wMax, pOut, &cnt, first, s);
    return cnt;
}

//绘制程序
void display17()
{
    glClear(GL_COLOR_BUFFER_BIT); //将屏幕设置为黑色

    //Sutherland-Hodgman多边形裁剪算法
    glClear(GL_COLOR_BUFFER_BIT);

    //裁剪区域
    const int minX = 100, minY = 100, maxX = 300, maxY = 300;
    glColor3f(1.0, 0.0, 0.0);
    lineDDA(minX, minY, minX, maxY);
    lineDDA(minX, minY, maxX, minY);
    lineDDA(maxX, maxY, minX, maxY);
    lineDDA(maxX, maxY, maxX, minY);

    //多边形
    glColor3f(0.0, 1.0, 0.0);
    GLint n = 4;
    wcPt2D pIn[n];
    pIn[0].setCoords(50, 200);
    pIn[1].setCoords(200, 350);
    pIn[2].setCoords(350, 200);
    pIn[3].setCoords(200, 50);

    for (int i = 0; i < n; ++i)
    {
        lineDDA(pIn[i].x, pIn[i].y, pIn[(i + 1) % n].x, pIn[(i + 1) % n].y);
    }

    wcPt2D pOut[20];

    int count = polygonClipSuthHodg(wcPt2D(minX, minY), wcPt2D(maxX, maxY), n, pIn, pOut);

    glColor3f(0.0, 0.0, 1.0);
    int i = 1;
    for (; i <= count; ++i)
    {
        lineDDA(pOut[i - 1].x, pOut[i - 1].y, pOut[i % count].x, pOut[i % count].y);
    }

    glFlush();

    return;
}

//初始化绘制
void init17()
{
    glClearColor(1.0, 1.0, 1.0, 0.0); //清除颜色设置
    glMatrixMode(GL_PROJECTION);      //设置投影方式
    gluOrtho2D(0.0, windowWidge * 1.0, 0.0, windowHeight * 1.0);
    return;
}
//----------------------------------------------------------------------------------

//----------------------------------------------------------------------------------
//纹理映射
//使用stb_image让其支持的图片格式更多
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

void handleKeypress(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27: //Escape key
        exit(0);
    }
}

//image类储存加载到内存中的图片
struct Image
{
    int width = 0;
    int height = 0;
    int nrChannels = 0;
    unsigned char *data = nullptr;
};

//图片加载函数
/**
 * @brief loadImage	将图片加载到内存
 * @param fileName	图片文件名(相对路径)
 * @return
 */
Image *loadImage(const char *fileName)
{
    Image *image = new Image();
    //翻转图像, 否则图像是反的
    stbi_set_flip_vertically_on_load(true);
    image->data = stbi_load(fileName, &image->width, &image->height,
                            &image->nrChannels, 0);
    return image;
}

//纹理加载函数
/**
 * @brief loadTexture 将图片加载为纹理
 * @param image	已经加载到内存中的图片
 * @return
 */
GLuint loadTexture(Image *image)
{
    GLuint textureId;
    //纹理初始化
    glGenTextures(1, &textureId);
    //选定当前要编辑的纹理
    glBindTexture(GL_TEXTURE_2D, textureId);

    if (image->nrChannels == 3)
    {
        glTexImage2D(GL_TEXTURE_2D,               //二维纹理永远是GL_TEXTURE_2D
                     0,                           //基本都是用0
                     GL_RGB,                      //纹理储存格式
                     image->width, image->height, //图像宽高
                     0,                           //永远是0
                     GL_RGB,                      //纹理数据格式, 必须与上头相同
                     GL_UNSIGNED_BYTE,            //纹理数据类型, 基本用GL_UNSIGNED_BYTE
                     image->data);                //图片data数组指针
    }
    else
    {
        //如果是PNG图像就有alpha通道, 用RGBA
        glTexImage2D(GL_TEXTURE_2D,               //二维纹理永远是GL_TEXTURE_2D
                     0,                           //基本都是用0
                     GL_RGBA,                     //纹理储存格式
                     image->width, image->height, //图像宽高
                     0,                           //永远是0
                     GL_RGBA,                     //纹理数据格式, 必须与上头相同
                     GL_UNSIGNED_BYTE,            //纹理数据类型, 基本用GL_UNSIGNED_BYTE
                     image->data);                //图片data数组指针
    }
    return textureId; //返回加载的纹理ID
}

GLuint _textureId; //The id of the texture

void initRendering()
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);

    //加载纹理用的图片
    //支持绝大多数主流格式
    //注意图像分辨率不要太大(玄学错误), 否则纹理出错
    Image *image = nullptr;
    image = loadImage("1.bmp");
    _textureId = loadTexture(image);
    delete image;
    image = nullptr;

    //	Image* image = loadTexture("1.bmp");
    //	_textureId = loadTexture(image);
    //	delete image;
}

void handleResize32(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (float)w / (float)h, 1.0, 200.0);
}

void drawScene()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glTranslatef(0.0f, 1.0f, -6.0f);

    GLfloat ambientLight[] = {0.2f, 0.2f, 0.2f, 1.0f};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);

    GLfloat directedLight[] = {0.7f, 0.7f, 0.7f, 1.0f};
    GLfloat directedLightPos[] = {-10.0f, 15.0f, 20.0f, 0.0f};
    glLightfv(GL_LIGHT0, GL_DIFFUSE, directedLight);
    glLightfv(GL_LIGHT0, GL_POSITION, directedLightPos);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureId);

    //底部图形
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glColor3f(0.2f, 0.2f, 0.2f); //设置颜色
    glBegin(GL_QUADS);

    glNormal3f(0.0, 1.0f, 0.0f);    //法向量
    glTexCoord2f(0.0f, 0.0f);       //纹理映射
    glVertex3f(-2.5f, -2.5f, 2.5f); //绘图
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(2.5f, -2.5f, 2.5f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(2.5f, -2.5f, -2.5f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-2.5f, -2.5f, -2.5f);

    glEnd();

    //中间的三角形
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_TRIANGLES);

    glNormal3f(0.0f, 0.0f, 1.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-2.5f, -2.5f, -2.5f);
    glTexCoord2f(0.5f, 1.0f);
    glVertex3f(0.0f, 2.5f, -2.5f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(2.5f, -2.5f, -2.5f);

    glEnd();

    glutSwapBuffers();
}

//----------------------------------------------------------------------------------

//----------------------------------------------------------------------------------
//单光源
void Initsinglelight()
{
    GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat mat_shininess[] = {50.0};

    //设置光源位置
    GLfloat light_position[] = {-10.0, 1.0, 20.0, 0.0};
    GLfloat light_position2[] = {1.0, 1.0, 1.0, 0.0};
    GLfloat light_position3[] = {1.0, 10.0, 1.0, 0.0};

    //环境光
    GLfloat lmodel_ambient[] = {0.1, 0.1, 0.1, 1.0};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);

    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_SMOOTH);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);   //指定材质属性
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess); //镜面反射指数

    //设置light0--white
    GLfloat white_light[] = {1.0, 1.0, 1.0, 1.0};      //设置编号、特性、颜色
    glLightfv(GL_LIGHT0, GL_POSITION, light_position); //设置位置
    glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, white_light);
    glEnable(GL_LIGHT0);

    //设置light1--red
    GLfloat red_light[] = {1.0, 0.0, 0.0, 1.0};
    glLightfv(GL_LIGHT1, GL_POSITION, light_position);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, red_light);
    glLightfv(GL_LIGHT1, GL_SPECULAR, red_light);
    //	glEnable(GL_LIGHT1);

    //设置light2--green
    GLfloat green_light[] = {0.0, 1.0, 0.0, 1.0};
    glLightfv(GL_LIGHT2, GL_POSITION, light_position2);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, green_light);
    glLightfv(GL_LIGHT2, GL_SPECULAR, green_light);
    //	glEnable(GL_LIGHT2);

    //设置light3--blue
    GLfloat blue_light[] = {0.0, 0.0, 1.0, 1.0};
    glLightfv(GL_LIGHT3, GL_POSITION, light_position3);
    glLightfv(GL_LIGHT3, GL_DIFFUSE, blue_light);
    glLightfv(GL_LIGHT3, GL_SPECULAR, blue_light);
    //	glEnable(GL_LIGHT3);

    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
}
//----------------------------------------------------------------------------------

//----------------------------------------------------------------------------------

//----------------------------------------------------------------------------------

//----------------------------------------------------------------------------------

//----------------------------------------------------------------------------------

//----------------------------------------------------------------------------------
//可视化 天空盒+几何模型+视点变换+坐标变换

//视线参数化, 方便更改
static GLfloat xequalzero[] = {1.0, 1.0, 1.0, 1.0};
static double lookat[] = {0.0, -5.0, 7.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0};
static double perspective[] = {90.0, 1.0f, 1.0f, 50.0f};
static GLfloat *currentCoeff;
static GLenum currentPlane;
static GLint currentGenMode;
static float roangles;

const int MAX = 20;       //最大纹理数量
int textureId[MAX] = {0}; //纹理ID:

//初始化绘制
void init41()
{
    glClearColor(0.0, 0.0, 0.0, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //清理颜色和深度缓存

    //创建透视效果视图
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(perspective[0], perspective[1],
                   perspective[2], perspective[3]);

    //定义视点:
    //头两个不动
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(lookat[0], lookat[1], lookat[2],
              lookat[3], lookat[4], lookat[5],
              lookat[6], lookat[7], lookat[8]);

    //启用深度测试:
    //在绘制3D物体时必要, 否则无法判断消隐关系
    glEnable(GL_DEPTH_TEST);

    //定义默认光源:
    {
        //光源位置, 默认在z轴从上到下的光
        GLfloat sun_light_position[] = {0.0f, 0.0f, 30.0f, 1.0f}; //光源的位置在世界坐标系圆心，齐次坐标形式
        //RGBA模式的环境光
        GLfloat sun_light_ambient[] = {0.1f, 0.1f, 0.1f, 1.0f};
        //RGBA模式的漫反射光，全白光
        GLfloat sun_light_diffuse[] = {1.0f, 1.0, 1.0, 1.0f};
        //RGBA模式下的镜面光 ，全白光
        GLfloat sun_light_specular[] = {1.0f, 1.0, 1.0, 1.0f};
        //应用光照:
        glLightfv(GL_LIGHT0, GL_POSITION, sun_light_position);
        glLightfv(GL_LIGHT0, GL_AMBIENT, sun_light_ambient);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, sun_light_diffuse);
        glLightfv(GL_LIGHT0, GL_SPECULAR, sun_light_specular);

        //开启灯光
        glEnable(GL_LIGHT0);
        glEnable(GL_LIGHTING);
    }

    //开启法向量自动重置
    glEnable(GL_NORMALIZE);

    //开启纹理&颜色叠加
    glEnable(GL_COLOR_MATERIAL);

    //加载纹理用的图片
    Image *image = nullptr;
    image = loadImage("front.jpg");
    textureId[0] = loadTexture(image);
    delete image;
    image = nullptr;

    image = loadImage("back.jpg");
    textureId[1] = loadTexture(image);
    delete image;
    image = nullptr;

    image = loadImage("bottom.jpg");
    textureId[2] = loadTexture(image);
    delete image;
    image = nullptr;

    image = loadImage("top.jpg");
    textureId[3] = loadTexture(image);
    delete image;
    image = nullptr;

    image = loadImage("right.jpg");
    textureId[4] = loadTexture(image);
    delete image;
    image = nullptr;

    image = loadImage("left.jpg");
    textureId[5] = loadTexture(image);
    delete image;
    image = nullptr;

    image = loadImage("universe.jpg");
    textureId[6] = loadTexture(image);
    delete image;
    image = nullptr;

    return;
}

//x,y,z轴旋转角度分量
GLfloat xtri = 0;
GLfloat ytri = 0;
GLfloat ztri = 0;
GLfloat xtri2 = 0;

//全局物体旋转方向:
float xrotate = 0.0;
float yrotate = 0.0;
float zrotate = 0.0;

GLuint texName;

#define SOLID 1
#define WIRE 2
void drawBall(double R, double x, double y, double z, double angle, double x2, double y2, double z2, int MODE = SOLID)
{
    const int PREC = 64;
    glPushMatrix();
    glRotatef(angle, x2, y2, z2);
    glTranslated(x, y, z);
    glScalef(R, R, R);
    if (MODE == SOLID)
    {
        glutSolidSphere(0.5, PREC, PREC);
    }
    else if (MODE == WIRE)
    {
        glutWireSphere(0.5, PREC, PREC);
    }
    glPopMatrix();
    return;
}

//显示调用函数
void display()
{
    //清除当前颜色&深度缓存
    glClearColor(0.0, 0.0, 0.0, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //在display中更新视点:
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //第一组eyex, eyey,eyez 相机在世界坐标的位置
    //第二组centerx,centery,centerz 相机镜头对准的物体在世界坐标的位置
    //第三组upx,upy,upz 相机向上的方向在世界坐标中的方向
    gluLookAt(lookat[0], lookat[1], lookat[2],
              lookat[3], lookat[4], lookat[5],
              lookat[6], lookat[7], lookat[8]);

    //矩阵旋转, 实现物体绕焦点旋转
    //绘制所有物体必须加上这个
    glRotatef(xrotate, 1, 0, 0);
    glRotatef(yrotate, 0, 1, 0);
    glRotatef(zrotate, 0, 0, 1);

    //	添加物体:
    {
        //这是开启glEnable(GL_COLOR_MATERIAL)之后设置材质颜色的方法:
        //具体使用glColor4f 还是 glColor3f 根据main中的设置而定
        glColorMaterial(GL_FRONT, GL_AMBIENT);
        glColor4f(0.0f, 0.0f, 1.0f, 1.0f);

        glColorMaterial(GL_FRONT, GL_DIFFUSE);
        glColor4f(0.0f, 0.0f, 1.0f, 1.0f);

        glColorMaterial(GL_FRONT, GL_SPECULAR);
        glColor4f(1.0f, 1.0, 1.0, 1.0f);

        glColorMaterial(GL_FRONT, GL_EMISSION);
        glColor4f(0.0f, 0.0f, 0.0f, 1.0f);

        //上头只能设置4个属性
        //材质的镜面指数依然需要使用glMaterialf设置
        GLfloat mat_shininess = 32.0f;
        glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);

        //控制物体三维几何变换 (组合体适用)
        //使用全局变量, 便于在Idle中修改
        glPushMatrix();
        ////		glRotatef(ztri,0.0f,0.0f,1.0f);                // 绕Z轴旋转
        ////		glTranslatef (2.0,0.0,0.0);
        //
        //		//画一个立方体
        ////		glutSolidCube (2);
        //		//glRotatef(xtri,1.0f,0.0f,0.0f);        // 绕X轴旋转
        //
        //		glRotatef(ytri,0.0f,1.0f,0.0f);          // 绕Y轴旋转
        //		glTranslated (3.0,0.0,0.0);
        //		glColor3f(1.0,0.0,0.0);	//设置颜色
        //		glBindTexture(GL_TEXTURE_2D,textureId[0]);
        //		//画一个球
        //		glutSolidSphere (0.5,20,20);
        //
        //		glRotatef(ytri,0.0f,1.0f,0.0f);          // 绕Y轴旋转
        //		glTranslated (5.0,0.0,0.0);
        //		glColor3f(1.0,0.0,0.0);	//设置颜色
        //		//画一个球
        //		glutSolidSphere (0.5,20,20);
        //
        //		glRotatef(ytri,0.0f,1.0f,0.0f);          // 绕Y轴旋转
        //		glTranslated (7.0,0.0,0.0);
        //		glColor3f(1.0,0.0,0.0);	//设置颜色
        //		//画一个球
        //		glutSolidSphere (0.5,20,20);
        //
        //
        //		glRotatef(ytri,0.0f,1.0f,0.0f);                // 绕Y轴旋转
        //		glTranslated (3.0,0.0,0.0);
        //		glColor3f(0.0,1.0,0.0);	//设置颜色
        //		glutSolidCube (2);

        glPopMatrix();
    }

    //添加贴图
    GLfloat len = 20.0f;
    GLfloat _len = -20.0f;

    //前面
    glEnable(GL_TEXTURE_2D);
    {
        //设置当前操作的纹理
        glBindTexture(GL_TEXTURE_2D, textureId[0]);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        //颜色叠加为白色, 即保留原色彩不变
        glColor3f(1.0f, 1.0f, 1.0f);
        //绘制四边形
        glBegin(GL_QUADS);
        {
            //确定绘制平面法向量
            glNormal3f(0.0, 1.0f, 0.0f);
            //纹理映射, 0~1, 超过将复制平铺
            glTexCoord2f(0.0f, 0.0f);
            glVertex3f(_len, _len, len); // 纹理和四边形的左下
            glTexCoord2f(1.0f, 0.0f);
            glVertex3f(len, _len, len); // 纹理和四边形的右下
            glTexCoord2f(1.0f, 1.0f);
            glVertex3f(len, len, len); // 纹理和四边形的右上
            glTexCoord2f(0.0f, 1.0f);
            glVertex3f(_len, len, len); // 纹理和四边形的左上
        }
        glEnd();
    }
    glDisable(GL_TEXTURE_2D);

    //后面
    glEnable(GL_TEXTURE_2D);
    {
        //设置当前操作的纹理
        glBindTexture(GL_TEXTURE_2D, textureId[1]);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        //颜色叠加为白色, 即保留原色彩不变
        glColor3f(1.0f, 1.0f, 1.0f);
        //绘制四边形
        glBegin(GL_QUADS);
        {
            //确定绘制平面法向量
            glNormal3f(0.0, 1.0f, 0.0f);
            //纹理映射, 0~1, 超过将复制平铺
            glTexCoord2f(1.0f, 0.0f);
            glVertex3f(_len, _len, _len); // 纹理和四边形的右下
            glTexCoord2f(1.0f, 1.0f);
            glVertex3f(_len, len, _len); // 纹理和四边形的右上
            glTexCoord2f(0.0f, 1.0f);
            glVertex3f(len, len, _len); // 纹理和四边形的左上
            glTexCoord2f(0.0f, 0.0f);
            glVertex3f(len, _len, _len); // 纹理和四边形的左下
        }
        glEnd();
    }
    glDisable(GL_TEXTURE_2D);

    //底面
    glEnable(GL_TEXTURE_2D);
    {
        //设置当前操作的纹理
        glBindTexture(GL_TEXTURE_2D, textureId[3]);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        //颜色叠加为白色, 即保留原色彩不变
        glColor3f(1.0f, 1.0f, 1.0f);
        //绘制四边形
        glBegin(GL_QUADS);
        {
            //确定绘制平面法向量
            glNormal3f(0.0, 1.0f, 0.0f);
            //纹理映射, 0~1, 超过将复制平铺
            glTexCoord2f(1.0f, 0.0f);
            glVertex3f(_len, len, _len); // 纹理和四边形的左上
            glTexCoord2f(1.0f, 1.0f);
            glVertex3f(_len, len, len); // 纹理和四边形的左下
            glTexCoord2f(0.0f, 1.0f);
            glVertex3f(len, len, len); // 纹理和四边形的右下
            glTexCoord2f(0.0f, 0.0f);
            glVertex3f(len, len, -len); // 纹理和四边形的右上
        }
        glEnd();
    }
    glDisable(GL_TEXTURE_2D);

    //顶面
    glEnable(GL_TEXTURE_2D);
    {
        //设置当前操作的纹理
        glBindTexture(GL_TEXTURE_2D, textureId[2]);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        //颜色叠加为白色, 即保留原色彩不变
        glColor3f(1.0f, 1.0f, 1.0f);
        //绘制四边形
        glBegin(GL_QUADS);
        {
            //确定绘制平面法向量
            glNormal3f(0.0, 1.0f, 0.0f);
            //纹理映射, 0~1, 超过将复制平铺
            glTexCoord2f(1.0f, 1.0f);
            glVertex3f(_len, _len, _len); // 纹理和四边形的右上
            glTexCoord2f(0.0f, 1.0f);
            glVertex3f(len, _len, _len); // 纹理和四边形的左上
            glTexCoord2f(0.0f, 0.0f);
            glVertex3f(len, _len, len); // 纹理和四边形的左下
            glTexCoord2f(1.0f, 0.0f);
            glVertex3f(_len, _len, len); // 纹理和四边形的右下
        }
        glEnd();
    }
    glDisable(GL_TEXTURE_2D);

    //右面
    glEnable(GL_TEXTURE_2D);
    {
        //设置当前操作的纹理
        glBindTexture(GL_TEXTURE_2D, textureId[5]);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        //颜色叠加为白色, 即保留原色彩不变
        glColor3f(1.0f, 1.0f, 1.0f);
        //绘制四边形
        glBegin(GL_QUADS);
        {
            //确定绘制平面法向量
            glNormal3f(0.0, 1.0f, 0.0f);
            //纹理映射, 0~1, 超过将复制平铺
            glTexCoord2f(1.0f, 0.0f);
            glVertex3f(len, _len, _len); // 纹理和四边形的右下
            glTexCoord2f(1.0f, 1.0f);
            glVertex3f(len, len, _len); // 纹理和四边形的右上
            glTexCoord2f(0.0f, 1.0f);
            glVertex3f(len, len, len); // 纹理和四边形的左上
            glTexCoord2f(0.0f, 0.0f);
            glVertex3f(len, _len, len); // 纹理和四边形的左下
        }
        glEnd();
    }
    glDisable(GL_TEXTURE_2D);

    //左面
    glEnable(GL_TEXTURE_2D);
    {
        //设置当前操作的纹理
        glBindTexture(GL_TEXTURE_2D, textureId[4]);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        //颜色叠加为白色, 即保留原色彩不变
        glColor3f(1.0f, 1.0f, 1.0f);
        //绘制四边形
        glBegin(GL_QUADS);
        {
            //确定绘制平面法向量
            glNormal3f(0.0, 1.0f, 0.0f);
            //纹理映射, 0~1, 超过将复制平铺
            glTexCoord2f(0.0f, 0.0f);
            glVertex3f(_len, _len, _len); // 纹理和四边形的左下
            glTexCoord2f(1.0f, 0.0f);
            glVertex3f(_len, _len, len); // 纹理和四边形的右下
            glTexCoord2f(1.0f, 1.0f);
            glVertex3f(_len, len, len); // 纹理和四边形的右上
            glTexCoord2f(0.0f, 1.0f);
            glVertex3f(_len, len, _len); // 纹理和四边形的左上
        }
        glEnd();
    }
    glDisable(GL_TEXTURE_2D);

    //	球体贴图
    //	贴图一定要长, 不然会出现拉伸等情况
    //	启用2D纹理
    glEnable(GL_TEXTURE_2D);
    {
        //设置当前操作的纹理
        glBindTexture(GL_TEXTURE_2D, textureId[6]);
        //设置环绕方式
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        //设置纹理过滤
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        //颜色叠加为白色, 即保留原色彩不变
        glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
        currentCoeff = xequalzero;
        currentGenMode = GL_OBJECT_LINEAR;
        currentPlane = GL_OBJECT_PLANE;
        //自动生成纹理坐标, 而不需要使用glTexCoord显式分配
        glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, currentGenMode);
        glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, currentGenMode);
        glTexGenfv(GL_S, currentPlane, currentCoeff);
        //启动自动生成纹理
        //不启用后头的glTexGen无法使用
        glEnable(GL_TEXTURE_GEN_S);
        glEnable(GL_TEXTURE_GEN_T);

        drawBall(3, 0, 0, 0, xtri, 0, 0, 1);
        //关闭自动生成纹理
        //不然影响其他手动贴图
        glDisable(GL_TEXTURE_GEN_S);
        glDisable(GL_TEXTURE_GEN_T);
    }
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    {
        //设置当前操作的纹理
        glBindTexture(GL_TEXTURE_2D, textureId[6]);
        //设置环绕方式
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        //设置纹理过滤
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        //颜色叠加为白色, 即保留原色彩不变
        glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
        currentCoeff = xequalzero;
        currentGenMode = GL_OBJECT_LINEAR;
        currentPlane = GL_OBJECT_PLANE;
        //自动生成纹理坐标, 而不需要使用glTexCoord显式分配
        glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, currentGenMode);
        glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, currentGenMode);
        glTexGenfv(GL_S, currentPlane, currentCoeff);
        //启动自动生成纹理
        //不启用后头的glTexGen无法使用
        glEnable(GL_TEXTURE_GEN_S);
        glEnable(GL_TEXTURE_GEN_T);

        drawBall(3, 5.0, 0, 0, ytri, 0, 1.0f, 0);
        //关闭自动生成纹理
        //不然影响其他手动贴图
        glDisable(GL_TEXTURE_GEN_S);
        glDisable(GL_TEXTURE_GEN_T);
    }
    glDisable(GL_TEXTURE_2D);

    //刷新缓冲区
    glutSwapBuffers();
    return;
}

//空闲调用函数
void myIdle(void)
{
    //执行画面更新任务

    //	xtri+=0.5f;
    //	ytri+=1;
    //	ztri+=1;

    xtri += 1;
    ytri += 1;
    ztri += 0;

    xtri2 += 1;
    if (xtri2 >= 10)
    {
        xtri2 = 0;
    }

    //窗口重绘函数:
    //通常用glutPostRedisplay, 其更为智能一点
    glutPostRedisplay();

    //通常需要一个sleep来防止帧率过高, 这里sleep 16ms, 约等于60fps
    Sleep(16);
    return;
}

//窗口尺寸重置函数:
//当窗口大小变化时调用, 保证图形不变形
void handleResize(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    perspective[1] = (float)w / (float)h;
    gluPerspective(perspective[0], perspective[1],
                   perspective[2], perspective[3]);
    return;
}

//键盘响应函数:
void keyboradAck(unsigned char key, int x, int y)
{
    printf("%d=%c, x=%d, y=%d\n", key, key, x, y);
    static double flag = 1.0;

    switch (key)
    {
        //控制视角以当前视点为中心旋转
    case 'w':
    {
        printf("up\n");
        xrotate += 2;
        break;
    }
    case 's':
    {
        printf("down\n");
        xrotate -= 2;
        break;
    }
    case 'a':
    {
        printf("left\n");
        yrotate += 2;
        break;
    }
    case 'd':
    {
        printf("right\n");
        yrotate -= 2;
        break;
    }
    case 'q':
    {
        printf("q\n");
        zrotate += 2;
        break;
    }
    case 'e':
    {
        printf("e\n");
        zrotate -= 2;
        break;
    }

    default:
    {
    }
    }

    return;
}

void specialKeyAck(int key, int x, int y)
{
    printf("%d=%c, x=%d, y=%d\n", key, key, x, y);
    //控制前进后退
    if (key == GLUT_KEY_UP)
    {
        printf("UP\n");
        //		lookat[2] += 2.0f;
        //		lookat[0] += 2.0f;
        lookat[2] -= 0.5f;
    }
    else if (key == GLUT_KEY_DOWN)
    {
        printf("DW\n");
        //		lookat[2] -= 2.0f;
        //		lookat[0] -= 2.0f;
        lookat[2] += 0.5f;
    }

    return;
}
//----------------------------------------------------------------------------------

//----------------------------------------------------------------------------------
//设置窗口大小
const int windowHeightbf=300;
const int windowWidgebf=250;

//点类
struct Point{
	int x, y;
	Point():x(0), y(0){}
	Point(int px, int py){
		x = px;
		y = py;
	}
};

//边类
struct Edge{
	float x;
	float dx;
	int yMax;
	Edge(){
		x = 0;
		dx = 0;
		yMax = 0;
	}
	Edge(float ex, float edx, int eyMax){
		x = ex;
		dx = edx;
		yMax = eyMax;
	}

};

//sort的cmp函数
bool cmp_x(Point p1, Point p2){		//x升序排列
	return p1.x<p2.x;
}
bool cmp_y(Point p1, Point p2){
	return p1.y<p2.y;
}

using namespace std;

//扫描划线填充 
void boundaryFill(vector <Point> points){
	//获取y坐标值最大和最小值 
	int yMin = points[0].y, yMax = points[0].x;
	for(int i=1; i<points.size(); ++i){
		if(yMin > points[i].y)
			yMin = points[i].y;
		if(yMax < points[i].y)
			yMax = points[i].y;
	}

	//建立边表edgeTable
	list<Edge> edgeTable[windowHeight];
	for(int i=0;i<points.size();++i){
		int x0 = points[i].x;
		int y0 = points[i].y;
		int x1 = points[(i+1)%points.size()].x;
		int y1 = points[(i+1)%points.size()].y;

		//舍弃与扫描线水平的线
		if(y0==y1)
			continue;
		
		//edgeTable边的各个参数
		int yMinTmp = min(y0,y1);
		int yMaxTmp = max(y0,y1);
		float x=y0<y1?x0:x1;
		float dx=(x0-x1)*1.0/(y0-y1);

		edgeTable[yMinTmp].push_back (Edge(x,dx,yMaxTmp));
	}

	//建立活动边表activeEdgeTable
	list<Edge> activeEdgeTable;
	//头结点
	activeEdgeTable.push_back (Edge());
	//建立活动边表 
	for(int i=yMin;i<yMax;++i){
		//按递增顺序建立活动边表 
		for(auto j=edgeTable[i].begin(); j!=edgeTable[i].end ();){
			auto tmp=activeEdgeTable.begin ();
			auto end=activeEdgeTable.end ();
			for(; tmp!=end; ++tmp){
				if(tmp->x > j->x){
					break;
				}
				if(j->x == tmp->x && j->dx < tmp->dx){
					break;
				}
			}
			activeEdgeTable.insert (tmp,*j);
			j=edgeTable[i].erase (j);
		}

		//删除当前活动边表中y最大的边
		for(auto tmp2=activeEdgeTable.begin (); tmp2!=activeEdgeTable.end ();){
			if(tmp2->yMax==i){
				tmp2=activeEdgeTable.erase (tmp2);
			}else{
				tmp2++;
			}
		}

		//填色
		//一次选取两个点组成填色区间
		auto tmp3 = activeEdgeTable.begin ();
		tmp3++;	//跳过头结点
		auto tmp3_next=tmp3;
		tmp3_next++;
		int count=activeEdgeTable.size ()-1;
		while(count>=2){
			for(int x=tmp3->x; x<tmp3_next->x; ++x){
				setPixel (x,i);
			}
			tmp3++;
			tmp3++;
			tmp3_next=tmp3;
			tmp3_next++;
			count-=2;
		}

		//更新activeEdgeTable中x的值
		for(auto &tmp:activeEdgeTable){
			tmp.x+=tmp.dx;
		}
	}
	return ;
}

//绘制程序
void displaybf(){
	vector <Point> pointList1;
	pointList1.push_back (Point(100,200));
	pointList1.push_back (Point(100,250));
	pointList1.push_back (Point(150,250));
	pointList1.push_back (Point(150,200));
	pointList1.push_back (Point(200,200));
	pointList1.push_back (Point(200,150));
	pointList1.push_back (Point(150,150));
	pointList1.push_back (Point(150,50));
	pointList1.push_back (Point(100,50));
	pointList1.push_back (Point(100,150));
	pointList1.push_back (Point(50,150));
	pointList1.push_back (Point(50,200));
	
	glClear(GL_COLOR_BUFFER_BIT);//将屏幕设置为白色
	glColor3f(1.0,0.0,0.0);//设置当前颜色状态为绿色

	boundaryFill(pointList1);
	glFlush();//交换缓冲区
	return ;
} 

//初始化绘制
void initbf(){
	glClearColor(1.0,1.0,1.0,0.0);//清除颜色设置
	glMatrixMode(GL_PROJECTION);//设置投影方式
	gluOrtho2D (0.0,windowWidgebf*1.0,0.0,windowHeightbf*1.0);
	return ;
}
//----------------------------------------------------------------------------------

//----------------------------------------------------------------------------------
//菜单

//操作界面
void draw()
{
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(0, 1, 0);
    glOrtho(-1, 1, -1, 1, -1, 1);
    glutSwapBuffers();
}

//点击某个条目时，输出该条目属于哪个菜单
void getcurrentmenu()
{
    int nmenu;
    nmenu = glutGetMenu();
    if (nmenu == menu)
        printf("请选择.\n");
}

//第一个子菜单	几何建模功能
void submenufunc1(int data)
{
    getcurrentmenu();
    switch (data)
    {
    case 1:
        printf("DDA画线.\n");
        setNewWindow();
        glutCreateWindow("line_DDA"); //设置窗口标题
        init();
        glutDisplayFunc(displayLineDDA);
        glutMainLoop();
        break;
    case 2:
        printf("中点画线.\n");
        setNewWindow();
        glutCreateWindow("line_Midpoint"); //设置窗口标题
        init();
        glutDisplayFunc(displayLineMidpoint);
        glutMainLoop();
        break;
    case 3:
        printf("Bresenham画线.\n");
        setNewWindow();
        glutCreateWindow("line_Bresenham"); //设置窗口标题
        init();
        glutDisplayFunc(displayLineBres);
        glutMainLoop();
        break;
    case 4:
        printf("中点画圆.\n");
        setNewWindow();
        glutCreateWindow("circle_Midpoint"); //设置窗口标题
        init();
        glutDisplayFunc(displayCircleMidpoint);
        glutMainLoop();
        break;
    case 5:
        printf("B样条曲线.\n");
        //初始化并显示到屏幕中央
        glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
        glutInitWindowPosition(600, 100); //指定窗口位置
        glutInitWindowSize(600, 600);     //指定窗口大小
        glutCreateWindow("鼠标单机画点，多个点自动拟合曲线");
        glClearColor(1, 1, 1, 0);
        glShadeModel(GL_FLAT);
        glutDisplayFunc(display3B);
        glutReshapeFunc(Reshape3B);
        glutMouseFunc(mouse3B);
        glutKeyboardFunc(keyboard3B);
        glutMainLoop();
        break;
    case 6:
        printf("Liang-Barsky 线段裁剪算法.\n");
        glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);   //设置显示模式为单缓冲，RGB模式
        glutInitWindowPosition(600, 100);              //设置窗口位置
        glutInitWindowSize(windowWidge, windowHeight); //设置窗口大小
        glutCreateWindow("Liang-Barsky 线段裁剪算法"); //设置窗口标题
        init16();
        glutDisplayFunc(display16);
        glutMainLoop();
        break;
    case 7:
        printf("Sutherland-Hodgman多边形裁剪算法.\n");
        glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);          //设置显示模式为单缓冲，RGB模式
        glutInitWindowPosition(600, 100);                     //设置窗口位置
        glutInitWindowSize(windowWidge, windowHeight);        //设置窗口大小
        glutCreateWindow("Sutherland-Hodgman多边形裁剪算法"); //设置窗口标题
        init17();
        glutDisplayFunc(display17);
        glutMainLoop();
        break;
    case 8:
        printf("多边形扫描填充算法.\n");
        glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);          //设置显示模式为单缓冲，RGB模式
        glutInitWindowPosition(600, 100);                     //设置窗口位置
        glutInitWindowSize(windowWidgebf, windowHeightbf);        //设置窗口大小
        glutCreateWindow("多边形扫描线填充算法");//设置窗口标题
		initbf();
		glutDisplayFunc(displaybf);
        glutMainLoop();
        break;    
    }
}

//第二个子菜单	几何变换功能
void submenufunc2(int data)
{
    getcurrentmenu();
    switch (data)
    {
    case 1:
        printf("时钟.\n");
        setNewWindow();
        glutInitWindowSize(600, 600); //设置窗口的宽高
        glutCreateWindow("时钟");
        gluOrtho2D(0, 600.0, 0.0, 600.0); //设置坐标系
        initClock();                      //初始化
        glutDisplayFunc(displayClock);
        glutTimerFunc(1000, timerFunc, 1); //每一秒执行一次
        glutMainLoop();
        break;
    case 2:
        printf("小球移动缩放.\n");
        setNewWindow();
        glutCreateWindow("小球移动缩放");
        Init22();
        glutDisplayFunc(&Display22);
        glutReshapeFunc(&Reshape22);
        glutIdleFunc(&myIdle22);
        glutMainLoop();
        break;
    }
}

//第三个子菜单	光源、材质和纹理映射功能
void submenufunc3(int data)
{
    getcurrentmenu();
    switch (data)
    {
    case 1:
        printf("单光源.\n");
        setNewWindow();
        glutCreateWindow("单光源");
        Initsinglelight();
        glutDisplayFunc(&Display22);
        glutReshapeFunc(&Reshape22);
        glutIdleFunc(&myIdle22);
        glutMainLoop();
        break;
    case 2:
        printf("多光源叠加.\n");
        setNewWindow();
        glutCreateWindow("多光源叠加");
        Init22();
        glutDisplayFunc(&Display22);
        glutReshapeFunc(&Reshape22);
        glutIdleFunc(&myIdle22);
        glutMainLoop();
        break;
    case 3:
        printf("纹理映射.\n");
        glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
        glutInitWindowPosition(600, 100); //设置窗口位置
        glutInitWindowSize(400, 400);
        glutCreateWindow("纹理映射");
        initRendering();
        glutDisplayFunc(drawScene);
        glutKeyboardFunc(handleKeypress);
        glutReshapeFunc(handleResize32);
        glutMainLoop();
        break;
    }
}

//第四个子菜单	可视化功能
void submenufunc4(int data)
{
    getcurrentmenu();
    switch (data)
    {
    case 1:
        printf("天空盒+几何模型+视点变换+坐标变换+纹理映射（立方体+球体）.\n");
        glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); //设置显示模式为单缓冲，RGB模式
        //设置窗口位置
        glutInitWindowPosition(600, 100);
        //设置窗口大小
        glutInitWindowSize(windowWidge, windowHeight);
        //设置窗口标题
        glutCreateWindow("上下控制移动，wasd控制方向");
        //初始化glut并绘制画面:
        init41();
        glutDisplayFunc(display);
        //注册键盘响应函数
        glutKeyboardFunc(keyboradAck);
        glutSpecialFunc(specialKeyAck);
        //空闲时自动调用函数:
        glutIdleFunc(myIdle);
        //窗口尺寸变化函数:
        glutReshapeFunc(handleResize);
        glutMainLoop();
        break;
    }
}

//主菜单
void menufunc(int data)
{
    getcurrentmenu();
    switch (data)
    {
    case 1:
        return;
        break;
    }
}
//----------------------------------------------------------------------------------

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowPosition(0, 100);
    glutInitWindowSize(512, 512);
    glutCreateWindow("需要菜单请在此黑色区域右键！！！！！！弹窗请勿关闭！！！！！！！");
    glutDisplayFunc(draw);

    //构建子菜单1的内容
    submenu1 = glutCreateMenu(submenufunc1);
    glutAddMenuEntry("DDA画线", 1);
    glutAddMenuEntry("中点画线", 2);
    glutAddMenuEntry("Bresenham画线", 3);
    glutAddMenuEntry("中点画圆", 4);
    glutAddMenuEntry("B样条画曲线", 5);
    glutAddMenuEntry("Liang-Barsky 线段裁剪算法", 6);
    glutAddMenuEntry("Sutherland-Hodgman多边形裁剪算法", 7);
    glutAddMenuEntry("多边形扫描线填充算法", 8);

    //构建子菜单2的内容
    submenu2 = glutCreateMenu(submenufunc2);
    glutAddMenuEntry("时钟", 1);
    glutAddMenuEntry("小球移动缩放", 2);

    //构建子菜单3的内容
    submenu3 = glutCreateMenu(submenufunc3);
    glutAddMenuEntry("单光源", 1);
    glutAddMenuEntry("多光源叠加", 2);
    glutAddMenuEntry("纹理映射", 3);

    //构建子菜单4的内容
    submenu4 = glutCreateMenu(submenufunc4);
    glutAddMenuEntry("天空盒+几何模型+视点变换+坐标变换+纹理映射（立方体+球体）", 1);

    //构建主菜单的内容
    menu = glutCreateMenu(menufunc);
    glutAddMenuEntry("请选择-注意：弹窗请勿关闭", 1);

    //将两个菜单变为另一个菜单的子菜单
    glutAddSubMenu("几何建模功能", submenu1);
    glutAddSubMenu("几何变换功能", submenu2);
    glutAddSubMenu("光源、材质和纹理映射功能", submenu3);
    glutAddSubMenu("可视化功能", submenu4);
    //点击鼠标右键时显示菜单
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutMainLoop();
    return 0;
}

