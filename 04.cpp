#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>

using namespace std;

void plot_pixels(int h, int k, int x, int y) {
  glColor3f(1.0, 0.0, 0.0);
  glBegin(GL_POINTS);
  glVertex2i(x + h, y + k);
  glVertex2i(-x + h, y + k);
  glVertex2i(-x + h, -y + k);
  glVertex2i(x + h, -y + k);
  glEnd();
}

void draw_circle(int xc, int yc, int r) {
  int p = 3 - 2 * r;
  int x = 0, y = r;
  while (y > x) {
    plot_pixels(xc, yc, x, y);
    plot_pixels(xc, yc, y, x);
    if (p > 0) {
      --y;
      p += 4 * (x - y) + 10;
    } else {
      p += 4 * x + 6;
    }
    ++x;
  }
  plot_pixels(xc, yc, x, y);
  plot_pixels(xc, yc, y, x);
  glFlush();
}

void displayCylinder() {
  int xc = 100, yc = 100, r = 50;
  int n = 200;
  for (int i = 0; i < n; i += 3) {
    draw_circle(xc, yc + i, r);
  }
}

void displayParallelopiped() {
  int x1 = 100, x2 = 350, y1 = 100, y2 = 250;
  glColor3f(0.0, 1.0, 0.0);
  for (int i = 0; i < 100; i += 2) {
    glBegin(GL_LINE_LOOP);
    glVertex2i(x1 + i, y1 + i);
    glVertex2i(x2 + i, y1 + i);
    glVertex2i(x2 + i, y2 + i);
    glVertex2i(x1 + i, y2 + i);
    glEnd();
    glFlush();
  }
}

void my_init() {
  glClearColor(1.0, 1.0, 1.0, 1.0);
  gluOrtho2D(0, 500, 0, 500);
  glClear(GL_COLOR_BUFFER_BIT);
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(500, 500);
  glutInitWindowPosition(100, 100);
  glutCreateWindow("Cylinder");
  my_init();
  glutDisplayFunc(displayCylinder);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(500, 500);
  glutInitWindowPosition(700, 700);
  glutCreateWindow("Parallelopiped");
  my_init();
  glutDisplayFunc(displayParallelopiped);
  glutMainLoop();
  return 0;
}