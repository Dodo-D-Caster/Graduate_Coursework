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

//���ڴ�С
const int windowWidge = 600, windowHeight = 600;

//���ô���
void setNewWindow()
{
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); //������ʾģʽ�������壬RGBģʽ
    glutInitWindowPosition(600, 100);            //���ô���λ��
    glutInitWindowSize(400, 300);                //���ô��ڴ�С
}

//��ʼ������
void init()
{
    glClearColor(1.0, 1.0, 1.0, 0.0);   //�����ɫ����
    glMatrixMode(GL_PROJECTION);        //����ͶӰ��ʽ
    gluOrtho2D(0.0, 200.0, 0.0, 150.0); //���û�����С
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

//����ֱ��
void displayLineDDA()
{
    glClear(GL_COLOR_BUFFER_BIT); //�����ɫ
    glColor3f(0.0, 0.4, 0.2);     //���õ�ǰ��ɫΪ��ɫ
    lineDDA(0, 0, 180, 180);
    glFlush(); //���ͻ�����
}
//----------------------------------------------------------------------------------

//----------------------------------------------------------------------------------
//�е㻭��
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

//����ֱ��
void displayLineMidpoint()
{
    glClear(GL_COLOR_BUFFER_BIT); //�����ɫ
    glColor3f(0.0, 0.4, 0.2);     //���õ�ǰ��ɫΪ��ɫ
    lineMidp(0, 0, 180, 180);
    glFlush(); //���ͻ�����
}
//----------------------------------------------------------------------------------

//----------------------------------------------------------------------------------
//Bresenham����

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

//����ֱ��
void displayLineBres()
{
    glClear(GL_COLOR_BUFFER_BIT); //�����ɫ
    glColor3f(0.0, 0.4, 0.2);     //���õ�ǰ��ɫΪ��ɫ
    lineBres(0, 0, 180, 180);
    glFlush(); //���ͻ�����
}
//----------------------------------------------------------------------------------

//----------------------------------------------------------------------------------
//�е㻭Բ
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

//����Բ
void displayCircleMidpoint()
{
    glClear(GL_COLOR_BUFFER_BIT); //�����ɫ
    glColor3f(0.0, 0.4, 0.2);     //���õ�ǰ��ɫΪ��ɫ
    circleMidp(100, 100, 50);
    glFlush(); //���ͻ�����
}
//----------------------------------------------------------------------------------

//----------------------------------------------------------------------------------
//B��������
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
    double precision = 200; //��ȷ��
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
    glClear(GL_COLOR_BUFFER_BIT); //�����ɫ�������Ȼ���

    //����
    glPointSize(5);
    glColor3d(1, 0, 0);
    glBegin(GL_POINTS);
    for (int i = 0; i < p.size(); i++)
        glVertex2d(p[i].x, p[i].y);
    glEnd();

    //����
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
    { //�˸��
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

//�������������ڱ��ƶ����С
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
//ʱ��
//��ǰʱ�䣬ʱ �� ��
float h = 0.0f;
float m = 0.0f;
float s = 0.0f;

//��ʱ�ӵĺ���
void displayClock(void)
{
    int Width = 600;
    int Height = 600;

    GLfloat PI = 3.1415926f;

    //�õ�ǰ���ɫ�����ɫ�����������趨���ڵı���ɫ
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.1f, 0.2f, 0.1f); //������ɫ

    //������
    int cx = Width / 2; //���ĵ�
    int cy = Height / 2;
    int R = 100; // �뾶��
    int n = 100;
    int i;
    circleMidp(cx, cy, R); //�е㻭Բ��

    //���ƿ̶�
    int lines = 60;
    for (i = 0; i < lines; i++)
    {
        //5�ı����Ŀ̶� �ֵ�
        if (i % 5 == 0)
        {
            glLineWidth(3);
            glBegin(GL_LINES);
            glVertex2f(cx + (R - 10) * sin(2 * PI / lines * i), cy + (R - 10) * cos(2 * PI / lines * i));
            glVertex2f(cx + R * sin(2 * PI / lines * i), cy + R * cos(2 * PI / lines * i));
        }
        else
        {
            glLineWidth(2); //����̶�
            glBegin(GL_LINES);
            glVertex2f(cx + (R - 5) * sin(2 * PI / lines * i), cy + (R - 5) * cos(2 * PI / lines * i));
            glVertex2f(cx + R * sin(2 * PI / lines * i), cy + R * cos(2 * PI / lines * i));
        }
    }

    //����ʱ �� ����
    int h_len = 60;  //ʱ�볤��
    int m_len = 80;  //���볤��
    int s_len = 100; //���볤��
    float s_Angle = s / 60.0;
    float m_Angle = (m * 60 + s) / 3600.0;
    float h2 = h >= 12 ? (h - 12) : h;
    float h_Angle = (h2 * 60 * 60 + m * 60 + s) / (12 * 60 * 60);

    //ʱ
    glLineWidth(3); //ʱ����
    glBegin(GL_LINES);
    glVertex2f(cx, cy);
    glVertex2f(cx + h_len * sin(2 * PI * h_Angle), cy + h_len * cos(2 * PI * h_Angle));
    glEnd();

    //��
    glLineWidth(2); //������
    glBegin(GL_LINES);
    glVertex2f(cx, cy);
    glVertex2f(cx + m_len * sin(2 * PI * m_Angle), cy + m_len * cos(2 * PI * m_Angle));
    glEnd();

    //��
    glLineWidth(1); //������
    glBegin(GL_LINES);
    glVertex2f(cx - 2 * 5 * sin(2 * PI * s_Angle), cy - 2 * 5 * cos(2 * PI * s_Angle));
    glVertex2f(cx + (R - 10) * sin(2 * PI * s_Angle), cy + (R - 10) * cos(2 * PI * s_Angle));
    glEnd();

    //ˢ��
    glFlush();
}

//�ص���������϶�ʱ��ʹ��
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

    glutPostRedisplay();               //�ػ�
    glutTimerFunc(1000, timerFunc, 1); //ÿһ��ִ��һ��
}

//��ʼ�������ñ�������ȡʱ��
void initClock(void)
{
    // ���ô���Ϊ��ɫ
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    // ��ȡ���ص�ǰʱ��
    SYSTEMTIME sys;
    GetLocalTime(&sys);
    h = sys.wHour;
    m = sys.wMinute;
    s = sys.wSecond;
}
//----------------------------------------------------------------------------------

//----------------------------------------------------------------------------------
//С���ƶ�����
float angle22 = 0.0f;

void Init22()
{
    GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat mat_shininess[] = {50.0};

    //���ù�Դλ��
    GLfloat light_position[] = {-10.0, 1.0, 20.0, 0.0};
    GLfloat light_position2[] = {1.0, 1.0, 1.0, 0.0};
    GLfloat light_position3[] = {1.0, 10.0, 1.0, 0.0};

    //������
    GLfloat lmodel_ambient[] = {0.1, 0.1, 0.1, 1.0};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);

    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_SMOOTH);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);   //ָ����������
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess); //���淴��ָ��

    //����light0--white
    GLfloat white_light[] = {1.0, 1.0, 1.0, 1.0};      //���ñ�š����ԡ���ɫ
    glLightfv(GL_LIGHT0, GL_POSITION, light_position); //����λ��
    glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, white_light);
    glEnable(GL_LIGHT0);

    //����light1--red
    GLfloat red_light[] = {1.0, 0.0, 0.0, 1.0};
    glLightfv(GL_LIGHT1, GL_POSITION, light_position);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, red_light);
    glLightfv(GL_LIGHT1, GL_SPECULAR, red_light);
    glEnable(GL_LIGHT1);

    //����light2--green
    GLfloat green_light[] = {0.0, 1.0, 0.0, 1.0};
    glLightfv(GL_LIGHT2, GL_POSITION, light_position2);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, green_light);
    glLightfv(GL_LIGHT2, GL_SPECULAR, green_light);
    glEnable(GL_LIGHT2);

    //����light3--blue
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
    glRotatef(angle22, 0.0f, 0.0f, 0.0f); //�Ƕ�+��ת��
    glTranslatef(1.0f, 0.0f, 0.0f);       //�ƶ�
    glutSolidSphere(1.0, 100, 50);        //�뾶Ϊ1, 100��γ��, 50������
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
    //ʹ���ؾ���ռ�������´���
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    //�õ�ǰ����ΪͶӰ����
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //�ı䴰�ڴ�С��ͼ����״���ֲ���
    if (w <= h)
    {
        glOrtho(-1.5, 1.5, -1.5 * (GLfloat)h / (GLfloat)w, 1.5 * (GLfloat)h / (GLfloat)w, -10.0, 10.0);
    }
    else
    {
        glOrtho(-1.5 * (GLfloat)w / (GLfloat)h, 1.5 * (GLfloat)w / (GLfloat)h, -1.5, 1.5, -10.0, 10.0);
    }

    //ģ�;���
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
//----------------------------------------------------------------------------------

//----------------------------------------------------------------------------------
//Liang-Barsky �߶βü��㷨
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
    //���ӻ��߽�:
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

//��ʼ������
void init16()
{
    glClearColor(1.0, 1.0, 1.0, 0.0); //�����ɫ����
    glMatrixMode(GL_PROJECTION);      //����ͶӰ��ʽ
    gluOrtho2D(0.0, windowWidge * 1.0, 0.0, windowHeight * 1.0);
    return;
}
//----------------------------------------------------------------------------------

//----------------------------------------------------------------------------------
//Sutherland-Hodgman����βü��㷨
const int Left = 0, Right = 1, Bottom = 2, Top = 3; //�������� �ֱ�ü�
const GLint nClip = 4;                              //�߽����

//�жϵ���߽��λ�ù�ϵ
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

//�ж��Ƿ��ཻ
GLint cross(wcPt2D p1, wcPt2D p2, int winEdge, wcPt2D wMin, wcPt2D wMax)
{
    if (inside(p1, winEdge, wMin, wMax) == inside(p2, winEdge, wMin, wMax))
        return false;
    else
        return true;
}

//���ؽ���
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

//�ü���
void clipPoint(wcPt2D p, int winEdge, wcPt2D wMin, wcPt2D wMax, wcPt2D *pOut, int *cnt, wcPt2D first[], wcPt2D *s)
{
    wcPt2D iPt;

    //�޽����򱣴�
    if (first[winEdge].x == 0 && first[winEdge].y == 0)
    {
        first[winEdge] = p;
    }
    else
    {
        //�н������ҵ����㲢����
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

    //������ڱ��ڣ�����һ����
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

//����βü�
GLint polygonClipSuthHodg(wcPt2D wMin, wcPt2D wMax, GLint n, wcPt2D *pIn, wcPt2D *pOut)
{
    wcPt2D first[nClip], s[nClip];
    GLint k, cnt = 0;
    for (k = 0; k < n; k++)
        clipPoint(pIn[k], Left, wMin, wMax, pOut, &cnt, first, s);
    closeClip(wMin, wMax, pOut, &cnt, first, s);
    return cnt;
}

//���Ƴ���
void display17()
{
    glClear(GL_COLOR_BUFFER_BIT); //����Ļ����Ϊ��ɫ

    //Sutherland-Hodgman����βü��㷨
    glClear(GL_COLOR_BUFFER_BIT);

    //�ü�����
    const int minX = 100, minY = 100, maxX = 300, maxY = 300;
    glColor3f(1.0, 0.0, 0.0);
    lineDDA(minX, minY, minX, maxY);
    lineDDA(minX, minY, maxX, minY);
    lineDDA(maxX, maxY, minX, maxY);
    lineDDA(maxX, maxY, maxX, minY);

    //�����
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

//��ʼ������
void init17()
{
    glClearColor(1.0, 1.0, 1.0, 0.0); //�����ɫ����
    glMatrixMode(GL_PROJECTION);      //����ͶӰ��ʽ
    gluOrtho2D(0.0, windowWidge * 1.0, 0.0, windowHeight * 1.0);
    return;
}
//----------------------------------------------------------------------------------

//----------------------------------------------------------------------------------
//����ӳ��
//ʹ��stb_image����֧�ֵ�ͼƬ��ʽ����
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

//image�ഢ����ص��ڴ��е�ͼƬ
struct Image
{
    int width = 0;
    int height = 0;
    int nrChannels = 0;
    unsigned char *data = nullptr;
};

//ͼƬ���غ���
/**
 * @brief loadImage	��ͼƬ���ص��ڴ�
 * @param fileName	ͼƬ�ļ���(���·��)
 * @return
 */
Image *loadImage(const char *fileName)
{
    Image *image = new Image();
    //��תͼ��, ����ͼ���Ƿ���
    stbi_set_flip_vertically_on_load(true);
    image->data = stbi_load(fileName, &image->width, &image->height,
                            &image->nrChannels, 0);
    return image;
}

//������غ���
/**
 * @brief loadTexture ��ͼƬ����Ϊ����
 * @param image	�Ѿ����ص��ڴ��е�ͼƬ
 * @return
 */
GLuint loadTexture(Image *image)
{
    GLuint textureId;
    //�����ʼ��
    glGenTextures(1, &textureId);
    //ѡ����ǰҪ�༭������
    glBindTexture(GL_TEXTURE_2D, textureId);

    if (image->nrChannels == 3)
    {
        glTexImage2D(GL_TEXTURE_2D,               //��ά������Զ��GL_TEXTURE_2D
                     0,                           //����������0
                     GL_RGB,                      //�������ʽ
                     image->width, image->height, //ͼ����
                     0,                           //��Զ��0
                     GL_RGB,                      //�������ݸ�ʽ, ��������ͷ��ͬ
                     GL_UNSIGNED_BYTE,            //������������, ������GL_UNSIGNED_BYTE
                     image->data);                //ͼƬdata����ָ��
    }
    else
    {
        //�����PNGͼ�����alphaͨ��, ��RGBA
        glTexImage2D(GL_TEXTURE_2D,               //��ά������Զ��GL_TEXTURE_2D
                     0,                           //����������0
                     GL_RGBA,                     //�������ʽ
                     image->width, image->height, //ͼ����
                     0,                           //��Զ��0
                     GL_RGBA,                     //�������ݸ�ʽ, ��������ͷ��ͬ
                     GL_UNSIGNED_BYTE,            //������������, ������GL_UNSIGNED_BYTE
                     image->data);                //ͼƬdata����ָ��
    }
    return textureId; //���ؼ��ص�����ID
}

GLuint _textureId; //The id of the texture

void initRendering()
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);

    //���������õ�ͼƬ
    //֧�־������������ʽ
    //ע��ͼ��ֱ��ʲ�Ҫ̫��(��ѧ����), �����������
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

    //�ײ�ͼ��
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glColor3f(0.2f, 0.2f, 0.2f); //������ɫ
    glBegin(GL_QUADS);

    glNormal3f(0.0, 1.0f, 0.0f);    //������
    glTexCoord2f(0.0f, 0.0f);       //����ӳ��
    glVertex3f(-2.5f, -2.5f, 2.5f); //��ͼ
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(2.5f, -2.5f, 2.5f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(2.5f, -2.5f, -2.5f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-2.5f, -2.5f, -2.5f);

    glEnd();

    //�м��������
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
//����Դ
void Initsinglelight()
{
    GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat mat_shininess[] = {50.0};

    //���ù�Դλ��
    GLfloat light_position[] = {-10.0, 1.0, 20.0, 0.0};
    GLfloat light_position2[] = {1.0, 1.0, 1.0, 0.0};
    GLfloat light_position3[] = {1.0, 10.0, 1.0, 0.0};

    //������
    GLfloat lmodel_ambient[] = {0.1, 0.1, 0.1, 1.0};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);

    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_SMOOTH);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);   //ָ����������
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess); //���淴��ָ��

    //����light0--white
    GLfloat white_light[] = {1.0, 1.0, 1.0, 1.0};      //���ñ�š����ԡ���ɫ
    glLightfv(GL_LIGHT0, GL_POSITION, light_position); //����λ��
    glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, white_light);
    glEnable(GL_LIGHT0);

    //����light1--red
    GLfloat red_light[] = {1.0, 0.0, 0.0, 1.0};
    glLightfv(GL_LIGHT1, GL_POSITION, light_position);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, red_light);
    glLightfv(GL_LIGHT1, GL_SPECULAR, red_light);
    //	glEnable(GL_LIGHT1);

    //����light2--green
    GLfloat green_light[] = {0.0, 1.0, 0.0, 1.0};
    glLightfv(GL_LIGHT2, GL_POSITION, light_position2);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, green_light);
    glLightfv(GL_LIGHT2, GL_SPECULAR, green_light);
    //	glEnable(GL_LIGHT2);

    //����light3--blue
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
//���ӻ� ��պ�+����ģ��+�ӵ�任+����任

//���߲�����, �������
static GLfloat xequalzero[] = {1.0, 1.0, 1.0, 1.0};
static double lookat[] = {0.0, -5.0, 7.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0};
static double perspective[] = {90.0, 1.0f, 1.0f, 50.0f};
static GLfloat *currentCoeff;
static GLenum currentPlane;
static GLint currentGenMode;
static float roangles;

const int MAX = 20;       //�����������
int textureId[MAX] = {0}; //����ID:

//��ʼ������
void init41()
{
    glClearColor(0.0, 0.0, 0.0, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //������ɫ����Ȼ���

    //����͸��Ч����ͼ
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(perspective[0], perspective[1],
                   perspective[2], perspective[3]);

    //�����ӵ�:
    //ͷ��������
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(lookat[0], lookat[1], lookat[2],
              lookat[3], lookat[4], lookat[5],
              lookat[6], lookat[7], lookat[8]);

    //������Ȳ���:
    //�ڻ���3D����ʱ��Ҫ, �����޷��ж�������ϵ
    glEnable(GL_DEPTH_TEST);

    //����Ĭ�Ϲ�Դ:
    {
        //��Դλ��, Ĭ����z����ϵ��µĹ�
        GLfloat sun_light_position[] = {0.0f, 0.0f, 30.0f, 1.0f}; //��Դ��λ������������ϵԲ�ģ����������ʽ
        //RGBAģʽ�Ļ�����
        GLfloat sun_light_ambient[] = {0.1f, 0.1f, 0.1f, 1.0f};
        //RGBAģʽ��������⣬ȫ�׹�
        GLfloat sun_light_diffuse[] = {1.0f, 1.0, 1.0, 1.0f};
        //RGBAģʽ�µľ���� ��ȫ�׹�
        GLfloat sun_light_specular[] = {1.0f, 1.0, 1.0, 1.0f};
        //Ӧ�ù���:
        glLightfv(GL_LIGHT0, GL_POSITION, sun_light_position);
        glLightfv(GL_LIGHT0, GL_AMBIENT, sun_light_ambient);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, sun_light_diffuse);
        glLightfv(GL_LIGHT0, GL_SPECULAR, sun_light_specular);

        //�����ƹ�
        glEnable(GL_LIGHT0);
        glEnable(GL_LIGHTING);
    }

    //�����������Զ�����
    glEnable(GL_NORMALIZE);

    //��������&��ɫ����
    glEnable(GL_COLOR_MATERIAL);

    //���������õ�ͼƬ
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

//x,y,z����ת�Ƕȷ���
GLfloat xtri = 0;
GLfloat ytri = 0;
GLfloat ztri = 0;
GLfloat xtri2 = 0;

//ȫ��������ת����:
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

//��ʾ���ú���
void display()
{
    //�����ǰ��ɫ&��Ȼ���
    glClearColor(0.0, 0.0, 0.0, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //��display�и����ӵ�:
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //��һ��eyex, eyey,eyez ��������������λ��
    //�ڶ���centerx,centery,centerz �����ͷ��׼�����������������λ��
    //������upx,upy,upz ������ϵķ��������������еķ���
    gluLookAt(lookat[0], lookat[1], lookat[2],
              lookat[3], lookat[4], lookat[5],
              lookat[6], lookat[7], lookat[8]);

    //������ת, ʵ�������ƽ�����ת
    //���������������������
    glRotatef(xrotate, 1, 0, 0);
    glRotatef(yrotate, 0, 1, 0);
    glRotatef(zrotate, 0, 0, 1);

    //	�������:
    {
        //���ǿ���glEnable(GL_COLOR_MATERIAL)֮�����ò�����ɫ�ķ���:
        //����ʹ��glColor4f ���� glColor3f ����main�е����ö���
        glColorMaterial(GL_FRONT, GL_AMBIENT);
        glColor4f(0.0f, 0.0f, 1.0f, 1.0f);

        glColorMaterial(GL_FRONT, GL_DIFFUSE);
        glColor4f(0.0f, 0.0f, 1.0f, 1.0f);

        glColorMaterial(GL_FRONT, GL_SPECULAR);
        glColor4f(1.0f, 1.0, 1.0, 1.0f);

        glColorMaterial(GL_FRONT, GL_EMISSION);
        glColor4f(0.0f, 0.0f, 0.0f, 1.0f);

        //��ͷֻ������4������
        //���ʵľ���ָ����Ȼ��Ҫʹ��glMaterialf����
        GLfloat mat_shininess = 32.0f;
        glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);

        //����������ά���α任 (���������)
        //ʹ��ȫ�ֱ���, ������Idle���޸�
        glPushMatrix();
        ////		glRotatef(ztri,0.0f,0.0f,1.0f);                // ��Z����ת
        ////		glTranslatef (2.0,0.0,0.0);
        //
        //		//��һ��������
        ////		glutSolidCube (2);
        //		//glRotatef(xtri,1.0f,0.0f,0.0f);        // ��X����ת
        //
        //		glRotatef(ytri,0.0f,1.0f,0.0f);          // ��Y����ת
        //		glTranslated (3.0,0.0,0.0);
        //		glColor3f(1.0,0.0,0.0);	//������ɫ
        //		glBindTexture(GL_TEXTURE_2D,textureId[0]);
        //		//��һ����
        //		glutSolidSphere (0.5,20,20);
        //
        //		glRotatef(ytri,0.0f,1.0f,0.0f);          // ��Y����ת
        //		glTranslated (5.0,0.0,0.0);
        //		glColor3f(1.0,0.0,0.0);	//������ɫ
        //		//��һ����
        //		glutSolidSphere (0.5,20,20);
        //
        //		glRotatef(ytri,0.0f,1.0f,0.0f);          // ��Y����ת
        //		glTranslated (7.0,0.0,0.0);
        //		glColor3f(1.0,0.0,0.0);	//������ɫ
        //		//��һ����
        //		glutSolidSphere (0.5,20,20);
        //
        //
        //		glRotatef(ytri,0.0f,1.0f,0.0f);                // ��Y����ת
        //		glTranslated (3.0,0.0,0.0);
        //		glColor3f(0.0,1.0,0.0);	//������ɫ
        //		glutSolidCube (2);

        glPopMatrix();
    }

    //�����ͼ
    GLfloat len = 20.0f;
    GLfloat _len = -20.0f;

    //ǰ��
    glEnable(GL_TEXTURE_2D);
    {
        //���õ�ǰ����������
        glBindTexture(GL_TEXTURE_2D, textureId[0]);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        //��ɫ����Ϊ��ɫ, ������ԭɫ�ʲ���
        glColor3f(1.0f, 1.0f, 1.0f);
        //�����ı���
        glBegin(GL_QUADS);
        {
            //ȷ������ƽ�淨����
            glNormal3f(0.0, 1.0f, 0.0f);
            //����ӳ��, 0~1, ����������ƽ��
            glTexCoord2f(0.0f, 0.0f);
            glVertex3f(_len, _len, len); // ������ı��ε�����
            glTexCoord2f(1.0f, 0.0f);
            glVertex3f(len, _len, len); // ������ı��ε�����
            glTexCoord2f(1.0f, 1.0f);
            glVertex3f(len, len, len); // ������ı��ε�����
            glTexCoord2f(0.0f, 1.0f);
            glVertex3f(_len, len, len); // ������ı��ε�����
        }
        glEnd();
    }
    glDisable(GL_TEXTURE_2D);

    //����
    glEnable(GL_TEXTURE_2D);
    {
        //���õ�ǰ����������
        glBindTexture(GL_TEXTURE_2D, textureId[1]);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        //��ɫ����Ϊ��ɫ, ������ԭɫ�ʲ���
        glColor3f(1.0f, 1.0f, 1.0f);
        //�����ı���
        glBegin(GL_QUADS);
        {
            //ȷ������ƽ�淨����
            glNormal3f(0.0, 1.0f, 0.0f);
            //����ӳ��, 0~1, ����������ƽ��
            glTexCoord2f(1.0f, 0.0f);
            glVertex3f(_len, _len, _len); // ������ı��ε�����
            glTexCoord2f(1.0f, 1.0f);
            glVertex3f(_len, len, _len); // ������ı��ε�����
            glTexCoord2f(0.0f, 1.0f);
            glVertex3f(len, len, _len); // ������ı��ε�����
            glTexCoord2f(0.0f, 0.0f);
            glVertex3f(len, _len, _len); // ������ı��ε�����
        }
        glEnd();
    }
    glDisable(GL_TEXTURE_2D);

    //����
    glEnable(GL_TEXTURE_2D);
    {
        //���õ�ǰ����������
        glBindTexture(GL_TEXTURE_2D, textureId[3]);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        //��ɫ����Ϊ��ɫ, ������ԭɫ�ʲ���
        glColor3f(1.0f, 1.0f, 1.0f);
        //�����ı���
        glBegin(GL_QUADS);
        {
            //ȷ������ƽ�淨����
            glNormal3f(0.0, 1.0f, 0.0f);
            //����ӳ��, 0~1, ����������ƽ��
            glTexCoord2f(1.0f, 0.0f);
            glVertex3f(_len, len, _len); // ������ı��ε�����
            glTexCoord2f(1.0f, 1.0f);
            glVertex3f(_len, len, len); // ������ı��ε�����
            glTexCoord2f(0.0f, 1.0f);
            glVertex3f(len, len, len); // ������ı��ε�����
            glTexCoord2f(0.0f, 0.0f);
            glVertex3f(len, len, -len); // ������ı��ε�����
        }
        glEnd();
    }
    glDisable(GL_TEXTURE_2D);

    //����
    glEnable(GL_TEXTURE_2D);
    {
        //���õ�ǰ����������
        glBindTexture(GL_TEXTURE_2D, textureId[2]);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        //��ɫ����Ϊ��ɫ, ������ԭɫ�ʲ���
        glColor3f(1.0f, 1.0f, 1.0f);
        //�����ı���
        glBegin(GL_QUADS);
        {
            //ȷ������ƽ�淨����
            glNormal3f(0.0, 1.0f, 0.0f);
            //����ӳ��, 0~1, ����������ƽ��
            glTexCoord2f(1.0f, 1.0f);
            glVertex3f(_len, _len, _len); // ������ı��ε�����
            glTexCoord2f(0.0f, 1.0f);
            glVertex3f(len, _len, _len); // ������ı��ε�����
            glTexCoord2f(0.0f, 0.0f);
            glVertex3f(len, _len, len); // ������ı��ε�����
            glTexCoord2f(1.0f, 0.0f);
            glVertex3f(_len, _len, len); // ������ı��ε�����
        }
        glEnd();
    }
    glDisable(GL_TEXTURE_2D);

    //����
    glEnable(GL_TEXTURE_2D);
    {
        //���õ�ǰ����������
        glBindTexture(GL_TEXTURE_2D, textureId[5]);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        //��ɫ����Ϊ��ɫ, ������ԭɫ�ʲ���
        glColor3f(1.0f, 1.0f, 1.0f);
        //�����ı���
        glBegin(GL_QUADS);
        {
            //ȷ������ƽ�淨����
            glNormal3f(0.0, 1.0f, 0.0f);
            //����ӳ��, 0~1, ����������ƽ��
            glTexCoord2f(1.0f, 0.0f);
            glVertex3f(len, _len, _len); // ������ı��ε�����
            glTexCoord2f(1.0f, 1.0f);
            glVertex3f(len, len, _len); // ������ı��ε�����
            glTexCoord2f(0.0f, 1.0f);
            glVertex3f(len, len, len); // ������ı��ε�����
            glTexCoord2f(0.0f, 0.0f);
            glVertex3f(len, _len, len); // ������ı��ε�����
        }
        glEnd();
    }
    glDisable(GL_TEXTURE_2D);

    //����
    glEnable(GL_TEXTURE_2D);
    {
        //���õ�ǰ����������
        glBindTexture(GL_TEXTURE_2D, textureId[4]);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        //��ɫ����Ϊ��ɫ, ������ԭɫ�ʲ���
        glColor3f(1.0f, 1.0f, 1.0f);
        //�����ı���
        glBegin(GL_QUADS);
        {
            //ȷ������ƽ�淨����
            glNormal3f(0.0, 1.0f, 0.0f);
            //����ӳ��, 0~1, ����������ƽ��
            glTexCoord2f(0.0f, 0.0f);
            glVertex3f(_len, _len, _len); // ������ı��ε�����
            glTexCoord2f(1.0f, 0.0f);
            glVertex3f(_len, _len, len); // ������ı��ε�����
            glTexCoord2f(1.0f, 1.0f);
            glVertex3f(_len, len, len); // ������ı��ε�����
            glTexCoord2f(0.0f, 1.0f);
            glVertex3f(_len, len, _len); // ������ı��ε�����
        }
        glEnd();
    }
    glDisable(GL_TEXTURE_2D);

    //	������ͼ
    //	��ͼһ��Ҫ��, ��Ȼ�������������
    //	����2D����
    glEnable(GL_TEXTURE_2D);
    {
        //���õ�ǰ����������
        glBindTexture(GL_TEXTURE_2D, textureId[6]);
        //���û��Ʒ�ʽ
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        //�����������
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        //��ɫ����Ϊ��ɫ, ������ԭɫ�ʲ���
        glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
        currentCoeff = xequalzero;
        currentGenMode = GL_OBJECT_LINEAR;
        currentPlane = GL_OBJECT_PLANE;
        //�Զ�������������, ������Ҫʹ��glTexCoord��ʽ����
        glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, currentGenMode);
        glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, currentGenMode);
        glTexGenfv(GL_S, currentPlane, currentCoeff);
        //�����Զ���������
        //�����ú�ͷ��glTexGen�޷�ʹ��
        glEnable(GL_TEXTURE_GEN_S);
        glEnable(GL_TEXTURE_GEN_T);

        drawBall(3, 0, 0, 0, xtri, 0, 0, 1);
        //�ر��Զ���������
        //��ȻӰ�������ֶ���ͼ
        glDisable(GL_TEXTURE_GEN_S);
        glDisable(GL_TEXTURE_GEN_T);
    }
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    {
        //���õ�ǰ����������
        glBindTexture(GL_TEXTURE_2D, textureId[6]);
        //���û��Ʒ�ʽ
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        //�����������
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        //��ɫ����Ϊ��ɫ, ������ԭɫ�ʲ���
        glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
        currentCoeff = xequalzero;
        currentGenMode = GL_OBJECT_LINEAR;
        currentPlane = GL_OBJECT_PLANE;
        //�Զ�������������, ������Ҫʹ��glTexCoord��ʽ����
        glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, currentGenMode);
        glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, currentGenMode);
        glTexGenfv(GL_S, currentPlane, currentCoeff);
        //�����Զ���������
        //�����ú�ͷ��glTexGen�޷�ʹ��
        glEnable(GL_TEXTURE_GEN_S);
        glEnable(GL_TEXTURE_GEN_T);

        drawBall(3, 5.0, 0, 0, ytri, 0, 1.0f, 0);
        //�ر��Զ���������
        //��ȻӰ�������ֶ���ͼ
        glDisable(GL_TEXTURE_GEN_S);
        glDisable(GL_TEXTURE_GEN_T);
    }
    glDisable(GL_TEXTURE_2D);

    //ˢ�»�����
    glutSwapBuffers();
    return;
}

//���е��ú���
void myIdle(void)
{
    //ִ�л����������

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

    //�����ػ溯��:
    //ͨ����glutPostRedisplay, ���Ϊ����һ��
    glutPostRedisplay();

    //ͨ����Ҫһ��sleep����ֹ֡�ʹ���, ����sleep 16ms, Լ����60fps
    Sleep(16);
    return;
}

//���ڳߴ����ú���:
//�����ڴ�С�仯ʱ����, ��֤ͼ�β�����
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

//������Ӧ����:
void keyboradAck(unsigned char key, int x, int y)
{
    printf("%d=%c, x=%d, y=%d\n", key, key, x, y);
    static double flag = 1.0;

    switch (key)
    {
        //�����ӽ��Ե�ǰ�ӵ�Ϊ������ת
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
    //����ǰ������
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
//���ô��ڴ�С
const int windowHeightbf=300;
const int windowWidgebf=250;

//����
struct Point{
	int x, y;
	Point():x(0), y(0){}
	Point(int px, int py){
		x = px;
		y = py;
	}
};

//����
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

//sort��cmp����
bool cmp_x(Point p1, Point p2){		//x��������
	return p1.x<p2.x;
}
bool cmp_y(Point p1, Point p2){
	return p1.y<p2.y;
}

using namespace std;

//ɨ�軮����� 
void boundaryFill(vector <Point> points){
	//��ȡy����ֵ������Сֵ 
	int yMin = points[0].y, yMax = points[0].x;
	for(int i=1; i<points.size(); ++i){
		if(yMin > points[i].y)
			yMin = points[i].y;
		if(yMax < points[i].y)
			yMax = points[i].y;
	}

	//�����߱�edgeTable
	list<Edge> edgeTable[windowHeight];
	for(int i=0;i<points.size();++i){
		int x0 = points[i].x;
		int y0 = points[i].y;
		int x1 = points[(i+1)%points.size()].x;
		int y1 = points[(i+1)%points.size()].y;

		//������ɨ����ˮƽ����
		if(y0==y1)
			continue;
		
		//edgeTable�ߵĸ�������
		int yMinTmp = min(y0,y1);
		int yMaxTmp = max(y0,y1);
		float x=y0<y1?x0:x1;
		float dx=(x0-x1)*1.0/(y0-y1);

		edgeTable[yMinTmp].push_back (Edge(x,dx,yMaxTmp));
	}

	//������߱�activeEdgeTable
	list<Edge> activeEdgeTable;
	//ͷ���
	activeEdgeTable.push_back (Edge());
	//������߱� 
	for(int i=yMin;i<yMax;++i){
		//������˳������߱� 
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

		//ɾ����ǰ��߱���y���ı�
		for(auto tmp2=activeEdgeTable.begin (); tmp2!=activeEdgeTable.end ();){
			if(tmp2->yMax==i){
				tmp2=activeEdgeTable.erase (tmp2);
			}else{
				tmp2++;
			}
		}

		//��ɫ
		//һ��ѡȡ�����������ɫ����
		auto tmp3 = activeEdgeTable.begin ();
		tmp3++;	//����ͷ���
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

		//����activeEdgeTable��x��ֵ
		for(auto &tmp:activeEdgeTable){
			tmp.x+=tmp.dx;
		}
	}
	return ;
}

//���Ƴ���
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
	
	glClear(GL_COLOR_BUFFER_BIT);//����Ļ����Ϊ��ɫ
	glColor3f(1.0,0.0,0.0);//���õ�ǰ��ɫ״̬Ϊ��ɫ

	boundaryFill(pointList1);
	glFlush();//����������
	return ;
} 

//��ʼ������
void initbf(){
	glClearColor(1.0,1.0,1.0,0.0);//�����ɫ����
	glMatrixMode(GL_PROJECTION);//����ͶӰ��ʽ
	gluOrtho2D (0.0,windowWidgebf*1.0,0.0,windowHeightbf*1.0);
	return ;
}
//----------------------------------------------------------------------------------

//----------------------------------------------------------------------------------
//�˵�

//��������
void draw()
{
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(0, 1, 0);
    glOrtho(-1, 1, -1, 1, -1, 1);
    glutSwapBuffers();
}

//���ĳ����Ŀʱ���������Ŀ�����ĸ��˵�
void getcurrentmenu()
{
    int nmenu;
    nmenu = glutGetMenu();
    if (nmenu == menu)
        printf("��ѡ��.\n");
}

//��һ���Ӳ˵�	���ν�ģ����
void submenufunc1(int data)
{
    getcurrentmenu();
    switch (data)
    {
    case 1:
        printf("DDA����.\n");
        setNewWindow();
        glutCreateWindow("line_DDA"); //���ô��ڱ���
        init();
        glutDisplayFunc(displayLineDDA);
        glutMainLoop();
        break;
    case 2:
        printf("�е㻭��.\n");
        setNewWindow();
        glutCreateWindow("line_Midpoint"); //���ô��ڱ���
        init();
        glutDisplayFunc(displayLineMidpoint);
        glutMainLoop();
        break;
    case 3:
        printf("Bresenham����.\n");
        setNewWindow();
        glutCreateWindow("line_Bresenham"); //���ô��ڱ���
        init();
        glutDisplayFunc(displayLineBres);
        glutMainLoop();
        break;
    case 4:
        printf("�е㻭Բ.\n");
        setNewWindow();
        glutCreateWindow("circle_Midpoint"); //���ô��ڱ���
        init();
        glutDisplayFunc(displayCircleMidpoint);
        glutMainLoop();
        break;
    case 5:
        printf("B��������.\n");
        //��ʼ������ʾ����Ļ����
        glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
        glutInitWindowPosition(600, 100); //ָ������λ��
        glutInitWindowSize(600, 600);     //ָ�����ڴ�С
        glutCreateWindow("��굥�����㣬������Զ��������");
        glClearColor(1, 1, 1, 0);
        glShadeModel(GL_FLAT);
        glutDisplayFunc(display3B);
        glutReshapeFunc(Reshape3B);
        glutMouseFunc(mouse3B);
        glutKeyboardFunc(keyboard3B);
        glutMainLoop();
        break;
    case 6:
        printf("Liang-Barsky �߶βü��㷨.\n");
        glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);   //������ʾģʽΪ�����壬RGBģʽ
        glutInitWindowPosition(600, 100);              //���ô���λ��
        glutInitWindowSize(windowWidge, windowHeight); //���ô��ڴ�С
        glutCreateWindow("Liang-Barsky �߶βü��㷨"); //���ô��ڱ���
        init16();
        glutDisplayFunc(display16);
        glutMainLoop();
        break;
    case 7:
        printf("Sutherland-Hodgman����βü��㷨.\n");
        glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);          //������ʾģʽΪ�����壬RGBģʽ
        glutInitWindowPosition(600, 100);                     //���ô���λ��
        glutInitWindowSize(windowWidge, windowHeight);        //���ô��ڴ�С
        glutCreateWindow("Sutherland-Hodgman����βü��㷨"); //���ô��ڱ���
        init17();
        glutDisplayFunc(display17);
        glutMainLoop();
        break;
    case 8:
        printf("�����ɨ������㷨.\n");
        glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);          //������ʾģʽΪ�����壬RGBģʽ
        glutInitWindowPosition(600, 100);                     //���ô���λ��
        glutInitWindowSize(windowWidgebf, windowHeightbf);        //���ô��ڴ�С
        glutCreateWindow("�����ɨ��������㷨");//���ô��ڱ���
		initbf();
		glutDisplayFunc(displaybf);
        glutMainLoop();
        break;    
    }
}

//�ڶ����Ӳ˵�	���α任����
void submenufunc2(int data)
{
    getcurrentmenu();
    switch (data)
    {
    case 1:
        printf("ʱ��.\n");
        setNewWindow();
        glutInitWindowSize(600, 600); //���ô��ڵĿ��
        glutCreateWindow("ʱ��");
        gluOrtho2D(0, 600.0, 0.0, 600.0); //��������ϵ
        initClock();                      //��ʼ��
        glutDisplayFunc(displayClock);
        glutTimerFunc(1000, timerFunc, 1); //ÿһ��ִ��һ��
        glutMainLoop();
        break;
    case 2:
        printf("С���ƶ�����.\n");
        setNewWindow();
        glutCreateWindow("С���ƶ�����");
        Init22();
        glutDisplayFunc(&Display22);
        glutReshapeFunc(&Reshape22);
        glutIdleFunc(&myIdle22);
        glutMainLoop();
        break;
    }
}

//�������Ӳ˵�	��Դ�����ʺ�����ӳ�书��
void submenufunc3(int data)
{
    getcurrentmenu();
    switch (data)
    {
    case 1:
        printf("����Դ.\n");
        setNewWindow();
        glutCreateWindow("����Դ");
        Initsinglelight();
        glutDisplayFunc(&Display22);
        glutReshapeFunc(&Reshape22);
        glutIdleFunc(&myIdle22);
        glutMainLoop();
        break;
    case 2:
        printf("���Դ����.\n");
        setNewWindow();
        glutCreateWindow("���Դ����");
        Init22();
        glutDisplayFunc(&Display22);
        glutReshapeFunc(&Reshape22);
        glutIdleFunc(&myIdle22);
        glutMainLoop();
        break;
    case 3:
        printf("����ӳ��.\n");
        glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
        glutInitWindowPosition(600, 100); //���ô���λ��
        glutInitWindowSize(400, 400);
        glutCreateWindow("����ӳ��");
        initRendering();
        glutDisplayFunc(drawScene);
        glutKeyboardFunc(handleKeypress);
        glutReshapeFunc(handleResize32);
        glutMainLoop();
        break;
    }
}

//���ĸ��Ӳ˵�	���ӻ�����
void submenufunc4(int data)
{
    getcurrentmenu();
    switch (data)
    {
    case 1:
        printf("��պ�+����ģ��+�ӵ�任+����任+����ӳ�䣨������+���壩.\n");
        glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); //������ʾģʽΪ�����壬RGBģʽ
        //���ô���λ��
        glutInitWindowPosition(600, 100);
        //���ô��ڴ�С
        glutInitWindowSize(windowWidge, windowHeight);
        //���ô��ڱ���
        glutCreateWindow("���¿����ƶ���wasd���Ʒ���");
        //��ʼ��glut�����ƻ���:
        init41();
        glutDisplayFunc(display);
        //ע�������Ӧ����
        glutKeyboardFunc(keyboradAck);
        glutSpecialFunc(specialKeyAck);
        //����ʱ�Զ����ú���:
        glutIdleFunc(myIdle);
        //���ڳߴ�仯����:
        glutReshapeFunc(handleResize);
        glutMainLoop();
        break;
    }
}

//���˵�
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
    glutCreateWindow("��Ҫ�˵����ڴ˺�ɫ�����Ҽ���������������������رգ�������������");
    glutDisplayFunc(draw);

    //�����Ӳ˵�1������
    submenu1 = glutCreateMenu(submenufunc1);
    glutAddMenuEntry("DDA����", 1);
    glutAddMenuEntry("�е㻭��", 2);
    glutAddMenuEntry("Bresenham����", 3);
    glutAddMenuEntry("�е㻭Բ", 4);
    glutAddMenuEntry("B����������", 5);
    glutAddMenuEntry("Liang-Barsky �߶βü��㷨", 6);
    glutAddMenuEntry("Sutherland-Hodgman����βü��㷨", 7);
    glutAddMenuEntry("�����ɨ��������㷨", 8);

    //�����Ӳ˵�2������
    submenu2 = glutCreateMenu(submenufunc2);
    glutAddMenuEntry("ʱ��", 1);
    glutAddMenuEntry("С���ƶ�����", 2);

    //�����Ӳ˵�3������
    submenu3 = glutCreateMenu(submenufunc3);
    glutAddMenuEntry("����Դ", 1);
    glutAddMenuEntry("���Դ����", 2);
    glutAddMenuEntry("����ӳ��", 3);

    //�����Ӳ˵�4������
    submenu4 = glutCreateMenu(submenufunc4);
    glutAddMenuEntry("��պ�+����ģ��+�ӵ�任+����任+����ӳ�䣨������+���壩", 1);

    //�������˵�������
    menu = glutCreateMenu(menufunc);
    glutAddMenuEntry("��ѡ��-ע�⣺��������ر�", 1);

    //�������˵���Ϊ��һ���˵����Ӳ˵�
    glutAddSubMenu("���ν�ģ����", submenu1);
    glutAddSubMenu("���α任����", submenu2);
    glutAddSubMenu("��Դ�����ʺ�����ӳ�书��", submenu3);
    glutAddSubMenu("���ӻ�����", submenu4);
    //�������Ҽ�ʱ��ʾ�˵�
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutMainLoop();
    return 0;
}

