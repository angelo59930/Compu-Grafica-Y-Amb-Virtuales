#include <stdio.h>
#include <iostream>
#include <fstream>
#include <GL/glu.h>
#include <GL/glut.h>

#define WIDTH 500.0
#define HEIGTH 500.0

using namespace std;

struct vector2d
{
  float x, y;
};

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

  int firstline = 0, i = 0;
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

    getline(file, line);

    if (line[0] == '#')
    {
      j--;
      continue;
    }

    int tmp = stoi(line);

    cout << "numero de puntos: " << tmp << endl;

    for (int k = 0; k < tmp; k++)
    {

      int x, y;
      getline(file, line);
      if (line[0] == '#')
      {
        k--;
        continue;
      }

      x = stoi(line.substr(0, line.find(' ')));
      y = stoi(line.substr(line.find(' '), line.length()));

      cout << "x: " << x << "  y: " << y << endl;

      glClear(GL_COLOR_BUFFER_BIT);

      glBegin(GL_POINTS);
      glPointSize(2);

      glVertex2d(x, y);

      glEnd();
      glutSwapBuffers();
    }
  }

  file.close();
}

//<<<<<<<<<<<<<<<<<<< main >>>>>>>>>>>>>>>>>>
int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE| GLUT_RGB);
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