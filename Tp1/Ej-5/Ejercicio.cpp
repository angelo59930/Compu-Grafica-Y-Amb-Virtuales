#include <stdio.h>
#include <iostream>
#include <fstream>
#include <GL/glu.h>
#include <GL/glut.h>

#define WIDTH 700.0
#define HEIGTH 500.0

using namespace std;

struct vector2d
{
  float x, y;
};

void drawFile()
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
  cout << "Numero de lineas:" << i << endl;
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

    cout << "numero de puntos: " << tmp << endl;

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

      if (k == 0)
      {
        previusPoint.x = actualPoint.x;
        previusPoint.y = actualPoint.y;
        continue;
      }

      glBegin(GL_LINE_STRIP);
      glLineWidth(4);

      glVertex2d(previusPoint.x, previusPoint.y);
      glVertex2d(actualPoint.x, actualPoint.y);

      glEnd();

      previusPoint.x = actualPoint.x;
      previusPoint.y = actualPoint.y;
    }
  }

  file.close();
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
  drawFile();

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