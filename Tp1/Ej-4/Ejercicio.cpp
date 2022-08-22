#include <stdio.h>
#include <iostream>
#include <cmath>
#include <GL/glu.h>
#include <GL/glut.h>

#define WIDTH 400.0
#define HEIGTH 400.0

using namespace std;

struct vector2d
{
  float x, y;
};

double f(double x){
  return exp(x) * cos(2 * M_PI * x);
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


  // Malla de Sierpinski
  glClear(GL_COLOR_BUFFER_BIT);
  // Definimos el tamaño de los puntos
  glLineWidth(2);

  glBegin(GL_LINE_STRIP);
  glVertex2d(0, HEIGTH/2);
  glVertex2d(WIDTH, HEIGTH / 2);
  glEnd();

  while (x <= 4.001)
  {
    glPointSize(2);
    glBegin(GL_POINTS);
    glVertex2d(x, f(-x) + (HEIGTH / 2));
    glEnd();
    x += 0.001;
  }
  
  

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