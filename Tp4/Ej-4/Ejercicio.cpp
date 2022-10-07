#include <stdio.h>
#include <iostream>
#include <fstream>
#include <GL/glu.h>
#include <GL/glut.h>
#include <cmath>

#define WIDTH 600.0
#define HEIGTH 600.0

using namespace std;

struct vector3d
{
  float x;
  float y;
  float z;
};

void draw(vector3d vector, int nVertices)
{

  glBegin(GL_POLYGON);

  for (int i = 0; i < nVertices; i++)
    glVertex3d(vector.x, vector.y, vector.z);

  glEnd();
}

void drawFigure(int angulo)
{
  vector3d actualPoint = {0, 0, 0};

  // -- Lectura del archivo .3vn
  string filename = "mahal.dat", line = "";
  ifstream file(filename.c_str());
  getline(file, line);

  int points = stoi(line);

  cout << "puntos: " << points << endl;

  glRotatef(angulo, 0, 1, 0);

  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  glBegin(GL_POLYGON);
  for (int i = 0; i < points; i++)
  {
    getline(file, line);

    actualPoint.y = stof(line.substr(0, line.find(' ')));
    actualPoint.x = stof(line.substr(line.find(' '), line.length()));
    
    cout << "punto actual: [" << actualPoint.x << ", " << actualPoint.y << ", " << actualPoint.z << "]" << endl;

    // dibujado
    glVertex3d(actualPoint.x * 2, (actualPoint.y - 4.8)*2, 0);
  }
  glEnd();



  file.close();
  // -- fin de lectura del archivo .3vn
}

//<<<<<<<<<<<<< Inicialización >>>>>>>>>>>>>
void iniciar(void)
{
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glClearColor(1.0, 1.0, 1.0, 0.0);
  glColor3f(0.0f, 0.0f, 0.0f);
  gluPerspective(45, (float)16 / 9, 0.1, 100);
  glMatrixMode(GL_MODELVIEW);
}

//<<<<<<<<<<<<<<<<< Dibujado >>>>>>>>>>>>>>>>
void dibujar(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glLoadIdentity();
  gluLookAt(22, 5,22, 0, 0, 0, 0, 1, 0);

  glBegin(GL_LINES);
  glVertex3d(0, 0, 0);
  glVertex3d(400, 0, 0);
  glEnd();
  glBegin(GL_LINES);
  glVertex3d(0, 0, 0);
  glVertex3d(0, 400, 0);
  glEnd();
  glBegin(GL_LINES);
  glVertex3d(0, 0, 0);
  glVertex3d(0, 0, 400);
  glEnd();


  for(int i = 0; i <= 360; i++)
    drawFigure(i);

  glutSwapBuffers();
}

//<<<<<<<<<<<<<<<<<<< main >>>>>>>>>>>>>>>>>>
int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
  glutInitWindowSize(WIDTH, HEIGTH);
  glutInitWindowPosition(100, 150);
  glutCreateWindow("Ejercicio-1");
  glutDisplayFunc(dibujar);
  iniciar();
  glutMainLoop();

  return 0;
}
/**
 * @author Angelo59930
 *
 */