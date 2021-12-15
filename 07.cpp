#include <algorithm>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
#include <ctime>

using namespace std;

const int MAXN = 110;

int n;
float x[MAXN], y[MAXN];
int m = 0;
float intx[MAXN] = {0};

void delay(float secs) {
  clock_t end = clock() / CLOCKS_PER_SEC + secs;
  while ((clock() / CLOCKS_PER_SEC) < end);
}

void draw_line(float x1, float x2, float y_common) {
  delay(0.2);
  glColor3f(1.0, 1.0, 0.0);
  glBegin(GL_LINES);
  glVertex2f(x1, y_common);
  glVertex2f(x2, y_common);
  glEnd();
}

void detect_edge(float x1, float y1, float x2, float y2, int line) {
  if (y2 < y1) {
    swap(y1, y2);
    swap(x1, x2);
  }
  if (line > y1 && line < y2) {
    intx[m] = x1 + (x2 - x1) * (line - y1) / (y2 - y1);
    ++m;
  }
}

void scanline_polyfill() {
  for (int i = 0; i < 500; ++i) {
    m = 0;
    for (int j = 0; j < n; ++j) {
      detect_edge(x[j], y[j], x[(j + 1) % n], y[(j + 1) % n], i);
    }
    sort(intx, intx + m);
    if (m >= 2) {
      for (int j = 0; j < m; j += 2) {
        draw_line(intx[j], intx[j + 1], i);
      }
    }
  }
}

void display_fill() {
  glClear(GL_COLOR_BUFFER_BIT);
  glLineWidth(2.0);
  glBegin(GL_LINE_LOOP);
  for (int i = 0; i < n; ++i) {
    glVertex2f(x[i], y[i]);
  }
  glEnd();
  scanline_polyfill();
  glFlush();
}

void my_init() {
  glClearColor(1.0, 1.0, 1.0, 1.0);
  glColor3f(0.0, 0.0, 1.0);
  glPointSize(1.0);
  gluOrtho2D(0, 500, 0, 500);
}

int main(int argc, char **argv) {
  cout << "Enter the number of vertices in the polygon: ";
  cin >> n;
  for (int i = 0; i < n; ++i) {
    cout << "Enter vertex " << i + 1 << ": ";
    cin >> x[i] >> y[i];
  }
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(500, 500);
  glutInitWindowPosition(100, 100);
  glutCreateWindow("Scanline Polygon Filling");
  my_init();
  glutDisplayFunc(display_fill);
  glutMainLoop();
  return 0;
}