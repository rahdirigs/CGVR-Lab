#include <GLUT/glut.h>
#include <iostream>

using namespace std;

struct LineSegment {
	int x1, y1, x2, y2;
};

LineSegment ls[10];

int xmin, ymin, xmax, ymax;
int xvmin, yvmin, xvmax, yvmax;
int n;

const int TOP = 1;
const int BOTTOM = 2;
const int RIGHT = 4;
const int LEFT = 8;

void myInit()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	gluOrtho2D(0, 500, 0, 500);
	glClear(GL_COLOR_BUFFER_BIT);
}

int computeOutcode(double x, double y)
{
	int outcode = 0;
	if (x > xmax)
	{
		outcode |= RIGHT;
	}
	if (x < xmin)
	{
		outcode |= LEFT;
	}
	if (y > ymax)
	{
		outcode |= TOP;
	}
	if (y < ymin)
	{
		outcode |= BOTTOM;
	}
	return outcode;
}

void cohenSutherland(double x1, double y1, double x2, double y2)
{
	int outcode1 = computeOutcode(x1, y1);
	int outcode2 = computeOutcode(x2, y2);
	bool accept = false, done = false;
	double x, y;
	int cur = 0;
	do {
		if (!(outcode1 | outcode2))
		{
			accept = true;
			done = true;
		}
		else if (outcode1 & outcode2)
		{
			done = true;
		}
		else
		{
			cur = outcode1 ? outcode1 : outcode2;
			if (cur & TOP)
			{
				y = ymax;
				x = x1 + (y - y1) * (x2 - x1) / (y2 - y1);
			}
			else if (cur & BOTTOM)
			{
				y = ymin;
				x = x1 + (y - y1) * (x2 - x1) / (y2 - y1);
			}
			else if (cur & RIGHT)
			{
				x = xmax;
				y = y1 + (x - x1) * (y2 - y1) / (x2 - x1);
			}
			else
			{
				x = xmin;
				y = y1 + (x - x1) * (y2 - y1) / (x2 - x1);
			}
			if (cur == outcode1)
			{
				x1 = x;
				y1 = y;
				outcode1 = computeOutcode(x1, y1);
			}
			else
			{
				x2 = x;
				y2 = y;
				outcode2 = computeOutcode(x2, y2);
			}
		}
	} while (!done);
	if (accept)
	{
		double sx = (double) (xvmax - xvmin) / (xmax - xmin);
		double sy = (double) (yvmax - yvmin) / (ymax - ymin);
		double xv1 = xvmin + (x1 - xmin) * sx;
		double yv1 = yvmin + (y1 - ymin) * sy;
		double xv2 = xvmin + (x2 - xmin) * sx;
		double yv2 = yvmin + (y2 - ymin) * sy;
		glBegin(GL_LINES);
		glVertex2d(xv1, yv1);
		glVertex2d(xv2, yv2);
		glEnd();
	}
}

void displayFunction()
{
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINE_LOOP);
	glVertex2i(xmin, ymin);
	glVertex2i(xmax, ymin);
	glVertex2i(xmax, ymax);
	glVertex2i(xmin, ymax);
	glEnd();
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_LINES);
	for (int i = 0; i < n; i++)
	{
		glVertex2i(ls[i].x1, ls[i].y1);
		glVertex2i(ls[i].x2, ls[i].y2);
	}
	glEnd();
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINE_LOOP);
	glVertex2i(xvmin, yvmin);
	glVertex2i(xvmax, yvmin);
	glVertex2i(xvmax, yvmax);
	glVertex2i(xvmin, yvmax);
	glEnd();
	glColor3f(0.0, 0.0, 1.0);
	for (int i = 0; i < n; i++)
	{
		cohenSutherland(ls[i].x1, ls[i].y1, ls[i].x2, ls[i].y2);
	}
	glFlush();
}

int main(int argc, char **argv)
{
	cout << "Enter the window co-ordinates: ";
	cin >> xmin >> ymin >> xmax >> ymax;
	cout << "Enter the viewport co_ordinates: ";
	cin >> xvmin >> yvmin >> xvmax >> yvmax;
	cout << "Enter the number of lines: ";
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cout << "Enter the endpoints of line " << i + 1 << ": ";
		cin >> ls[i].x1 >> ls[i].y1 >> ls[i].x2 >> ls[i].y2;
	}
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Cohen-Sutherland Line Clipping");
	myInit();
	glutDisplayFunc(displayFunction);
	glutMainLoop();
}