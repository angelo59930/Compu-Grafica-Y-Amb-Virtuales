#include <stdio.h>
#include <iostream>
#include <cmath>
#include <GL/glu.h>
#include <GL/glut.h>

#define WIDTH 500.0
#define HEIGTH 500.0

using namespace std;

struct vector2d
{
  float x, y;
};

double f(double x)
{
  return exp(-x) * cos(2 * M_PI * x);
}

//<<<<<<<<<<<<< Inicialización >>>>>>>>>>>>>
void iniciar(void)
{
  glClearColor(1.0, 1.0, 1.0, 0.0);
  glColor3f(0.0f, 0.0f, 0.0f);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0.0, WIDTH, 0.0, HEIGTH);
}

//<<<<<<<<<<<<<<<<< Dibujado >>>>>>>>>>>>>>>>
void dibujar(void)
{
  double x = 0.0;

  glClear(GL_COLOR_BUFFER_BIT);
  // Definimos el tamaño de los puntos
  glLineWidth(2);

  glBegin(GL_LINE_STRIP);
  glVertex2d(0, HEIGTH / 2);
  glVertex2d(WIDTH, HEIGTH / 2);
  glEnd();

  /*
   * En eje y -> 1  = 400dpx
   * En eje y -> 0  = 200dpx
   * En eje y -> -1 = 0dpx
   *
   * En eje x -> 4 = 0dpx
   * En eje x -> 4 = 400dpx
   *
   */

  glPointSize(4);
  glBegin(GL_POINTS);
  while (x <= 4.0)
  {
    double y = f(x) / (1 / (HEIGTH / 2)) + (HEIGTH / 2);

    glVertex2d(x/(4/WIDTH) , y);

    x += 0.005;
  }
  glEnd();

  glFlush();
}

//<<<<<<<<<<<<<<<<<<< main >>>>>>>>>>>>>>>>>>
int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(WIDTH, HEIGTH);
  glutInitWindowPosition(100, 150);
  glutCreateWindow("Ejercicio-4");
  glutDisplayFunc(dibujar);
  iniciar();
  glutMainLoop();

  return 0;
}
/**
 * @author Angelo59930
 *
 */