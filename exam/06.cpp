#include <GLUT/glut.h>
#include <iostream>
#include <cmath>

using namespace std;

const double RAD = M_PI / 180.0;

void myInit()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glOrtho(-2.0, 2.0, -2.0, 2.0, -2.0, 2.0);
	glColor3f(0.0, 0.0, 1.0);
}

void reshapeFunction(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
	{
		glOrtho(-2.0, 2.0, -2.0 * (float) h / w, 2.0 * (float) h / w, -2.0, 2.0);
	}
	else
	{
		glOrtho(-2.0 * (float) w / h, 2.0 * (float) w / h, -2.0, 2.0, -2.0, 2.0);
	}
	glTranslatef(0, 0, -1);
	glRotatef(-45, 1, 0, 0);
	glRotatef(30, 0, 1, 0);
	glScalef(2, 2, 2);
	glMatrixMode(GL_MODELVIEW);
	glutPostRedisplay();
}

void displayFunction()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	double theta, thetar, phi, phir, phir20;
	double x, y, z;
	for (phi = -80.0; phi <= 80.0; phi += 20.0)
	{
		phir = phi * RAD;
		phir20 = (phi + 20.0) * RAD;
		glBegin(GL_QUAD_STRIP);
		for (theta = -180.0; theta <= 180.0; theta += 20.0)
		{
			thetar = theta * RAD;
			x = sin(thetar) * cos(phir);
			y = cos(thetar) * cos(phir);
			z = sin(phir);
			glVertex3d(x, y, z);
			x = sin(thetar) * cos(phir20);
			y = cos(thetar) * cos(phir20);
			z = sin(phir20);
			glVertex3d(x, y, z);
		}
		glEnd();
	}
	double c80 = 80.0 * RAD;
	z = sin(c80);
	glBegin(GL_TRIANGLE_FAN);
	glVertex3d(0, 0, 1);
	for (theta = -180.0; theta <= 180.0; theta += 20.0)
	{
		thetar = theta * RAD;
		x = sin(thetar) * cos(c80);
		y = cos(thetar) * cos(c80);
		glVertex3d(x, y, z);
	}
	glEnd();
	z = -sin(c80);
	glBegin(GL_TRIANGLE_FAN);
	glVertex3d(0, 0, -1);
	for (theta = -180.0; theta <= 180.0; theta += 20.0)
	{
		thetar = theta * RAD;
		x = sin(thetar) * cos(c80);
		y = cos(thetar) * cos(c80);
		glVertex3d(x, y, z);
	}
	glEnd();
	glFlush();
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Sphere Rendering");
	myInit();
	glutDisplayFunc(displayFunction);
	glutReshapeFunc(reshapeFunction);
	glEnable(GL_DEPTH_TEST);
	glutMainLoop();
}