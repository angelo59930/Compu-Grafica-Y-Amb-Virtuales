#include <stdio.h>
#include <iostream>
#include <cmath>
#include <GL/glu.h>
#include <GL/glut.h>

#define WIDTH 400.0
#define HEIGTH 400.0

// Vector de 2 dimensiones
struct vector2d
{
  float x, y;
};

int tmp = 0;
struct vector2d vector1, vector2;

void paintPoint(vector2d ptm)
{
  // glPointSize(10);
  glBegin(GL_POINTS);
  glVertex2d(ptm.x, ptm.y);
  glEnd();
}

void puntoMedio(vector2d p1, vector2d p2)
{
  struct vector2d ptm;
  float m, t, dx, dy, p;
  if ((p2.x - p2.y) == 0)
    m = (p2.y - p1.y);
  else
    m = (p2.y - p1.y) / (p2.x - p1.x);

  if (fabs(m) < 1)
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

    dx = fabs(p2.x - p1.y);
    dy = fabs(p2.y - p1.y);
    p = 2 * dy - dx;
    ptm.x = p1.x;
    ptm.y = p1.y;

    while (ptm.x <= p2.x)
    {
      paintPoint(ptm);
      ptm.x++;
      if (p >= 0)
      {
        if (m < 1)
          ptm.y++;
        else
          ptm.y--;
        p = p + 2 * dy - 2 * dx;
      }
      else
      {
        p = p + 2 * dy;
      }
    }
  }

  if (fabs(m) >= 1)
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

    dx = fabs(p2.x - p1.y);
    dy = fabs(p2.y - p1.y);
    p = 2 * dy - dx;
    ptm.x = p1.x;
    ptm.y = p1.y;

    while (ptm.y <= p2.y)
    {
      paintPoint(ptm);
      ptm.y++;
      if (p >= 0)
      {
        if (m >= 1)
          ptm.x++;
        else
          ptm.x--;
        p = p + 2 * dx - 2 * dy;
      }
      else
      {
        p = p + 2 * dx;
      }
    }
  }
}

//<<<<<<<<<<<<< Inicialización >>>>>>>>>>>>>
void iniciar(void)
{
  glClearColor(1.0, 1.0, 1.0, 0.0);
  glMatrixMode(GL_PROJECTION);
  glColor3f(0.0f, 0.0f, 0.0f);
  glLoadIdentity();
  gluOrtho2D(0.0, WIDTH, 0.0, HEIGTH);
}

//<<<<<<<<<<<<<<<<< Dibujado >>>>>>>>>>>>>>>>
void dibujar(void)
{

  glClear(GL_COLOR_BUFFER_BIT);
  puntoMedio({2, 200}, {100, 300});
  glFlush();
}

//<<<<<<<<<<<<<<<<<<< main >>>>>>>>>>>>>>>>>>
int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(WIDTH, HEIGTH);
  glutInitWindowPosition(100, 150);
  glutCreateWindow("Ejercicio-3");
  glutDisplayFunc(dibujar);
  iniciar();
  glutMainLoop();

  return 0;
}
/**
 * @author Angelo59930
 *
 */