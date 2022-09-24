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


/**
 * @brief 
 * Esta funcion nos permite multiplcar las matrices que necesitamos
 * 
 * La primera matriz es de cecilla la cual nos permite generar
 * la "curva" de cada ramita de la rama principal
 * 
 * La segunda matriz que multiplica es la que le da la rotacion
 * en otras palabras, la rota
 * 
 * @attention NO DEVUELVE NADA ESTA MATRIZ YA QUE LO VUELCA EN LAS MATRICES GLOBALES 
 */
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

/**
 * @brief
 *
 * Funcion que dibuja el copo de nieve en la posicion deseada y del tamaño deseado
 *
 * @param position[vector2d] posicion donde queresmos que se dibuje el copo
 * @param esc[float] escalado del copo de nieve
 */
void dibujarRama(vector2d position, float esc)
{
  multiplicarMarices();
  glBegin(GL_LINE_STRIP);

  /*Dibujamos la rama opuesta*/
  for (int i = 0; i < LONG; i++)
  {
    glVertex2d(position.x + result[i][0] * esc, (position.y - result[i][1] * esc));
    glVertex2d(position.x + result[i][0] * esc, (position.y - result[i][1] * esc));
  }
  glEnd();
  glBegin(GL_LINE_STRIP);
  /*Dibujamos la rama original*/
  for (int i = 0; i < LONG; i++)
  {
    glVertex2d(position.x + result[i][0] * esc, position.y + result[i][1] * esc);
    glVertex2d(position.x + result[i][0] * esc, position.y + result[i][1] * esc);
  }
  glEnd();
}
/**
 * @brief 
 * 
 * Esta funcion nos permite dibujar un copo de nieve completo en una posicion x e y que querramos
 * 
 * @param x[float] posicion x
 * @param y[float] posicion y
 */
void drawSnow(float x, float y)
{
  float esc = drand48();

  /* Vamos generando la matriz de rotacion para cada "rama" del copo*/
  for (int m = 1; m < 7; m++)
  {
    rotacion[0][0] = cos(m * M_PI / 3);
    rotacion[0][1] = -sin(m * M_PI / 3);
    rotacion[1][0] = sin(m * M_PI / 3);
    rotacion[1][1] = cos(m * M_PI / 3);

    dibujarRama({x, y}, esc);
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

  srand(time(NULL));

  for (int i = 0; i < 25; i++)
  {
    drawSnow(rand() % (400) - +rand() % (i + 25) - 5, rand() % (400) - +rand() % (i + 25) - 5);
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
/**
 * @author Angelo59930
 *
 */