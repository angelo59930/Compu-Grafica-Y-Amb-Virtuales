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

// --------------------Variables Globales---------------------------
// Puntos iniciales
struct vector2d T1 = {50, 100}, T2 = {200, 350}, T3 = {350, 100};
int tmp = 0, r = 0, g = 0, b = 0;

// -----------------------------------------------------------------

// Funcion recursiva para armar el triangulo del buen señor con apellido dificil
void Sierpinski(int n, struct vector2d T1, struct vector2d T2, struct vector2d T3)
{
  if (n == 0)
    return;

  struct vector2d P1 = {(T1.x + T2.x) / 2, (T1.y + T2.y) / 2},
                  P2 = {(T1.x + T3.x) / 2, (T1.y + T3.y) / 2},
                  P3 = {(T2.x + T3.x) / 2, (T2.y + T3.y) / 2};

  // Dibujamos el nuevo triangulo
  glBegin(GL_POINTS);

  glVertex2d(P1.x, P1.y);
  glVertex2d(P2.x, P2.y);
  glVertex2d(P3.x, P3.y);

  glEnd();

  n--;

  //  Llamada recursiva
  Sierpinski(n, T1, P1, P2);
  Sierpinski(n, P1, T2, P3);
  Sierpinski(n, P2, P3, T3);
}

// Funcion que dibuja el triangulo mas grande
void makeSierpinski(struct vector2d T1, struct vector2d T2, struct vector2d T3)
{
  glColor3f(r, g, b);
  glBegin(GL_POINTS);
  glVertex2d(T1.x, T1.y);
  glVertex2d(T2.x, T2.y);
  glVertex2d(T3.x, T3.y);
  glEnd();
  Sierpinski(8, T1, T2, T3);
}

//<<<<<<<<<<<<< Inicialización >>>>>>>>>>>>>
void iniciar(void)
{
  glClearColor(1.0, 1.0, 1.0, 0.0);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0.0, WIDTH, 0.0, HEIGTH);
}

//<<<<<<<<<<<<<<<<< Dibujado >>>>>>>>>>>>>>>>
void dibujar(void)
{

  glClear(GL_COLOR_BUFFER_BIT);
  // Definimos el tamaño de los puntos
  glLineWidth(2);

  // Dibujo del triangulo principal
  makeSierpinski(T1, T2, T3);

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
        T1.x = x;
        T1.y = abs(y - HEIGTH);
        tmp++;
        break;
      case 1:
        T3.x = x;
        T3.y = abs(y - HEIGTH);
        tmp++;
        break;
      case 2:
        T2.x = x;
        T2.y = abs(y - HEIGTH);
        tmp = 0;
        break;
      }
      glClear(GL_COLOR_BUFFER_BIT);
      makeSierpinski(T1, T2, T3);
      glFlush();
    }
  }
}



// Deteccion del teclado. Las teclas habilitadas son a,b,c SIN EL BLOCK MAYUS ACTIVADO
void keyboard(unsigned char key, int x, int y)
{
  switch (key)
  {
  case 97:
    r = 255;
    g = 0;
    b = 0;
    glClear(GL_COLOR_BUFFER_BIT);
    makeSierpinski(T1, T2, T3);
    glFlush();
    break;
  case 115:
    r = 0;
    g = 255;
    b = 0;
    glClear(GL_COLOR_BUFFER_BIT);
    makeSierpinski(T1, T2, T3);
    glFlush();
    break;
  case 100:
    r = 0;
    g = 0;
    b = 255;
    glClear(GL_COLOR_BUFFER_BIT);
    makeSierpinski(T1, T2, T3);
    glFlush();
    break;
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
  glutDisplayFunc(dibujar);
  glutMouseFunc(mouse);
  glutKeyboardFunc(keyboard);
  iniciar();
  glutMainLoop();

  return 0;
}
/**
 * @author Angelo59930
 * 
 */