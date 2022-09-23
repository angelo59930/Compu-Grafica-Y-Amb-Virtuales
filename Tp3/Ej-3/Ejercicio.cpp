#include <stdio.h>
#include <iostream>
#include <cmath>
#include <GL/glu.h>
#include <GL/glut.h>

#define WIDTH 400.0
#define HEIGTH 400.0
#define LONG 11
#define ESC 1.1

using namespace std;

// Vector de 2 dimensiones
struct vector2d
{
  float x, y;
};
// temnplate de rama
float rama[LONG][2] = {{0, 2},
                       {50, 2},
                       {50, 27},
                       {55, 27},
                       {55, 2},
                       {75, 2},
                       {75, 17},
                       {80, 17},
                       {80, 2},
                       {100, 2},
                       {100, 0}};
float result[8][2];
float resultCecilla[8][2];
float rotacion[2][2] = {{1, 1}, {1, 1}};
float cecilla[2][2] = {{1 / tan(M_PI / 4), 0},
                       {1, 1}};

void multiplicarMarices()
{
  // curvando las "ramitas" del copo
  for (int i = 0; i < LONG; i++)
    for (int j = 0; j < 2; j++)
    {
      resultCecilla[i][j] = 0;
      for (int k = 0; k < 2; k++)
      {
        resultCecilla[i][j] += rama[i][k] * cecilla[k][j];
      }
    }
  // rotando la "rama" complta
  for (int i = 0; i < LONG; i++)
    for (int j = 0; j < 2; j++)
    {
      result[i][j] = 0;
      for (int k = 0; k < 2; k++)
      {
        result[i][j] += resultCecilla[i][k] * rotacion[k][j];
      }
    }
}

void dibujarRama()
{
  multiplicarMarices();
  glBegin(GL_LINE_STRIP);
  for (int i = 0; i < LONG; i++)
  {
    glVertex2d(200 + result[i][0], (200 - result[i][1]));
    glVertex2d(200 + result[i][0], (200 - result[i][1]));
  }
  glEnd();
  glBegin(GL_LINE_STRIP);
  for (int i = 0; i < LONG; i++)
  {
    glVertex2d(200 + result[i][0], 200 + result[i][1]);
    glVertex2d(200 + result[i][0], 200 + result[i][1]);
  }
  glEnd();
}

void drawSnow()
{

  for (int m = 1; m < 7; m++)
  {
    rotacion[0][0] = cos(m * M_PI / 3);
    rotacion[0][1] = -sin(m * M_PI / 3);
    rotacion[1][0] = sin(m * M_PI / 3);
    rotacion[1][1] = cos(m * M_PI / 3);

    dibujarRama();
  }
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

  drawSnow();

  glFlush();
}

void keyboard(unsigned char key, int x, int y)
{
  switch (key)
  {
  case '-':
    for (int i = 0; i < LONG; i++)
    {
      rama[i][0] /= ESC;
      rama[i][1] /= ESC;
    }
    break;
  case '+':

    for (int i = 0; i < LONG; i++)
    {
      rama[i][0] *= ESC;
      rama[i][1] *= ESC;
    }
    break;
  }
  dibujar();
}

//<<<<<<<<<<<<<<<<<<< main >>>>>>>>>>>>>>>>>>
int main(int argc, char **argv)
{

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(WIDTH, HEIGTH);
  glutInitWindowPosition(100, 150);
  glutCreateWindow("Ejercicio-3");
  glutKeyboardFunc(keyboard);
  glutDisplayFunc(dibujar);
  iniciar();
  glutMainLoop();

  return 0;
}
/**
 * @author Angelo59930
 *
 */