#include <stdio.h>
#include <iostream>
#include <fstream>
#include <GL/glu.h>
#include <GL/glut.h>
#include <cmath>

#define WIDTH 600.0
#define HEIGTH 600.0

using namespace std;

float CAMERA_VEL = 0.25;

struct vector3d
{
  float x;
  float y;
  float z;
};

vector3d postion = {7, 2.5, 3.75};

void draw(vector3d vector, int nVertices)
{

  glBegin(GL_POLYGON);

  for (int i = 0; i < nVertices; i++)
    glVertex3d(vector.x, vector.y, vector.z);

  glEnd();
}

void drawFigure(string nameFile, vector3d color)
{

  int nVertices, nNormales, nSuperficies;

  // -- Lectura del archivo .3vn
  string filename = nameFile, line = "";
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

    getline(file, line);

    // glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glBegin(GL_POLYGON);

    glColor3d(color.x, color.y, color.z);
    // lista de vertices
    cout << "indice: ";
    for (int j = 0; j < verticesSuperficie; j++)
    {
      int k = stoi(line.substr(0, line.find(' ')));
      line.erase(0, line.find(' ') + 1);
      cout << k << " ";

      glVertex3d(vertices[k].x, vertices[k].y, vertices[k].z);
    }
    cout << endl;
    glEnd();

    getline(file, line);

    int normalesSuperficie = stoi(line);
    // lista de normales
    for (int j = 0; j < verticesSuperficie; j++)
    {
    }
    getline(file, line);
  }

  /*-------------------------------------------*/
  /*-------------------------------------------*/

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
  glEnable(GL_DEPTH_TEST);
  glLoadIdentity();
  gluLookAt(postion.x, postion.y, postion.z, 0, 0, 0, 0, 1, 0);
  drawFigure("pared_1.3vn", {0.8, 0.8, 0.45});
  drawFigure("pared_2.3vn", {0.8, 0.8, 0.45});
  drawFigure("piso.3vn", {0.8, 0.8, 0.2});
  drawFigure("mesa.3vn", {0.5, 0.2, 0.1});
  drawFigure("silla.3vn", {0.5, 0, 0.5});
  drawFigure("pelota.3vn", {1 / 255, 1, 1});
  glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y)
{
  switch (key)
  {
  case 'w':
    postion.y += CAMERA_VEL;
    break;

  case 's':
    postion.y -= CAMERA_VEL;
    break;

  case 'a':
    postion.x += CAMERA_VEL;
    break;

  case 'd':
    postion.x -= CAMERA_VEL;
    break;

  case 'q':
    postion.z += CAMERA_VEL;
    break;
  case 'e':
    postion.z -= CAMERA_VEL;
    break;
  }

  cout << "punto actual: [" << postion.x << ", " << postion.y << ", " << postion.z << "]" << endl;

  glutPostRedisplay();
}

//<<<<<<<<<<<<<<<<<<< main >>>>>>>>>>>>>>>>>>
int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glutInitWindowSize(WIDTH, HEIGTH);
  glutInitWindowPosition(100, 150);
  glutCreateWindow("Ejercicio-5");
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