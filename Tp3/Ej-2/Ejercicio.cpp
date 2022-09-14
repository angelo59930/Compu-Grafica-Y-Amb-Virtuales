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

float position[] = {0, 0};

// TODO ARREGLAR LA POSICION
float fix[] = {HEIGTH / 32, HEIGTH / 25};

float normal[4][2] = {{10, 10},
                      {10, 100},
                      {70, 100},
                      {70, 10}};

float italic[2][2] = {
    {sin(-0.523599), cos(-0.523599)},
    {cos(-0.523599), -sin(-0.523599)},
};

float resultNormal[4][2];
float result[4][2];

void trasladarNormal()
{
  for (int i = 0; i < 4; i++)
  {
    for (int j = 0; j < 2; j++)
    {
      resultNormal[i][j] = normal[i][j] + position[j];
    }
  }
}

// TODO MOD
void trasladarRotada()
{
  for (int i = 0; i < 4; i++)
  {
    for (int j = 0; j < 2; j++)
    {
      result[i][j] += position[j] + fix[j];
    }
  }
}

void multiplicarMarices()
{
  for (int i = 0; i < 4; i++)
  {
    for (int j = 0; j < 2; j++)
    {
      result[i][j] = 0;
    }
  }

  for (int i = 0; i < 4; i++)
  {
    for (int j = 0; j < 2; j++)
    {
      for (int k = 0; k < 2; k++)
      {
        result[i][j] += normal[i][k] * italic[k][j];
      }
    }
  }
}

void drawG()
{
  trasladarNormal();
  glBegin(GL_LINE_LOOP);
  glVertex2d(resultNormal[0][0], resultNormal[0][1]);
  glVertex2d(resultNormal[1][0], resultNormal[1][1]);
  glVertex2d(resultNormal[2][0], resultNormal[2][1]);
  glVertex2d(resultNormal[3][0], resultNormal[3][1]);
  glEnd();
}

void cizalla()
{
  multiplicarMarices();

  trasladarRotada();

  glBegin(GL_LINE_LOOP);
  glVertex2d(result[0][0], result[0][1]);
  glVertex2d(result[1][0], result[1][1]);
  glVertex2d(result[2][0], result[2][1]);
  glVertex2d(result[3][0], result[3][1]);
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
  glFlush();
}

void mouse(int button, int state, int x, int y)
{

  if (button == GLUT_LEFT_BUTTON)
  {
    if (state == GLUT_DOWN)
    {
      position[0] = x;
      position[1] = (float)abs(y - HEIGTH);
      glClear(GL_COLOR_BUFFER_BIT);
      drawG();
      cizalla();
      glFlush();
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
  glutCreateWindow("Ejercicio-1");
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