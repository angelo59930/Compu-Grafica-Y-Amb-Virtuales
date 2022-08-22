#include <stdio.h>
#include <iostream>

#include <GL/glu.h>
#include <GL/glut.h>

// Vector de 2 dimensiones
struct vector2d
{
  float x, y;
};

// Funcion recursiva para armar el triangulo del buen señor con apellido dificil
void Sierpinski(int n, struct vector2d T1, struct vector2d T2, struct vector2d T3)
{
  if (n == 0)
    return;

  struct vector2d P1 = {(T1.x + T2.x) / 2, (T1.y + T2.y) / 2},
                  P2 = {(T1.x + T3.x) / 2, (T1.y + T3.y) / 2},
                  P3 = {(T2.x + T3.x) / 2, (T2.y + T3.y) / 2};

  // Dibujamos el nuevo triangulo
  glBegin(GL_LINE_STRIP);

  glVertex2d(P1.x, P1.y);
  glVertex2d(P2.x, P2.y);
  glVertex2d(P3.x, P3.y);
  glVertex2d(P1.x, P1.y);

  glEnd();

  n--;

  //  Llamada recursiva
  Sierpinski(n, T1, P1, P2);
  Sierpinski(n, P1, T2, P3);
  Sierpinski(n, P2, P3, T3);
}

//<<<<<<<<<<<<< Inicialización >>>>>>>>>>>>>
void iniciar(void)
{
  glClearColor(1.0, 1.0, 1.0, 0.0);
  glColor3f(0.0f, 0.0f, 0.0f);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0.0, 400, 0.0, 400);
}

//<<<<<<<<<<<<<<<<< Dibujado >>>>>>>>>>>>>>>>
void dibujar(void)
{
  // Malla de Sierpinski
  glClear(GL_COLOR_BUFFER_BIT);
  // Definimos el tamaño de los puntos
  glLineWidth(5);

  // Empezamos el dibujado de puntos
  glBegin(GL_LINE_STRIP);

  // Puntos iniciales
  struct vector2d T1 = {50, 100}, T2 = {200, 350}, T3 = {350, 100};

  // Dibujo del triangulo principal
  glVertex2d(T1.x, T1.y);
  glVertex2d(T2.x, T2.y);
  glVertex2d(T3.x, T3.y);
  glVertex2d(T1.x, T1.y);

  glEnd();

  Sierpinski(4, T1, T2, T3);

  glFlush();
}

//<<<<<<<<<<<<<<<<<<< main >>>>>>>>>>>>>>>>>>
int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(400, 400);
  glutInitWindowPosition(100, 150);
  glutCreateWindow("Ejercicio-3");
  glutDisplayFunc(dibujar);
  iniciar();
  glutMainLoop();

  return 0;
}