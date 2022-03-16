#include <GLUT/glut.h>
#include <iostream>

using namespace std;

double db, angle = 0.0;

void reshapeFunction(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
	{
		gluOrtho2D(-2.0, 2.0, -2.0 * (float) h / w, 2.0 * (float) h / w);
	}
	else
	{
		gluOrtho2D(-2.0 * (float) w / h, 2.0 * (float) w / h, -2.0, 2.0);
	}
	glMatrixMode(GL_MODELVIEW);
}

void myInit()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	gluOrtho2D(-2.0, 2.0, -2.0, 2.0);
}

void singleDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POLYGON);
	glColor3f(1.0, 0.0, 0.0);
	glVertex2d(1.0, 1.0);
	glColor3f(0.0, 1.0, 0.0);
	glVertex2d(-1.0, 1.0);
	glColor3f(0.0, 0.0, 1.0);
	glVertex2d(-1.0, -1.0);
	glColor3f(1.0, 1.0, 0.0);
	glVertex2d(1.0, -1.0);
	glEnd();
	glFlush();
}

void doubleDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glRotatef(angle, 0, 0, 1);
	glBegin(GL_POLYGON);
	glColor3f(1.0, 0.0, 0.0);
	glVertex2d(1.0, 1.0);
	glColor3f(0.0, 1.0, 0.0);
	glVertex2d(-1.0, 1.0);
	glColor3f(0.0, 0.0, 1.0);
	glVertex2d(-1.0, -1.0);
	glColor3f(1.0, 1.0, 0.0);
	glVertex2d(1.0, -1.0);
	glEnd();
	glutSwapBuffers();
}

void spinFunction()
{
	angle += 0.1;
	if (angle > 360)
	{
		angle -= 360;
	}
	glutPostRedisplay();
}

void mouseFunction(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		glutIdleFunc(spinFunction);
	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		glutIdleFunc(NULL);
	}
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Single Buffer");
	myInit();
	glutDisplayFunc(singleDisplay);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(700, 700);
	db = glutCreateWindow("Double Buffer");
	myInit();
	glutDisplayFunc(doubleDisplay);
	glutMouseFunc(mouseFunction);
	glutReshapeFunc(reshapeFunction);

	glutMainLoop();
}