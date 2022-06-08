#include<stdio.h>
#include<GL/glut.h>
#include<math.h>

int r;

void CirclePoints(int x, int y) {
    glVertex2i(x, y);
    glVertex2i(y, x);
    glVertex2i(-x, y);
    glVertex2i(y, -x);
    glVertex2i(x, -y);
    glVertex2i(-y, x);
    glVertex2i(-x, -y);
    glVertex2i(-y, -x);
}

void IntMidPointCircle(int r) {
    int x, y, d;
    x = 0;
    y = r;
    d = 1 - r;
    CirclePoints(x, y);
    while (x < y) {
        if (d < 0)
            d += 2 * x + 3;
        else {
            d += 2 * (x - y) + 5;
            y--;
        }
        x++;
        CirclePoints(x, y);
    }
}

void init(void)
{
    glClearColor(1.0, 1.0, 1.0, 1.0);

    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, 200.0, 0.0, 150.0);
}

void myDisplay(void) {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glPointSize(1);
    glBegin(GL_POINTS);
    glColor3f(0.0f, 0.0f, 1.0f);
    IntMidPointCircle(r);
    glEnd();
    glFlush();
}

int main(int argc, char** argv) {
    printf("Please enter the radius of the circle:");
    scanf_s("%d", &r);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(400, 400);
    glutCreateWindow("HELLO WORLD!");
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-500.0, 500.0, -500.0, 500.0);
    glutDisplayFunc(&myDisplay);
    glutMainLoop();
}