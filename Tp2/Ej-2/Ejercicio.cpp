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

int tmp =0;
struct vector2d vector1, vector2;

void paintPoint(vector2d ptm)
{
  //glPointSize(10);
  glBegin(GL_POINTS);
  glVertex2d(ptm.x, ptm.y);
  glEnd();
}

void puntoMedio(vector2d p0, vector2d p1)
{
  struct vector2d ptm = {p0.x, p0.y};

  if (ptm.x > p1.x || ((p0.x == p1.x) && (p0.y > p1.y)))
  {
    struct vector2d temp = ptm;
    ptm = p1;
    p1 = temp;
  }

  int d = 2 * (p1.y - ptm.y) - (p1.x - ptm.x);
  int incrE = 2 * (p1.y - ptm.y);
  int incrNE = 2 * ((p1.y - ptm.y) - (p1.x - ptm.x));

  paintPoint(ptm);

  while (ptm.x < p1.x)
  {
    if (d <= 0)
    {
      d = d + incrE;
    }
    else
    {
      d = d + incrNE;
      ptm.y++;
    }
    ptm.x++;
    paintPoint(ptm);
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
  puntoMedio({2,200}, {100, 300});
  glFlush();
}

void mouse(int button, int state, int x, int y)
{

  if (button == GLUT_LEFT_BUTTON)
  {
    if (state == GLUT_DOWN)
    {
      switch (tmp)
      {
      case 0:
          vector1 = {(float) x,(float) y};
          tmp++;
        break;
      
      case 1:
        vector2 = {(float)x, (float)y};
        puntoMedio(vector1,vector2);
        tmp = 0;
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
  glutDisplayFunc(dibujar);
  iniciar();
  glutMainLoop();

  return 0;
}
/**
 * @author Angelo59930
 *
 */