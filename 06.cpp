#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <cmath>
#include <iostream>

using namespace std;

const float RAD = 3.14159 / 180.0;

void reshape_function(int w, int h) {
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  if (w <= h) {
    glOrtho(-2.0, 2.0, -2.0 * (float) h / (float) w, 2.0 * (float) h / (float) w, -2.0, 2.0);
  } else {
    glOrtho(-2.0 * (float) w / (float) h, 2.0 * (float) w / (float) h, -2.0, 2.0, -2.0, 2.0);
  }
  glTranslatef(0, 0, -1);
  glRotatef(-45, 0, 1, 0);
  glMatrixMode(GL_MODELVIEW);
  glutPostRedisplay();
}

void display_sphere() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  float x, y, z, phi, phir, phir20, theta, thetar;
  for (phi = -80.0; phi <= 80.0; phi += 20.0) {
    phir = phi * RAD;
    phir20 = (phi + 20.0) * RAD;
    glBegin(GL_QUAD_STRIP);
    for (theta = -180.0; theta <= 180.0; theta += 20.0) {
      thetar = theta * RAD;
      x = sin(thetar) * cos(phir);
      y = cos(thetar) * cos(phir);
      z = sin(phir);
      glVertex3d(x, y, z);
      x = sin(thetar) * cos(phir20);
      y = cos(thetar) * cos(phir20);
      z = sin(phir20);
      glVertex3d(x, y, z);
    }
    glEnd();
  }
  float c80 = 80.0 * RAD;
  z = sin(c80);
  glBegin(GL_TRIANGLE_FAN);
  glVertex3d(0, 0, 1);
  for (theta = -180.0; theta <= 180.0; theta += 20.0) {
    thetar = theta * RAD;
    x = sin(thetar) * cos(c80);
    y = cos(thetar) * cos(c80);
    glVertex3d(x, y, z);
  }
  glEnd();
  z = -sin(c80);
  glBegin(GL_TRIANGLE_FAN);
  glVertex3d(0, 0, -1);
  for (theta = -180.0; theta <= 180.0; theta += 20.0) {
    thetar = theta * RAD;
    x = sin(thetar) * cos(c80);
    y = cos(thetar) * cos(c80);
    glVertex3d(x, y, z);
  }
  glEnd();
  glFlush();
}

void my_init() {
  glClearColor(1.0, 1.0, 1.0, 1.0);
  glColor3f(0.0, 0.0, 1.0);
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(500, 500);
  glutInitWindowPosition(100, 100);
  glutCreateWindow("Sphere");
  my_init();
  glutDisplayFunc(display_sphere);
  glutReshapeFunc(reshape_function);
  glEnable(GL_DEPTH_TEST);
  glutMainLoop();
  return 0;
}
