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
int click = 0;

float position[] = {0, 0};

float normal[14][2] = {{10, 10},
                       {10, 100},
                       {70, 100},
                       {70, 65},
                       {55, 65},
                       {55, 80},
                       {27, 80},
                       {27, 25},
                       {55, 25},
                       {55, 40},
                       {45, 40},
                       {45, 55},
                       {70, 55},
                       {70, 10}};
/*
  MATRIZ PARA LA TRANSFORMACION
  (  1/tan(PI/4)     0  )
  (     1            1  )
*/
float rotar[2][2] = {{1 / tan(M_PI / 4), 0},
                      {1, 1}};

float resultNormal[14][2];
float result[14][2];

void trasladarNormal()
{
  for (int i = 0; i < 14; i++)
  {
    for (int j = 0; j < 2; j++)
    {
      resultNormal[i][j] = normal[i][j] + position[j];
    }
  }
}

void trasladarCecilla()
{
  for (int i = 0; i < 14; i++)
  {
    for (int j = 0; j < 2; j++)
    {
      result[i][j] += position[j];
    }
  }
}

void multiplicarMarices()
{
  for (int i = 0; i < 14; i++)
  {
    for (int j = 0; j < 2; j++)
    {
      result[i][j] = 0;
    }
  }

  for (int i = 0; i < 14; i++)
  {
    for (int j = 0; j < 2; j++)
    {
      for (int k = 0; k < 2; k++)
      {
        result[i][j] += normal[i][k] * rotar[k][j];
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
  glVertex2d(resultNormal[4][0], resultNormal[4][1]);
  glVertex2d(resultNormal[5][0], resultNormal[5][1]);
  glVertex2d(resultNormal[6][0], resultNormal[6][1]);
  glVertex2d(resultNormal[7][0], resultNormal[7][1]);
  glVertex2d(resultNormal[8][0], resultNormal[8][1]);
  glVertex2d(resultNormal[9][0], resultNormal[9][1]);
  glVertex2d(resultNormal[10][0], resultNormal[10][1]);
  glVertex2d(resultNormal[11][0], resultNormal[11][1]);
  glVertex2d(resultNormal[12][0], resultNormal[12][1]);
  glVertex2d(resultNormal[13][0], resultNormal[13][1]);
  glEnd();
}

void cizalla()
{
  multiplicarMarices();

  trasladarCecilla();

  glBegin(GL_LINE_LOOP);
  glVertex2d(result[0][0], result[0][1]);
  glVertex2d(result[1][0], result[1][1]);
  glVertex2d(result[2][0], result[2][1]);
  glVertex2d(result[3][0], result[3][1]);
  glVertex2d(result[4][0], result[4][1]);
  glVertex2d(result[5][0], result[5][1]);
  glVertex2d(result[6][0], result[6][1]);
  glVertex2d(result[7][0], result[7][1]);
  glVertex2d(result[8][0], result[8][1]);
  glVertex2d(result[9][0], result[9][1]);
  glVertex2d(result[10][0], result[10][1]);
  glVertex2d(result[11][0], result[11][1]);
  glVertex2d(result[12][0], result[12][1]);
  glVertex2d(result[13][0], result[13][1]);
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
      switch (click)
      {
      case 0:
      
        position[0] = x;
        position[1] = (float)abs(y - HEIGTH);
        glClear(GL_COLOR_BUFFER_BIT);
        drawG();
        glFlush();
        click++;
        break;

      case 1:
        position[0] = x;
        position[1] = (float)abs(y - HEIGTH);
        cizalla();
        glFlush();
        click--;
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