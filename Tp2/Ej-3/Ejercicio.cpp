#include <stdio.h>
#include <iostream>
#include <cmath>
#include <GL/glu.h>
#include <GL/glut.h>

#define WIDTH 400.0
#define HEIGTH 400.0

struct punto {
  float x, y;
};

bool flag = true;
punto P, Q, puntoTemporal;

void iniciar(void)
{
  glClearColor(1.0, 1.0, 1.0, 0.0);
  glMatrixMode(GL_PROJECTION);
  glColor3f(0.0f, 0.0f, 0.0f);
  glLoadIdentity();
  gluOrtho2D(0.0, WIDTH, 0.0, HEIGTH);
<<<<<<< HEAD
}

void paintPoint(vector2d ptm)
{
  glPointSize(10);
  glBegin(GL_POINTS);
  glVertex2d(ptm.x, ptm.y);
  glEnd();
}

void puntoMedio(vector2d p1, vector2d p2)
{
  GLfloat M, p, dx, dy, t;
  vector2d ptm;

  if ((p2.x - p1.x) == 0)
    M = (p2.y - p1.y);
  else
    M = (p2.y - p1.y) / (p2.x - p2.y);

  if (fabs(M) < 1)
  {
    if (p1.x > p2.x)
    {
      t = p1.x;
      p1.x = p2.x;
      p2.x = t;

      t = p1.y;
      p1.y = p2.y;
      p2.y = t;
    }

    dx = fabs(p2.x - p1.x);
    dy = fabs(p2.y - p1.y);

    p = 2 * dy - dx;

    ptm.x = p1.x;
    ptm.y = p1.y;

    while (ptm.x <= p2.x)
    {
      paintPoint(ptm);
      ptm.x += 1;

      if (p >= 0)
      {
        if (M < 1)
          ptm.y += 1;
        else
          ptm.y -= 1;
        p = p + 2 * dy - 2 * dx;
      }
      else
        p = p + 2 * dy;
    }
  }

  if (fabs(M) >= 1)
  {
    if (p1.y > p2.y)
    {
      t = p1.x;
      p1.x = p2.x;
      p2.x = t;

      t = p1.y;
      p1.y = p2.y;
      p2.y = t;
    }

    dx = fabs(p2.x - p1.x);
    dy = fabs(p2.y - p1.y);

    p = 2 * dx - dy;

    ptm.x = p1.x;
    ptm.y = p1.y;

    while (ptm.y <= p2.y)
    {
      paintPoint(ptm);
      ptm.y += 1;

      if (p >= 0)
      {
        if (M >= 1)
          ptm.x += 1;
        else
          ptm.x -= 1;
        p = p + 2 * dx - 2 * dy;
      }
      else
        p = p + 2 * dx;
    }
  }

=======
  glClear(GL_COLOR_BUFFER_BIT);
>>>>>>> e098162ad28ac6a49ae32dbf979a60eca50b1dc3
  glFlush();
}

void draw(punto point)
{
  glPointSize(3);
  glBegin(GL_POINTS);
  glVertex2d(point.x, point.y);
  glEnd();
}

void puntoMedio(punto p1, punto p2)
{
  GLfloat M, p, dx, dy;
  punto point, t; 

  if ((p2.x - p1.x) == 0){
    M = (p2.y - p1.y);
  }
  else {
    M = (p2.y - p1.y) / (p2.x - p2.y);
  }

  if (fabs(M) < 1) {
    if (p1.x > p2.x) {
      t = p1;
      p1 = p2;
      p2 = t;
    }

    dx = fabs(p2.x - p1.x);
    dy = fabs(p2.y - p1.y);

    p = 2 * dy - dx;

    point.x = p1.x;
    point.y = p1.y;

    while (point.x <= p2.x) {
      draw(point);
      point.x += 1;

      if (p >= 0){
        point.y = (M < 1) ? point.y += 1 : point.y -= 1;
        p = p + 2 * dy - 2 * dx; 
      }else{
        p = p + 2 * dy;
      }
    }
  }

  if (fabs(M) >= 1) {
    if (p1.y > p2.y) {
      t = p1;
      p1 = p2;
      p2 = t;
    }

    dx = fabs(p2.x - p1.x);
    dy = fabs(p2.y - p1.y);

    p = 2 * dx - dy;

    point.x = p1.x;
    point.y = p1.y;

    while (point.y <= p2.y){
      draw(point);
      point.y += 1;

    if (p >= 0){
      point.x = (M >= 0) ? point.x += 1 : point.x -= 1;
      p = p + 2 * dx - 2 * dy; 
    }else{
      p = p + 2 * dx;
    }
  }
}
  glFlush();
}
void drawRectangle(punto P, punto Q)
{
  puntoMedio(P, {P.x, Q.y});
  puntoMedio({P.x, Q.y}, Q);
  puntoMedio(P, {Q.x, P.y});
  puntoMedio({Q.x, P.y}, Q);
}

void passiveMotionFunc(int x, int y)
{
  if (!flag) {
    glClear(GL_COLOR_BUFFER_BIT);
    drawRectangle(P, {float (x), float (abs(y - HEIGTH))});
  }
}

void mouse(int button, int state, int x, int y) {
  if (button == GLUT_LEFT_BUTTON) {
    if (state == GLUT_DOWN) {

      if(flag){
        P = {float (x), float(abs(y - HEIGTH))};
        draw(P);
        flag = !flag;
      }else{
        Q = {float (x), float(abs(y - HEIGTH))};
        drawRectangle(P, Q);
        flag = !flag;
      }
    }
  }
}

int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(WIDTH, HEIGTH);
  glutInitWindowPosition(100, 150);
  glutCreateWindow("Cuadradito");
  glutMouseFunc(mouse);
  glutPassiveMotionFunc(passiveMotionFunc);
  iniciar();
  glutMainLoop();

  return 0;
}