#include <GLUT/glut.h>
#include <iostream>
#include <cmath>

using namespace std;

int choice, xc, yc, r, flag, n, x[2], y[2];

void myInit()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	gluOrtho2D(0, 500, 0, 500);
	glClear(GL_COLOR_BUFFER_BIT);
}

void plotPixels(int xp, int yp, int h, int k)
{
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_POINTS);
	glVertex2i(xp + h, yp + k);
	glVertex2i(-xp + h, yp + k);
	glVertex2i(-xp + h, -yp + k);
	glVertex2i(xp + h, -yp + k);
	glEnd();
}

void drawCircle()
{
	int xp = 0, yp = r;
	int p = 3 - 2 * r;
	while (yp > xp)
	{
		plotPixels(xp, yp, xc, yc);
		plotPixels(yp, xp, xc, yc);
		if (p > 0)
		{
			p += 4 * (xp - yp) + 10;
			yp--;
		}
		else
		{
			p += 4 * xp + 6;
		}
		xp++;
	}
	plotPixels(xp, yp, xc, yc);
	plotPixels(yp, xp, xc, yc);
}

void mouseFunction(int button, int state, int xm, int ym)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if (flag == 0)
		{
			x[0] = xm;
			y[0] = 500 - ym;
			xc = x[0];
			yc = y[0];
			cout << "Recorded (xc, yc) as (" << x[0] << ", " << y[0] << ")\n";
		}
		else
		{
			x[1] = xm;
			y[1] = 500 - ym;
			int r2 = (x[1] - x[0]) * (x[1] - x[0]) + (y[1] - y[0]) * (y[1] - y[0]);
			r = (int) sqrt(r2);
			cout << "Radius = " << r << "\n";
			drawCircle();
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
	cout << "Enter the number of circles: ";
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cout << "Enter xc and yc i.e., the centre for circle no. " << i + 1 << ": ";
		cin >> xc >> yc;
		cout << "Enter the radius r for the circle no. " << i + 1 << ": ";
		cin >> r;
		drawCircle();
		glFlush();
	}
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Bressenham's Circle Drawing");
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