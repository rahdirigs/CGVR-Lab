#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>

using namespace std;

const int MAXN = 20;

int poly_size;
int polygon[MAXN][2];
int clipper_size;
int clipper[MAXN][2];
int new_poly_size;
int new_polygon[MAXN][2];

void draw_polygon(int p[][2], int size) {
  glBegin(GL_POLYGON);
  for (int i = 0; i < size; ++i) {
    glVertex2d(p[i][0], p[i][1]);
  }
  glEnd();
}

int x_intersect(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4) {
  int num = (x1 * y2 - x2 * y1) * (x3 - x4) - (x3 * y4 - x4 * y3) * (x1 - x2);
  int den = (x1 - x2) * (y3 - y4) - (x3 - x4) * (y1 - y2);
  return num / den;
}

int y_intersect(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4) {
  int num = (x1 * y2 - x2 * y1) * (y3 - y4) - (x3 * y4 - x4 * y3) * (y1 - y2);
  int den = (x1 - x2) * (y3 - y4) - (x3 - x4) * (y1 - y2);
  return num / den;
}

void clip(int x1, int y1, int x2, int y2) {
  new_poly_size = 0;
  for (int i = 0; i < poly_size; ++i) {
    int k = (i + 1) % poly_size;
    int ix = polygon[i][0], iy = polygon[i][1];
    int kx = polygon[k][0], ky = polygon[k][1];
    int i_pos = (x2 - x1) * (iy - y1) - (y2 - y1) * (ix - x1);
    int k_pos = (x2 - x1) * (ky - y1) - (y2 - y1) * (kx - x1);
    if (i_pos >= 0 && k_pos >= 0) {
      new_polygon[new_poly_size][0] = kx;
      new_polygon[new_poly_size][1] = ky;
      ++new_poly_size;
    } else if (i_pos < 0 && k_pos >= 0) {
      new_polygon[new_poly_size][0] = x_intersect(x1, y1, x2, y2, ix, iy, kx, ky);
      new_polygon[new_poly_size][1] = y_intersect(x1, y1, x2, y2, ix, iy, kx, ky);
      ++new_poly_size;
      new_polygon[new_poly_size][0] = kx;
      new_polygon[new_poly_size][1] = ky;
      ++new_poly_size;
    } else if (i_pos >= 0 && k_pos < 0) {
      new_polygon[new_poly_size][0] = x_intersect(x1, y1, x2, y2, ix, iy, kx, ky);
      new_polygon[new_poly_size][1] = y_intersect(x1, y1, x2, y2, ix, iy, kx, ky);
      ++new_poly_size;
    }
  }
  poly_size = new_poly_size;
  for (int i = 0; i < poly_size; ++i) {
    polygon[i][0] = new_polygon[i][0];
    polygon[i][1] = new_polygon[i][1];
  }
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(1.0, 0.0, 0.0);
  draw_polygon(clipper, clipper_size);
  glColor3f(0.0, 1.0, 0.0);
  draw_polygon(polygon, poly_size);
  for (int i = 0; i < clipper_size; ++i) {
    int k = (i + 1) % clipper_size;
    clip(clipper[i][0], clipper[i][1], clipper[k][0], clipper[k][1]);
  }
  glColor3f(0.0, 0.0, 1.0);
  draw_polygon(polygon, poly_size);
  glFlush();
}

void my_init() {
  glClearColor(1.0, 1.0, 1.0, 1.0);
  gluOrtho2D(0, 500, 0, 500);
}

int main(int argc, char **argv) {
  cout << "Enter the number of vertices in the polygon: ";
  cin >> poly_size;
  for (int i = 0; i < poly_size; ++i) {
    cout << "Enter the vertex " << i + 1 << " of the polygon:\n";
    cin >> polygon[i][0] >> polygon[i][1];
  }
  cout << "Enter the number of vertices of the clipping window: ";
  cin >> clipper_size;
  for (int i = 0; i < clipper_size; ++i) {
    cout << "Enter the vertex " << i + 1 << " of the clipping window:\n";
    cin >> clipper[i][0] >> clipper[i][1];
  }
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(500, 500);
  glutInitWindowPosition(100, 100);
  glutCreateWindow("Cohen-Hodgeman Polygon Clipping");
  my_init();
  glutDisplayFunc(display);
  glutMainLoop();
  return 0;
}