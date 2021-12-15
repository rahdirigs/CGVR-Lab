#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>

using namespace std;

int xmin, ymin, xmax, ymax;
int xvmin, yvmin, xvmax, yvmax;
int n;

struct LineSegment {
  int x1, y1, x2, y2;
};

LineSegment ls[10];

bool test(double p, double q, double *t1, double *t2) {
  double r;
  if (p) {
    r = q / p;
  }
  if (p < 0.0) {
    if (r > *t1) {
      *t1 = r;
    }
    if (r > *t2) {
      return false;
    }
  } else if (p > 0.0) {
    if (r < *t2) {
      *t2 = r;
    }
    if (r < *t1) {
      return false;
    }
  } else {
    if (q < 0.0) {
      return false;
    }
  }
  return true;
}

void liang_barsky(double x1, double y1, double x2, double y2) {
  double dx = x2 - x1;
  double dy = y2 - y1;
  double t1 = 0.0;
  double t2 = 1.0;
  if (test(-dx, x1 - xmin, &t1, &t2)) {
    if (test(dx, xmax - x1, &t1, &t2)) {
      if (test(-dy, y1 - ymin, &t1, &t2)) {
        if (test(dy, ymax - y1, &t1, &t2)) {
          if (t1 > 0.0) {
            x1 = x1 + t1 * dx;
            y1 = y1 + t1 * dy;
          }
          if (t2 < 1.0) {
            x2 = x1 + t2 * dx;
            y2 = y1 + t2 * dy;
          }
          glColor3f(1.0, 0.0, 0.0);
          glBegin(GL_LINE_LOOP);
          glVertex2i(xvmin, yvmin);
          glVertex2i(xvmax, yvmin);
          glVertex2i(xvmax, yvmax);
          glVertex2i(xvmin, yvmax);
          glEnd();
          double sx = (double) (xvmax - xvmin) / (xmax - xmin);
          double sy = (double) (yvmax - yvmin) / (ymax - ymin);
          double xv1 = xvmin + sx * (x1 - xmin);
          double yv1 = yvmin + sy * (y1 - ymin);
          double xv2 = xvmin + sx * (x2 - xmin);
          double yv2 = yvmin + sy * (y2 - ymin);
          glColor3f(0.0, 0.0, 1.0);
          glBegin(GL_LINES);
          glVertex2f(xv1, yv1);
          glVertex2f(xv2, yv2);
          glEnd();
        }
      }
    }
  }
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(1.0, 0.0, 0.0);
  glBegin(GL_LINE_LOOP);
  glVertex2i(xmin, ymin);
  glVertex2i(xmax, ymin);
  glVertex2i(xmax, ymax);
  glVertex2i(xmin, ymax);
  glEnd();
  glColor3f(0.0, 0.0, 1.0);
  for (int i = 0; i < n; ++i) {
    glBegin(GL_LINES);
    glVertex2i(ls[i].x1, ls[i].y1);
    glVertex2i(ls[i].x2, ls[i].y2);
    glEnd();
  }
  for (int i = 0; i < n; ++i) {
    liang_barsky(ls[i].x1, ls[i].y1, ls[i].x2, ls[i].y2);
  }
  glFlush();
}

void my_init() {
  glClearColor(1.0, 1.0, 1.0, 1.0);
  gluOrtho2D(0, 500, 0, 500);
}

int main(int argc, char **argv) {
  cout << "Enter the window endpoints co-ordinates:\n";
  cin >> xmin >> ymin >> xmax >> ymax;
  cout << "Enter the viewport endpoints co-ordinates:\n";
  cin >> xvmin >> yvmin >> xvmax >> yvmax;
  cout << "Enter the number of lines: ";
  cin >> n;
  for (int i = 0; i < n; ++i) {
    cout << "Enter the endpoints of line " << i + 1 << ":\n";
    cin >> ls[i].x1 >> ls[i].y1 >> ls[i].x2 >> ls[i].y2;
  }
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(500, 500);
  glutInitWindowPosition(100, 100);
  glutCreateWindow("Liang-Barsky Line Clipping");
  my_init();
  glutDisplayFunc(display);
  glutMainLoop();
  return 0;
}