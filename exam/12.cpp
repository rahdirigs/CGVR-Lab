#include <GLUT/glut.h>

float vertices[] = {
	1, 1, 1,
	1, -1, 1,
	-1, -1, 1,
	-1, 1, 1,
	1, 1, -1,
	1, -1, -1,
	-1, -1, -1,
	-1, 1, -1
};

float colors[] = {
	1, 0, 0,
	0, 1, 0,
	0, 0, 1,
	1, 1, 0,
	1, 0, 1,
	0, 1, 1,
	0, 0, 0,
	1, 1, 1
};

GLubyte indices[] = {
	0, 1, 2, 3,
	4, 5, 6, 7,
	0, 4, 5, 1,
	3, 7, 6, 2,
	0, 4, 7, 3,
	1, 5, 6, 2
};

int axis = 0;
float theta[] = {
	0.0, 0.0, 0.0
};

void myInit()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glOrtho(-2.0, 2.0, -2.0, 2.0, -2.0, 2.0);
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
	glMatrixMode(GL_MODELVIEW);
}

void displayFunction()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glRotatef(theta[0], 1, 0, 0);
	glRotatef(theta[1], 0, 1, 0);
	glRotatef(theta[2], 0, 0, 1);
	glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, indices);
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex3d(0.0, 0.0, 0.0);
	glVertex3d(1.5, 1.5, 1.5);
	glEnd();
	glFlush();
}

void spinFunction()
{
	theta[axis] += 0.002;
	if (theta[axis] > 360.0)
	{
		theta[axis] -= 360.0;
	}
	glutPostRedisplay();
}

void mouseFunction(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		axis = 0;
	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		axis = 1;
	}
	if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN)
	{
		axis = 2;
	}
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Spinning cube");
	myInit();
	glutDisplayFunc(displayFunction);
	glutMouseFunc(mouseFunction);
	glutReshapeFunc(reshapeFunction);
	glutIdleFunc(spinFunction);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, vertices);
	glColorPointer(3, GL_FLOAT, 0, colors);
	glEnable(GL_DEPTH_TEST);
	glutMainLoop();
}