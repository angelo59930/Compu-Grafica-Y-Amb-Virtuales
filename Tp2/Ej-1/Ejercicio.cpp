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

void incremental(vector2d p0, vector2d p1)
{
  struct vector2d ptm;
  
  float m = (p1.y - p0.y) / (p1.x - p0.x);
  
  ptm = p0;
 
  glPointSize(2);
  glBegin(GL_POINTS);
  for (ptm.x; ptm.x < p1.x; ptm.x++)
  {
    glVertex2d(ptm.x, ptm.y);
    ptm.y = ptm.y + m;
  }
  glEnd();

}
//<<<<<<<<<<<<< Inicialización >>>>>>>>>>>>>
void iniciar(void)
{
  glClearColor(1, 1, 1, 1.0);
  glColor3f(0.0f, 0.0f, 0.0f);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0.0, WIDTH, 0.0, HEIGTH);
}

//<<<<<<<<<<<<<<<<< Dibujado >>>>>>>>>>>>>>>>
void dibujar(void)
{
  glClear(GL_COLOR_BUFFER_BIT);
  incremental({0,100},{200,300});
  glFlush();
}

//<<<<<<<<<<<<<<<<<<< main >>>>>>>>>>>>>>>>>>
int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(WIDTH, HEIGTH);
  glutInitWindowPosition(100, 150);
  glutCreateWindow("Ejercicio-1");
  glutDisplayFunc(dibujar);
  iniciar();
  glutMainLoop();

  return 0;
}
/**
 * @author Angelo59930
 *
 */