#include <GLUT/glut.h>
#include <iostream>
#include <cmath>

using namespace std;

const double DEG = 180.0 / M_PI;

double angle;
double m, c;
double theta;

float house[11][2] = {
	{100, 200}, {200, 250}, {300, 200},
	{100, 200}, {100, 100}, {175, 100},
	{175, 150}, {225, 150}, {225, 100},
	{300, 100}, {300, 200}
};

void myInit()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-450, 450, -450, 450);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void normalHouse()
{
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 11; i++)
	{
		glVertex2f(house[i][0], house[i][1]);
	}
	glEnd();
	glFlush();
}

void displayFunction()
{
	glColor3f(1.0, 0.0, 0.0);
	normalHouse();
}

void rotateHouse()
{
	myInit();
	glColor3f(1.0, 0.0, 0.0);
	normalHouse();
	glPushMatrix();
	glTranslatef(100, 100, 0);
	glRotatef(angle, 0, 0, 1);
	glTranslatef(-100, -100, 0);
	glColor3f(0.0, 1.0, 0.0);
	normalHouse();
}

void reflectHouse()
{
	myInit();
	glColor3f(1.0, 0.0, 0.0);
	normalHouse();
	int x1 = -450, x2 = 450;
	int y1 = m * x1 + c, y2 = m * x2 + c;
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex2f(x1, y1);
	glVertex2f(x2, y2);
	glEnd();
	glPushMatrix();
	glTranslatef(0, c, 0);
	theta = atan(m);
	theta *= DEG;
	glRotatef(theta, 0, 0, 1);
	glScalef(1, -1, 1);
	glRotatef(-theta, 0, 0, 1);
	glTranslatef(0, -c, 0);
	glColor3f(0.0, 0.0, 1.0);
	normalHouse();
}

void mouseFunction(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		rotateHouse();
	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		reflectHouse();
	}
}

int main(int argc, char **argv)
{
	cout << "Enter the angle of rotation in degrees: ";
	cin >> angle;
	cout << "Enter the 'm' (slope) and 'c' (intercept) values for the line: ";
	cin >> m >> c;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(900, 900);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("House - rotation and reflection");
	myInit();
	glutDisplayFunc(displayFunction);
	glutMouseFunc(mouseFunction);
	glutMainLoop();
}