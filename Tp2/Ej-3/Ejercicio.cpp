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
int click = 0, firstPoint = 0;
struct vector2d P, Q, noseLlamarlo;

//<<<<<<<<<<<<< Inicialización >>>>>>>>>>>>>
void iniciar(void)
{
  glClearColor(1.0, 1.0, 1.0, 0.0);
  glMatrixMode(GL_PROJECTION);
  glColor3f(0.0f, 0.0f, 0.0f);
  glLoadIdentity();
  gluOrtho2D(0.0, WIDTH, 0.0, HEIGTH);
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

  glFlush();
}
void drawRectangle(vector2d P, vector2d Q)
{
  puntoMedio(P, {P.x, Q.y});
  puntoMedio({P.x, Q.y}, Q);
  puntoMedio(P, {Q.x, P.y});
  puntoMedio({Q.x, P.y}, Q);
}

//<<<<<<<<<<<<<<<<< Dibujado >>>>>>>>>>>>>>>>
void dibujar(void)
{

  glClear(GL_COLOR_BUFFER_BIT);

  glFlush();
}

void passiveMove(int x, int y)
{
  if (firstPoint == 1)
  {
    noseLlamarlo.x = x;
    noseLlamarlo.y = abs(y - HEIGTH);

    vector2d pAUX = {noseLlamarlo.x, noseLlamarlo.y};
    std::cout << "ptm.x: " << pAUX.x << " ptm.y: " << pAUX.y << std::endl;
    glClear(GL_COLOR_BUFFER_BIT);
    drawRectangle(P, pAUX);
  }
}

void mouse(int button, int state, int x, int y)
{
  if (button == GLUT_LEFT_BUTTON)
  {
    if (state == GLUT_DOWN)
    {
      switch (click)
      {
      case 0:
        P.x = x;
        P.y = abs(y - HEIGTH);
        std::cout << "P.x: " << P.x << " P.y: " << P.y << std::endl;
        paintPoint(P);
        firstPoint = 1;
        click++;
        break;
      case 1:
        Q.x = x;
        Q.y = abs(y - HEIGTH);
        // std::cout << "Q.x: " << Q.x << " Q.y: " << Q.y << std::endl;
        drawRectangle(P, Q);
        firstPoint = 0;
        click = 0;
        break;
      }
    }
  }
}

//<<<<<<<<<<<<<<<<<<< main >>>>>>>>>>>>>>>>>>
int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(WIDTH, HEIGTH);
  glutInitWindowPosition(100, 150);
  glutCreateWindow("Ejercicio-3");
  glutMouseFunc(mouse);
  glutPassiveMotionFunc(passiveMove);
  glutDisplayFunc(dibujar);
  iniciar();
  glutMainLoop();

  return 0;
}
/**
 * @author Angelo59930
 *
 */