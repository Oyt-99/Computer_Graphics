#include <GL/glut.h>      // OPenGL实用工具库

#define LEFT 1
#define RIGHT 2
#define BOTTOM 4
#define TOP 8

int x1 = 150, y1 = 50, x2 = 250, y2 = 150, XL = 100, XR = 300, YB = 100, YT = 200;  //(x1,y1)、(x2,y2)为直线段的端点，XL为左边界，XR为右边界，YB为下边界，YT为上边界
int x1_init = 150, y1_init = 50, x2_init = 250, y2_init = 150;  //将直线段端点备份，以便画出裁剪前的直线段

char encode(float x, float y)
{
    char c = 0;
    if (x < XL) c |= LEFT;
    if (x > XR) c |= RIGHT;
    if (y < YB) c |= BOTTOM;
    if (y > YT) c |= TOP;
    return c;
}

void CS_LineClip(int& x1, int& y1, int& x2, int& y2, int XL, int XR, int YB, int YT) {
    char code1 = encode(x1, y1);
    char code2 = encode(x2, y2);
    char code;
    int x, y;
    while (code1 || code2) {
        if ((code1 & code2) != 0)return; //在外同侧
        if (code1 != 0) code = code1;
        else code = code2;
        if ((LEFT & code) != 0) {
            x = XL; y = y1 + (y2 - y1) * (XL - x1) / (x2 - x1);
        }
        else if ((RIGHT & code) != 0) {
            x = XR; y = y1 + (y2 - y1) * (XR - x1) / (x2 - x1);
        }
        else if ((BOTTOM & code) != 0) {
            y = YB; x = x1 + (x2 - x1) * (YB - y1) / (y2 - y1);
        }
        else if ((TOP & code) != 0) {
            y = YT; x = x1 + (x2 - x1) * (YT - y1) / (y2 - y1);
        }
        if (code == code1) {
            x1 = x; y1 = y; code1 = encode(x, y);
        }
        else { x2 = x; y2 = y; code2 = encode(x, y); }
    }
}

void init(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);  // 设置背景颜色
    glMatrixMode(GL_PROJECTION);       // 设置投影参数
    gluOrtho2D(0.0, 600.0, 0.0, 400.0); // 设置场景的大小
}


void draw(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0, 0.0, 0.0);      // 设置画图颜色
    glLineWidth(2);                // 设置边框宽度
    glPointSize(2);
    glPushMatrix();
    //glTranslatef(dx, dy, 0); //图形变换操作须放在绘制之前

    glBegin(GL_LINE_LOOP);
    glVertex2i(XL, YT);
    glVertex2i(XL, YB);
    glVertex2i(XR, YB);
    glVertex2i(XR, YT);
    glEnd();

    //绘制未裁剪前的线段
    glBegin(GL_LINES);
    glVertex2i(x1_init, y1_init);
    glVertex2i(x2_init, y2_init);
    glEnd();
    //绘制裁剪后的线段
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex2i(x1, y1);
    glVertex2i(x2, y2);
    glEnd();

    CS_LineClip(x1, y1, x2, y2, XL, XR, YB, YT);
    glPopMatrix();
    glFlush();     // 处理绘图pipeLine
    //glutSwapBuffers(); //GLUT_DOUBLE
}

void main(int argc, char** argv)
{
    glutInit(&argc, argv);  // 初始化GLUT环境
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);   // GLUT显示模式：单缓冲区、RGB颜色模型
    //glutInitWindowPosition(50, 100);   // 窗口左上角的位置
    glutInitWindowSize(800, 600);      // 显示窗口的大小
    glutCreateWindow("Cohen-Sutherland裁剪算法"); // 创建显示窗口，加上标题
    init();
    glutDisplayFunc(draw);           // 调用绘图函数
    glutMainLoop();				 // 进入事件处理循环
}
