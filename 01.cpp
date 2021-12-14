#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>

using namespace std;

int mode;
int num_lines;
int x1, y1, x2, y2;
int flag = 0;

void plot_pixel(int x, int y) {
  glColor3f(1.0, 0.0, 0.0);
  glBegin(GL_POINTS);
  glVertex2i(x, y);
  glEnd();
}

void draw_line() {
  int dx, dy, p;
  int incx, incy, delta1, delta2;
  int x, y;
  dx = x1 - x2;
  dy = y1 - y2;
  if (dx < 0) {
    dx = -dx;
  }
  if (dy < 0) {
    dy = -dy;
  }
  incx = x2 > x1 ? 1 : -1;
  incy = y2 > y1 ? 1 : -1;
  x = x1;
  y = y1;
  plot_pixel(x, y);
  if (dx > dy) {
    p = 2 * dy - dx;
    delta1 = 2 * (dy - dx);
    delta2 = 2 * dy;
    for (int i = 0; i < dx; ++i) {
      if (p > 0) {
        y += incy;
        p += delta1;
      } else {
        p += delta2;
      }
      x += incx;
      plot_pixel(x, y);
    }
  } else {
    p = 2 * dx - dy;
    delta1 = 2 * (dx - dy);
    delta2 = 2 * dx;
    for (int i = 0; i < dy; ++i) {
      if (p > 0) {
        x += incx;
        p += delta1;
      } else {
        p += delta2;
      }
      y += incy;
      plot_pixel(x, y);
    }
  }
}

void mouse_function(int button, int state, int x, int y) {
  if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
    if (flag == 0) {
      x1 = x;
      y1 = 500 - y;
      cout << "Defined (x1, y1) for the line as (" << x1 << ", " << y1 << ")\n";
    } else {
      x2 = x;
      y2 = 500 - y;
      cout << "Defined (x2, y2) for the line as (" << x2 << ", " << y2 << ")\n";
      draw_line();
      glFlush();
    }
    flag ^= 1;
  }
}

void mouse_display() {
}

void keyboard_display() {
  cout << "Enter the number of lines: ";
  cin >> num_lines;
  for (int i = 1; i <= num_lines; ++i) {
    cout << "Enter one end of line " << i << ": ";
    cin >> x1 >> y1;
    cout << "Enter the second end of line " << i << ": ";
    cin >> x2 >> y2;
    draw_line();
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
  glutCreateWindow("Bressenham's Line Drawing Algorithm");
  my_init();
  cout << "Enter the mode of input\n1. Keyboard\n2. Mouse\n";
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
      cout << "Invalid choice....\n";
      return 0;
  }
  glutMainLoop();
  return 0;
}
