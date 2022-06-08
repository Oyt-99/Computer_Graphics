#include<windows.h>
#include<gl/gl.h>  
#include<gl/glut.h>  
void SetupRC(void)
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}

void DrawTriangle(void)
{
	glBegin(GL_TRIANGLES);
	glVertex2f(0.0f, 0.0f);
	glVertex2f(40.0f, 0.0f);
	glVertex2f(20.0f, 40.0f);
	glEnd();
}
void ChangeSize(int w, int h)
{
	if (h == 0)
		h = 1;
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();


	if (w <= h)
		glOrtho(-100.0f, 100.0f, -100.0f * h / w, 100.0f * h / w, -100.0f, 100.0f);
	else
		glOrtho(-100.0f * w / h, 100.0f * w / h, -100.0f, 100.0f, -100.0f, 100.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_LINES);
	glVertex2f(-100.0f, 0.0f);
	glVertex2f(100.0f, 0.0f);
	glVertex2f(0.0f, -100.0f);
	glVertex2f(0.0f, 100.0f);
	glEnd();

	glColor3f(1.0f, 1.0f, 1.0f);
	DrawTriangle();

	glRotatef(200.0f, 0.0f, 0.0f, 1.0f);
	glColor3f(1.0f, 1.0f, 1.0f);
	DrawTriangle();
 
	glLoadIdentity();

	glEnable(GL_LINE_STIPPLE);
	glLineStipple(1, 0xF0F0);
	glLoadIdentity();
	glTranslatef(0.0, 50.0, 0.0);
	glRotatef(-45, 0.0, 0.0, 1.0);
	glScalef(1.0, -1.0, 1.0);
	glRotatef(45, 0.0, 0.0, 1.0);
	glTranslatef(0.0, -50.0, 0.0);
	glColor3f(0.5, 0.5, 1.0);
	DrawTriangle();

	glLoadIdentity();
  
	glTranslatef(-60.0f, 0.0f, 0.0f);
	glColor3f(1.0f, 1.0f, 0.0f);
	DrawTriangle();  
	glTranslatef(120.0f, 0.0f, 0.0f); 
	glScalef(1.0f, 2.0f, 100.0f);
	glColor3f(1.0f, 1.0f, 0.0f);
	DrawTriangle();
	glutSwapBuffers();

}
int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutCreateWindow("变换示例");
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);
	SetupRC();
	glutMainLoop();
	return 0;
}