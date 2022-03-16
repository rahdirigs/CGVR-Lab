#include <GLUT/glut.h>
#include <iostream>
#include <algorithm>
#include <ctime>

using namespace std;

const int MAXN = 20;

int n;
int poly[MAXN][2];
int x[MAXN], id;

void delay(int sec)
{
	int ms = 1000 * sec;
	clock_t startTime = clock();
	while (clock() < startTime + ms);
}

void myInit()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	gluOrtho2D(0, 500, 0, 500);
	glClear(GL_COLOR_BUFFER_BIT);
	glPointSize(1.0);
	glLineWidth(1.5);
}

void drawLine(int x1, int x2, int y)
{
	glColor3f(1.0, 1.0, 0.0);
	glBegin(GL_LINES);
	glVertex2i(x1, y);
	glVertex2i(x2, y);
	glEnd();
}

void detectEdge(int x1, int y1, int x2, int y2, int y)
{
	if (y1 > y2)
	{
		swap(x1, x2);
		swap(y1, y2);
	}
	if (y > y1 && y < y2)
	{
		x[id++] = x1 + (y - y1) * (x2 - x1) / (y2 - y1);
	}
}

void scanline()
{
	for (int y = 0; y < 500; y++)
	{
		id = 0;
		for (int i = 0; i < n; i++)
		{
			int k = (i + 1) % n;
			detectEdge(poly[i][0], poly[i][1], poly[k][0], poly[k][1], y);
			if (id >= 2)
			{
				sort(x, x + id);
				for (int j = 0; j < id; j += 2)
				{
					drawLine(x[j], x[j + 1], y);
				}
			}
		}
		delay(1);
	}
}

void displayFunction()
{
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < n; i++)
	{
		glVertex2iv(poly[i]);
	}
	glEnd();
	scanline();
	glFlush();
}

int main(int argc, char **argv)
{
	cout << "Enter the size of the polygon: ";
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cout << "Enter the vertex " << i + 1 << " of the polygon: ";
		cin >> poly[i][0] >> poly[i][1]; 
	}
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Scanline polygon filling");
	myInit();
	glutDisplayFunc(displayFunction);
	glutMainLoop();
}