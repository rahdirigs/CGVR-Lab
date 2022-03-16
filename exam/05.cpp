#include <GLUT/glut.h>
#include <iostream>

using namespace std;
using point = float[3];

int n;
point v[4] = {
	{0, 250, -250},
	{0, 0, 250},
	{250, -250, -250},
	{-250, -250, -250}
};

void myInit()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glOrtho(-300, 300, -300, 300, -300, 300);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void drawTriangle(point p1, point p2, point p3)
{
	glBegin(GL_TRIANGLES);
	glVertex3fv(p1);
	glVertex3fv(p2);
	glVertex3fv(p3);
	glEnd();
}

void tetrahedron(point p1, point p2, point p3, point p4)
{
	glColor3f(1.0, 0.0, 0.0);
	drawTriangle(p1, p2, p3);
	glColor3f(0.0, 1.0, 0.0);
	drawTriangle(p1, p2, p4);
	glColor3f(1.0, 0.0, 1.0);
	drawTriangle(p1, p3, p4);
	glColor3f(0.0, 0.0, 1.0);
	drawTriangle(p2, p3, p4);
}

void divideTetrahedron(point p1, point p2, point p3, point p4, int m)
{
	if (m == 0)
	{
		tetrahedron(p1, p2, p3, p4);
		return;
	}
	point mid[6];
	for (int i = 0; i < 3; i++)
	{
		mid[0][i] = (p1[i] + p2[i]) / 2;
		mid[1][i] = (p1[i] + p3[i]) / 2;
		mid[2][i] = (p1[i] + p4[i]) / 2;
		mid[3][i] = (p2[i] + p3[i]) / 2;
		mid[4][i] = (p2[i] + p4[i]) / 2;
		mid[5][i] = (p3[i] + p4[i]) / 2;
	}
	divideTetrahedron(p1, mid[0], mid[1], mid[2], m - 1);
	divideTetrahedron(mid[0], p2, mid[3], mid[4], m - 1);
	divideTetrahedron(mid[1], mid[3], p3, mid[5], m - 1);
	divideTetrahedron(mid[2], mid[4], mid[5], p4, m - 1);
}

void displayFunction()
{
	divideTetrahedron(v[0], v[1], v[2], v[3], n);
	glFlush();
}

int main(int argc, char **argv)
{
	cout << "Enter the number of divisions: ";
	cin >> n;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("3D Sierpinski Gasket - Volume Division");
	myInit();
	glutDisplayFunc(displayFunction);
	glEnable(GL_DEPTH_TEST);
	glutMainLoop();
}