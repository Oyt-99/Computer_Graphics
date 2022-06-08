#include<GL/glut.h>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include <iostream>

int x, y, xEnd, yEnd;

int intround(const float a) { return GLint(a + 0.5); }

void setPixel(GLint x, GLint y) {
	glBegin(GL_POINTS);
	glVertex2d(x, y);
	glEnd();
}

void lineDDA(int x0, int y0, int xend, int yend) {
	int dx = xend - x0, dy = yend - y0, steps, i;
	float xIncreasement, yIncreasement, x = x0, y = y0;
	if (fabs(dx) > fabs(dy))
		steps = fabs(dx);
	else steps = fabs(dy);
	xIncreasement = float(dx) / float(steps);
	yIncreasement = float(dy) / float(steps);
	setPixel(intround(x), intround(y));

	for (i = 0; i < steps; i++) {
		x += xIncreasement;
		y += yIncreasement;
		setPixel(intround(x), intround(y));
	}
}

void init(void) {
	glClearColor(1.0, 0.9, 1.0, 0.0);

	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, 200.0, 0.0, 150.0);
}

void lineSegment()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.4, 0.2);
	lineDDA(x, y, xEnd, yEnd);

	glFlush();
}

int main(int argc, char** argv)
{

	printf("请分别输入线段起点的横纵坐标以及终点的横纵坐标，中间用空格隔开\n");
	std::cin >> x;
	std::cin >> y;
	std::cin >> xEnd;
	std::cin >> yEnd;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(50, 100);
	glutInitWindowSize(200, 200);
	glutCreateWindow("A DDA line");

	init();
	glutDisplayFunc(lineSegment);
	glutMainLoop();

	return 0;
}
