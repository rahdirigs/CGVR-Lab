#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
#include <ctime>

using namespace std;

float db;
float angle = 0.0;

void display_single() {
  glClear(GL_COLOR_BUFFER_BIT);
  glBegin(GL_POLYGON);
  glColor3f(1.0, 0.0, 0.0);
  glVertex2d(1.0, 1.0);
  glColor3f(0.0, 1.0, 0.0);
  glVertex2d(-1.0, 1.0);
  glColor3f(0.0, 0.0, 1.0);
  glVertex2d(-1.0, -1.0);
  glColor3f(1.0, 1.0, 0.0);
  glVertex2d(1.0, -1.0);
  glEnd();
  glFlush();
}

void display_double() {
  glClear(GL_COLOR_BUFFER_BIT);
  glRotatef(angle, 0, 0, 1);
  glBegin(GL_POLYGON);
  glColor3f(1.0, 0.0, 0.0);
  glVertex2d(1.0, 1.0);
  glColor3f(0.0, 1.0, 0.0);
  glVertex2d(-1.0, 1.0);
  glColor3f(0.0, 0.0, 1.0);
  glVertex2d(-1.0, -1.0);
  glColor3f(1.0, 1.0, 0.0);
  glVertex2d(1.0, -1.0);
  glEnd();
  glutSwapBuffers();
}

void spin_function() {
  angle += 0.002;
  if (angle > 360) {
    angle -= 360;
  }
  glutPostRedisplay();
}

void mouse_function(int button, int state, int x, int y) {
  if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
    glutIdleFunc(spin_function);
  }
  if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
    glutIdleFunc(NULL);
  }
}

void reshape_function(int w, int h) {
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  if (w <= h) {
    gluOrtho2D(-2.0, 2.0, -2.0 * (float) h / w, 2.0 * (float) h / w);
  } else {
    gluOrtho2D(-2.0 * (float) w / h, 2.0 * (float) w / h, -2.0, 2.0);
  }
  glMatrixMode(GL_MODELVIEW);
}

void my_init() {
  glClearColor(1.0, 1.0, 1.0, 1.0);
  gluOrtho2D(-2.0, 2.0, -2.0, 2.0);
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(500, 500);
  glutInitWindowPosition(100, 100);
  glutCreateWindow("Single Buffer");
  my_init();
  glutDisplayFunc(display_single);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(500, 500);
  glutInitWindowPosition(700, 700);
  db = glutCreateWindow("Double Buffer");
  my_init();
  glutDisplayFunc(display_double);
  glutMouseFunc(mouse_function);
  glutIdleFunc(spin_function);
  glutReshapeFunc(reshape_function);
  glutMainLoop();
  return 0;
}