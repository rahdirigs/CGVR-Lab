#include <GLUT/glut.h>
#include <iostream>

using namespace std;

const int MAXN = 20;

int pn, cn, npn;
int poly[MAXN][2], clipper[MAXN][2], newPoly[MAXN][2];

void myInit()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	gluOrtho2D(0, 500, 0, 500);
	glClear(GL_COLOR_BUFFER_BIT);
}

int x_intersect(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4)
{
	int num = (x1 * y2 - x2 * y1) * (x3 - x4) - (x3 * y4 - x4 * y3) * (x1 - x2);
	int den = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
	return num / den;
}

int y_intersect(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4)
{
	int num = (x1 * y2 - x2 * y1) * (y3 - y4) - (x3 * y4 - x4 * y3) * (y1 - y2);
	int den = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
	return num / den;
}

void sutherlandHodgeman(int x1, int y1, int x2, int y2)
{
	npn = 0;
	for (int i = 0; i < pn; i++)
	{
		int k = (i + 1) % pn;
		int ix = poly[i][0], iy = poly[i][1];
		int kx = poly[k][0], ky = poly[k][1];
		int ipos = (x2 - x1) * (iy - y1) - (y2 - y1) * (ix - x1);
		int kpos = (x2 - x1) * (ky - y1) - (y2 - y1) * (kx - x1);
		if (ipos >= 0 && kpos >= 0)
		{
			newPoly[npn][0] = kx;
			newPoly[npn][1] = ky;
			npn++;
		}
		else if (ipos < 0 && kpos >= 0)
		{
			newPoly[npn][0] = x_intersect(x1, y1, x2, y2, ix, iy, kx, ky);
			newPoly[npn][1] = y_intersect(x1, y1, x2, y2, ix, iy, kx, ky);
			npn++;
			newPoly[npn][0] = kx;
			newPoly[npn][1] = ky;
			npn++;
		}
		else if (ipos >= 0 && kpos < 0)
		{
			newPoly[npn][0] = x_intersect(x1, y1, x2, y2, ix, iy, kx, ky);
			newPoly[npn][1] = y_intersect(x1, y1, x2, y2, ix, iy, kx, ky);
			npn++;
		}
	}
	pn = npn;
	for (int i = 0; i < pn; i++)
	{
		poly[i][0] = newPoly[i][0];
		poly[i][1] = newPoly[i][1];
	}
}

void displayFunction()
{
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < cn; i++)
	{
		glVertex2iv(clipper[i]);
	}
	glEnd();
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < pn; i++)
	{
		glVertex2iv(poly[i]);
	}
	glEnd();
	for (int i = 0; i < cn; i++)
	{
		int k = (i + 1) % cn;
		sutherlandHodgeman(clipper[i][0], clipper[i][1], clipper[k][0], clipper[k][1]);
	}
	glBegin(GL_POLYGON);
	for (int i = 0; i < pn; i++)
	{
		glVertex2iv(poly[i]);
	}
	glEnd();
	glFlush();
}

int main(int argc, char **argv)
{
	cout << "Enter the size of the polygon: ";
	cin >> pn;
	for (int i = 0; i < pn; i++)
	{
		cout << "Enter the vertex " << i + 1 << " of the polygon: ";
		cin >> poly[i][0] >> poly[i][1]; 
	}
	cout << "Enter the size of the clipping window: ";
	cin >> cn;
	for (int i = 0; i < cn; i++)
	{
		cout << "Enter the vertex " << i + 1 << " of the clipping window: ";
		cin >> clipper[i][0] >> clipper[i][1];
	}
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Sutherland-Hodgeman Polygon clipping");
	myInit();
	glutDisplayFunc(displayFunction);
	glutMainLoop();
}