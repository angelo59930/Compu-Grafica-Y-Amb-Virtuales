#include <stdio.h>
#include <iostream>
#include <fstream>
#include <GL/glu.h>
#include <GL/glut.h>
#include <cmath>

#define WIDTH 600.0
#define HEIGTH 600.0

using namespace std;

struct vector2d
{
  float x, y;
};

bool circleDino = true;
float dino[21][2];
float result[21][2];
float rotacion[2][2];

void multiplicarMarices()
{

  // rotando la "rama" complta
  for (int i = 0; i < 21; i++)
    for (int j = 0; j < 2; j++)
    {
      result[i][j] = 0;
      for (int k = 0; k < 2; k++)
      {
        result[i][j] += dino[i][k] * rotacion[k][j];
      }
    }
}

void drawFile(vector2d pos, float angulo)
{
  int firstline = 0, i = 0;

  // Lectura de archivo
  string fileName = "dino.dat";
  ifstream file(fileName.c_str());
  string line = "";

  getline(file, line);
  getline(file, line);
  getline(file, line);
  i = stoi(line);
  for (int j = 0; j < i; j++)
  {
    // Almacenamos el punto anterior para siempre tener 2 puntos por los cuales pasar la linea
    struct vector2d previusPoint;
    getline(file, line);

    // Omitimos las lineas que empiecen #
    if (line[0] == '#')
    {
      j--;
      continue;
    }

    int tmp = stoi(line);

    for (int k = 0; k < tmp; k++)
    {
      struct vector2d actualPoint;
      getline(file, line);
      if (line[0] == '#')
      {
        k--;
        continue;
      }

      actualPoint.x = stoi(line.substr(0, line.find(' ')));
      actualPoint.y = stoi(line.substr(line.find(' '), line.length()));

      if (k == 0 && !circleDino)
      {
        previusPoint.x = actualPoint.x;
        previusPoint.y = actualPoint.y;
        continue;
      }

      glBegin(GL_LINES);
      glLineWidth(4);

      if (!circleDino)
      {
        // Sirve para posicionar y "rotar" al dino
        glVertex2d(200 + pos.x + previusPoint.x / 4, 200 + pos.y + previusPoint.y / 4);
        glVertex2d(200 + pos.x + actualPoint.x / 4, 200 + pos.y + actualPoint.y / 4);
      }
      else
      {
        dino[i][0] = actualPoint.x;
        dino[j][1] = actualPoint.y;
        multiplicarMarices();
      }

      glEnd();

      previusPoint.x = actualPoint.x;
      previusPoint.y = actualPoint.y;
    }
  }

  file.close();

  if(circleDino){
    for(int i = 0; i < 21; i++){
      glVertex2d(200 + dino[i][0] / 4, 200  + dino[i][0] / 4);
      glVertex2d(200 + dino[i][1] / 4, 200  + dino[i][1] / 4);
    }
  }

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
  glClear(GL_COLOR_BUFFER_BIT);

  /*
   * funcion que se encarga de dibujar lo que se encuentre en el archivo
   * Tener en cuenta que el archivo DEBE TENER:
   * 1ra linea un \n
   * 2da linea la cantidad de lineas que tendra el dibujo
   * 3ra linea la cantidad de puntos que tendra esa linea
   * 4ta linea la cordenada de los puntos
   * Luego de eso repetir 3 y 4 las veces que sea necesaria
   */
  for (int i = 1; i < 9; i++)
  {
    float theta = 2.0f * M_PI * float(i) / 8;
    float x = 200 * cosf(theta);
    float y = 200 * sinf(theta);
    rotacion[0][0] = cos(theta);
    rotacion[0][1] = -sin(theta);
    rotacion[1][0] = sin(theta);
    rotacion[1][1] = cos(theta);

    drawFile({x, y}, theta);
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
  glutCreateWindow("Ejercicio-5");
  glutDisplayFunc(dibujar);
  iniciar();
  glutMainLoop();

  return 0;
}
/**
 * @author Angelo59930
 *
 */