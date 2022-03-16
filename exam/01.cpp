#include <GLUT/glut.h>
#include <iostream>
#include <cmath>

using namespace std;

int choice, n, x[2], y[2], flag;

void myInit()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	gluOrtho2D(0, 500, 0, 500);
	glClear(GL_COLOR_BUFFER_BIT);
}

void plotPixel(int xp, int yp)
{
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_POINTS);
	glVertex2i(xp, yp);
	glEnd();
}

void drawLine()
{
	int dx, dy, ix = 1, iy = 1;
	int delta1, delta2;
	dx = abs(x[1] - x[0]);
	dy = abs(y[1] - y[0]);
	if (x[1] < x[0])
	{
		ix = -1;
	}
	if (y[1] < y[0])
	{
		iy = -1;
	}
	int xc = x[0], yc = y[0];
	if (dy < dx)
	{
		int p = 2 * dy - dx;
		delta1 = 2 * (dy - dx);
		delta2 = 2 * dy;
		plotPixel(xc, yc);
		for (int i = 0; i < dx; i++)
		{
			if (p > 0)
			{
				yc += iy;
				p += delta1;
			}
			else
			{
				p += delta2;
			}
			xc += ix;
			plotPixel(xc, yc);
		}
	}
	else
	{
		int p = 2 * dx - dy;
		delta1 = 2 * (dx - dy);
		delta2 = 2 * dx;
		plotPixel(xc, yc);
		for (int i = 0; i < dy; i++)
		{
			if (p > 0)
			{
				xc += ix;
				p += delta1;
			}
			else
			{
				p += delta2;
			}
			yc += iy;
			plotPixel(xc, yc);
		}
	}
}

void mouseFunction(int button, int state, int xm, int ym)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if (flag == 0)
		{
			x[0] = xm;
			y[0] = 500 - ym;
			cout << "Recorded (x1, y1) as (" << x[0] << ", " << y[0] << ")\n";
		}
		else
		{
			x[1] = xm;
			y[1] = 500 - ym;
			cout << "Recorded (x2, y2) as (" << x[1] << ", " << y[1] << ")\n";
			drawLine();
			glFlush();
		}
		flag ^= 1;
	}
}

void mouseDisplay()
{

}

void keyboardDisplay()
{
	cout << "Enter the number of lines: ";
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cout << "Enter x1 and y1 for line no. " << i + 1 << ": ";
		cin >> x[0] >> y[0];
		cout << "Enter x2 and y2 for line no. " << i + 1 << ": ";
		cin >> x[1] >> y[1];
		drawLine();
		glFlush();
	}
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Bressenham's Line Drawing");
	cout << "Enter the input mode\n1. Keyboard\n2. Mouse\n";
	cin >> choice;
	myInit();
	switch (choice)
	{
		case 1:
			glutDisplayFunc(keyboardDisplay);
			break;
		case 2:
			glutMouseFunc(mouseFunction);
			glutDisplayFunc(mouseDisplay);
			break;
		default:
			cout << "Invalid choice...";
			return 0;
	}
	glutMainLoop();
}