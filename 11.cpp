#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <cmath>
#include <iostream>

using namespace std;

const float DEG = 180.0 / 3.14159;

int angle;
float m, c, theta;

float house[11][2] = {
  {100, 200}, {200, 250}, {300, 200}, {100, 200},
  {100, 100}, {175, 100}, {175, 150}, {225, 150},
  {225, 100}, {300, 100}, {300, 200}
};

void my_init() {
  glClearColor(1.0, 1.0, 1.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(-450, 450, -450, 450);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void normal_house() {
  glBegin(GL_LINE_LOOP);
  for (int i = 0; i < 11; ++i) {
    glVertex2fv(house[i]);
  }
  glEnd();
  glFlush();
}

void rotate_house() {
  my_init();
  glColor3f(1.0, 0.0, 0.0);
  normal_house();
  glPushMatrix();
  glTranslatef(100, 100, 0);
  glRotatef(angle, 0, 0, 1);
  glTranslatef(-100, -100, 0);
  glColor3f(0.0, 0.0, 1.0);
  normal_house();
}

void reflect_house() {
  my_init();
  glColor3f(1.0, 0.0, 0.0);
  normal_house();
  float x1 = 0, x2 = 500;
  float y1 = m * x1 + c;
  float y2 = m * x2 + c;
  glColor3f(0.0, 1.0, 0.0);
  glBegin(GL_LINES);
  glVertex2f(x1, y1);
  glVertex2f(x2, y2);
  glEnd();
  glPushMatrix();
  glTranslatef(0, c, 0);
  theta = atan(m);
  theta *= DEG;
  glRotatef(theta, 0, 0, 1);
  glScalef(1, -1, 1);
  glRotatef(-theta, 0, 0, 1);
  glTranslatef(0, -c, 0);
  glColor3f(0.0, 0.0, 1.0);
  normal_house();
}

void mouse_function(int button, int state, int x, int y) {
  if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
    rotate_house();
  }
  if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
    reflect_house();
  }
}

int main(int argc, char **argv) {
  cout << "Enter the angle of rotation: ";
  cin >> angle;
  cout << "Enter the 'm' and 'c' valuefor the line: ";
  cin >> m >> c;
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(500, 500);
  glutInitWindowPosition(100, 100);
  glutCreateWindow("House");
  glutDisplayFunc(rotate_house);
  glutMouseFunc(mouse_function);
  glutMainLoop();
  return 0;
}