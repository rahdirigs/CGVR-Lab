#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <cmath>
#include <iostream>

using namespace std;

int mode;
int num_circles;
int xc, yc, r;
int x2, y2;
int flag;

void plot_points(int h, int k, int x, int y) {
  glColor3f(1.0, 0.0, 0.0);
  glBegin(GL_POINTS);
  glVertex2i(x + h, y + k);
  glVertex2i(-x + h, y + k);
  glVertex2i(-x + h, -y + k);
  glVertex2i(x + h, -y + k);
  glEnd();
}

void draw_circle() {
  int p = 3 - 2 * r;
  int x = 0, y = r;
  while (y > x) {
    plot_points(xc, yc, x, y);
    plot_points(xc, yc, y, x);
    if (p > 0) {
      --y;
      p += 4 * (x - y) + 10;
    } else {
      p += 4 * x + 6;
    }
    ++x;
  }
  plot_points(xc, yc, x, y);
  plot_points(xc, yc, y, x);
}

void mouse_function(int button, int state, int x, int y) {
  if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
    if (flag == 0) {
      xc = x;
      yc = 500 - y;
      cout << "Defining center (xc, yc) as (" << xc << ", " << yc << ")\n";
    } else {
      x2 = x;
      y2 = 500 - y;
      int r2 = (x2 - xc) * (x2 - xc) + (y2 - yc) * (y2 - yc);
      r = (int) sqrt(r2);
      cout << "Defining radius as " << r << "pixels\n";
      draw_circle();
      glFlush();
    }
    flag ^= 1;
  }
}

void mouse_display() {
}

void keyboard_display() {
  cout << "Enter the number of circles: ";
  cin >> num_circles;
  for (int i = 0; i < num_circles; ++i) {
    cout << "Enter the center of circle " << i << ": ";
    cin >> xc >> yc;
    cout << "Enter its radius: ";
    cin >> r;
    draw_circle();
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
  glutCreateWindow("Bressenham's Circle Drawing");
  my_init();
  cout << "Enter the input mode:\n1. Keyboard\n2. Mouse\n";
  cin >> mode;
  switch (mode) {
    case 1:
      glutDisplayFunc(keyboard_display);
      break;
    case 2:
      glutMouseFunc(mouse_function);
      glutDisplayFunc(mouse_display);
      break;
    default:
      cout << "Invalid choice...\n";
      return 0;
  }
  glutMainLoop();
  return 0;
}