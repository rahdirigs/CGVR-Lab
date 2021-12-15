#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
#include <ctime>

using namespace std;

float vertices[] = {
  1, 1, 1,
  1, 1, -1,
  -1, 1, 1,
  -1, 1, -1,
  1, -1, 1,
  1, -1, -1,
  -1, -1, 1,
  -1, -1, -1
};

float colors[] = {
  1, 0, 0,
  0, 1, 0,
  0, 0, 1,
  1, 1, 0,
  0, 1, 1,
  1, 0, 1,
  0, 0, 0,
  1, 1, 1
};

GLubyte indices[] = {
  0, 2, 6, 4,
  1, 3, 7, 5,
  0, 1, 5, 4,
  2, 3, 7, 6,
  2, 3, 1, 0,
  6, 7, 5, 4
};

float theta[3] = {0.0, 0.0, 0.0};
int axis;

void display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glRotatef(theta[0], 1, 0, 0);
  glRotatef(theta[1], 0, 1, 0);
  glRotatef(theta[2], 0, 0, 1);
  glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, indices);
  glColor3f(0.0, 0.0, 0.0);
  glBegin(GL_LINES);
  glVertex3f(0.0, 0.0, 0.0);
  glVertex3f(1.0, 1.0, 1.0);
  glEnd();
  glFlush();
}

void delay(float secs) {
  float end = clock() / CLOCKS_PER_SEC + secs;
  while ((clock() / CLOCKS_PER_SEC) < end);
}

void spin_function() {
  delay(0.02);
  theta[axis] += 2.0;
  if (theta[axis] > 360.0) {
    theta[axis] -= 360.0;
  }
  glutPostRedisplay();
}

void mouse_function(int button, int state, int x, int y) {
  if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
    axis = 0;
  }
  if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) {
    axis = 1;
  }
  if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
    axis = 2;
  }
}

void reshape_function(int w, int h) {
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  if (w <= h) {
    glOrtho(-2.0, 2.0, -2.0 * (float) h / w, 2.0 * (float) h / w, -10.0, 10.0);
  } else {
    glOrtho(-2.0 * (float) w / h, 2.0 * (float) w / h, -2.0, 2.0, -10.0, 10.0);
  }
  glMatrixMode(GL_MODELVIEW);
}

void my_init() {
  glClearColor(1.0, 1.0, 1.0, 1.0);
  glOrtho(-2.0, 2.0, -2.0, 2.0, -10.0, 10.0);
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(500, 500);
  glutInitWindowPosition(100, 100);
  glutCreateWindow("Spinning cube");
  my_init();
  glutDisplayFunc(display);
  glutMouseFunc(mouse_function);
  glutIdleFunc(spin_function);
  glutReshapeFunc(reshape_function);
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_COLOR_ARRAY);
  glVertexPointer(3, GL_FLOAT, 0, vertices);
  glColorPointer(3, GL_FLOAT, 0, colors);
  glEnable(GL_DEPTH_TEST);
  glutMainLoop();
  return 0;
}
