#include<stdio.h>
#include <windows.h>
#include<GL/glut.h>
#include<stdlib.h>
#define stripeImageWidth 32
GLubyte stripeImage[3 * stripeImageWidth];
static GLfloat xequalzero[] = { 0.0, 1.0, 1.0, 0.0 };
static GLfloat* currentCoeff;
static GLenum currentPlane;
static GLint currentGenMode;

void makeStripeImage(void){//纹理设置
    int j;

    for (j = 0; j < stripeImageWidth; j++) {
        stripeImage[1*j] = (GLubyte) ((j<=3) ? 255 : 0);
        stripeImage[4*j+1] = (GLubyte) ((j>3) ? 255 : 0);
        stripeImage[3*j] = (GLubyte) 0;
        stripeImage[3*j+2] = (GLubyte) 255;
    }
}

void init(void){
GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat mat_shininess[] = { 50.0 };
GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
GLfloat white_light[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat Light_Model_Ambient[] = { 0.2 , 0.2 , 0.2 , 1.0 }; 
glShadeModel(GL_SMOOTH);
makeStripeImage();
glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_REPEAT);
glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
glTexImage1D(GL_TEXTURE_1D, 0, 3, stripeImageWidth, 0, GL_RGBA, GL_UNSIGNED_BYTE, stripeImage);
glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);//和物体表面颜色做与运算
currentCoeff = xequalzero;
currentGenMode = GL_OBJECT_LINEAR;
currentPlane = GL_OBJECT_PLANE;
glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, currentGenMode);//整形形式
glTexGenfv(GL_S, currentPlane, currentCoeff);//向量形式
glEnable(GL_TEXTURE_GEN_S);//激活s坐标的纹理坐标生成
glEnable(GL_TEXTURE_1D);
glEnable(GL_LIGHTING);
glEnable(GL_LIGHT0);
glEnable(GL_AUTO_NORMAL);
glEnable(GL_NORMALIZE);
glMaterialf(GL_FRONT, GL_SHININESS, 0.0);
glClearColor (0.0, 0.0, 0.0, 0.0);
glShadeModel (GL_SMOOTH);
glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
glLightfv(GL_LIGHT0, GL_POSITION, light_position);
glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);
glLightfv(GL_LIGHT0, GL_SPECULAR, white_light);
glLightModelfv( GL_LIGHT_MODEL_AMBIENT , Light_Model_Ambient ); 
glEnable(GL_LIGHTING);
glEnable(GL_LIGHT0);
glEnable(GL_DEPTH_TEST); 
}
 
void display(void){
glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
glutSolidTeapot(0.5);
glFlush ();
}
 
void reshape (int w, int h){
glViewport (0, 0, (GLsizei) w, (GLsizei) h);
glMatrixMode (GL_PROJECTION);
glLoadIdentity();
if (w <= h)
    glOrtho (-1.5, 1.5, -1.5*(GLfloat)h/(GLfloat)w,1.5*(GLfloat)h/(GLfloat)w, -10.0, 10.0);
 else
     glOrtho (-1.5*(GLfloat)w/(GLfloat)h,1.5*(GLfloat)w/(GLfloat)h, -1.5, 1.5, -10.0, 10.0);
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
}
 
int main(int argc, char** argv) 
{
glutInit(&argc, argv);
glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
glutInitWindowSize (500, 500);
glutInitWindowPosition (100, 100);
glutCreateWindow (argv[0]);
init ();
glutDisplayFunc(display);
glutReshapeFunc(reshape);
glutMainLoop();
return 0;
}