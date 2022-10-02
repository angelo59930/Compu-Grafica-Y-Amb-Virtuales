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

void drawFigure()
{

  int nVertices, nNormales, nSuperficies;

  // -- Lectura del archivo .3vn
  string filename = "basicbar.3vn", line = "";
  ifstream file(filename.c_str());

  getline(file, line);

  // Conseguimos la cantidad de vertices, normales y superficies
  nVertices = stoi(line.substr(0, line.find(' ')));
  nNormales = stoi(line.substr(line.find(' '), line.rfind(' ')));
  nSuperficies = stoi(line.substr(line.rfind(' '), line.length()));
  cout << "N vertices: " << nVertices << endl;
  cout << "N normales: " << nNormales << endl;
  cout << "N superficies: " << nSuperficies << endl;
  getline(file, line);

  /*-------------------------------------------*/
  /*CREACION DE ARREGLOS DE VERTICES Y NORMALES*/
  /*-------------------------------------------*/
  vector3d vertices[nVertices];
  vector3d normales[nNormales];
  /*-------------------------------------------*/
  /*-------------------------------------------*/

  /*-------------------------------------------*/
  /*------------RELLENO DE ARREGLOS------------*/
  /*-------------------------------------------*/

  // rellenamos el arreglo de vertices
  for (int i = 0; i < nVertices; i++)
  {
    vertices[i].x = stof(line.substr(0, line.find(' ')));
    vertices[i].y = stof(line.substr(line.find(' '), line.rfind(' ')));
    vertices[i].z = stof(line.substr(line.rfind(' '), line.length()));
    getline(file, line);
  }

  // imprimimos el arreglo de vertices
  cout << "Arreglo de vertices: [ ";
  for (int i = 0; i < nVertices; i++)
  {
    cout << "(" << vertices[i].x << "," << vertices[i].y << "," << vertices[i].z << ")"
         << " ";
  }
  cout << "]" << endl;

  /*------------------------------------------*/

  // rellenamos el arreglo de normales
  for (int i = 0; i < nNormales; i++)
  {
    normales[i].x = stof(line.substr(0, line.find(' ')));
    normales[i].y = stof(line.substr(line.find(' '), line.rfind(' ')));
    normales[i].z = stof(line.substr(line.rfind(' '), line.length()));
    getline(file, line);
  }

  // imprimimos el arreglo de normales
  cout << "Arreglo de normales: [ ";
  for (int i = 0; i < nNormales; i++)
  {
    cout << "(" << normales[i].x << "," << normales[i].y << "," << normales[i].z << ")"
         << " ";
  }
  cout << "]" << endl;

  /*-------------------------------------------*/
  /*-------------------------------------------*/

  /*-------------------------------------------*/
  /*----------CREACION DE SUPERFICIES----------*/
  /*-------------------------------------------*/

  for (int i = 0; i < nSuperficies; i++)
  {
    int verticesSuperficie = stoi(line);

    glBegin(GL_POLYGON);
    // lista de vertices
    for (int j = 0; j < verticesSuperficie; j++)
    {
      vector3d vector;

      glVertex3d(vector.x, vector.y, vector.z);
    }
    glEnd();

    int normalesSuperficie = stoi(line);
    // lista de normales
    for (int j = 0; j < verticesSuperficie; j++)
    {
    }
  }

  /*-------------------------------------------*/
  /*-------------------------------------------*/

  file.close();
  // -- fin de lectura del archivo .3vn
}

//<<<<<<<<<<<<< Inicialización >>>>>>>>>>>>>
void iniciar(void)
{
  glClearColor(1.0, 1.0, 1.0, 0.0);
  glColor3f(0.0f, 0.0f, 0.0f);
}

//<<<<<<<<<<<<<<<<< Dibujado >>>>>>>>>>>>>>>>
void dibujar(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  drawFigure();

  glutSwapBuffers();
}

//<<<<<<<<<<<<<<<<<<< main >>>>>>>>>>>>>>>>>>
int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
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