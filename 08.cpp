#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>

using namespace std;

int xmin, xmax, ymin, ymax;
int xvmin, xvmax, yvmin, yvmax;
int n;

struct LineSegment {
  int x1, y1, x2, y2;
};

LineSegment ls[10];

const int TOP = 1;
const int BOTTOM = 2;
const int RIGHT = 4;
const int LEFT = 8;

int compute_outcode(double x, double y) {
  int outcode = 0;
  if (y > ymax) {
    outcode |= TOP;
  }
  if (y < ymin) {
    outcode |= BOTTOM;
  }
  if (x > xmax) {
    outcode |= RIGHT;
  }
  if (x < xmin) {
    outcode |= LEFT;
  }
  return outcode;
}

void cohen_sutherland(double x1, double y1, double x2, double y2) {
  int outcode1 = compute_outcode(x1, y1);
  int outcode2 = compute_outcode(x2, y2);
  int cur_outcode;
  double x, y;
  bool done = false, accept = false;
  do {
    if (!(outcode1 | outcode2)) {
      accept = true;
      done = true;
    } else if (outcode1 & outcode2) {
      done = true;
    } else {
      cur_outcode = outcode1 ? outcode1 : outcode2;
      if (cur_outcode & TOP) {
        y = ymax;
        x = x1 + (ymax - y1) * (x2 - x1) / (y2 - y1);
      } else if (cur_outcode & BOTTOM) {
        y = ymin;
        x = x1 + (ymin - y1) * (x2 - x1) / (y2 - y1);
      } else if (cur_outcode & RIGHT) {
        x = xmax;
        y = y1 + (xmax - x1) * (y2 - y1) / (x2 - x1);
      } else {
        x = xmin;
        y = y1 + (xmin - x1) * (y2 - y1) / (x2 - x1);
      }
      if (cur_outcode == outcode1) {
        x1 = x;
        y1 = y;
        outcode1 = compute_outcode(x1, y1);
      } else {
        x2 = x;
        y2 = y;
        outcode2 = compute_outcode(x2, y2);
      }
    }
  } while (!done);
  if (accept) {
    double sx = (double) (xvmax - xvmin) / (xmax - xmin);
    double sy = (double) (yvmax - yvmin) / (ymax - ymin);
    double xv1 = xvmin + (x1 - xmin) * sx;
    double yv1 = yvmin + (y1 - ymin) * sy;
    double xv2 = xvmin + (x2 - xmin) * sx;
    double yv2 = xvmin + (y2 - ymin) * sy;
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINE_LOOP);
    glVertex2i(xvmin, yvmin);
    glVertex2i(xvmax, yvmin);
    glVertex2i(xvmax, yvmax);
    glVertex2i(xvmin, yvmax);
    glEnd();
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_LINES);
    glVertex2f(xv1, yv1);
    glVertex2f(xv2, yv2);
    glEnd();
  }
}

void display_lines() {
  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(0.0, 0.0, 1.0);
  glBegin(GL_LINE_LOOP);
  glVertex2d(xmin, ymin);
  glVertex2d(xmax, ymin);
  glVertex2d(xmax, ymax);
  glVertex2d(xmin, ymax);
  glEnd();
  for (int i = 0; i < n; ++i) {
    glBegin(GL_LINES);
    glVertex2d(ls[i].x1, ls[i].y1);
    glVertex2d(ls[i].x2, ls[i].y2);
    glEnd();
  }
  for (int i = 0; i < n; ++i) {
    cohen_sutherland(ls[i].x1, ls[i].y1, ls[i].x2, ls[i].y2);
  }
  glFlush();
}

void my_init() {
  glClearColor(1.0, 1.0, 1.0, 1.0);
  gluOrtho2D(0, 500, 0, 500);
  glPointSize(1.0);
}

int main(int argc, char **argv) {
  cout << "Enter the window co-ordinates endpoints:\n";
  cin >> xmin >> ymin >> xmax >> ymax;
  cout << "Enter the viewport co-ordinates endpoints:\n";
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
  glutCreateWindow("Cohen-Sutherland Line Clipping");
  my_init();
  glutDisplayFunc(display_lines);
  glutMainLoop();
  return 0;
}