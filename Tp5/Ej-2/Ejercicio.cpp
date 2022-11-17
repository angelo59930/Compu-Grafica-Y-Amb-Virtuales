#include <stdio.h>
#include <iostream>
#include <fstream>
#include <GL/glu.h>
#include <GL/glut.h>
#include <cmath>

using namespace std;

struct vector3d
{
  float x;
  float y;
  float z;
};

vector3d postion = {2, -2, 1};

void drawFigure(string nameFile)
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
      int k = stoi(line.substr(0, line.find(' ')));
      line.erase(0, line.find(' ') + 1);
      cout << k << " ";

      glNormal3d(normales[k].x, normales[k].y, normales[k].z);
    }
    getline(file, line);
  }

  /*-------------------------------------------*/
  /*-------------------------------------------*/

  file.close();
  // -- fin de lectura del archivo .3vn
}

void init(void)
{
  GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0};
  GLfloat mat_shininess[] = {10.0};
  GLfloat light_position[] = {1.0, 1.0, 1.0, 0.0};
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glShadeModel(GL_SMOOTH);
  glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
  glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
  glLightfv(GL_LIGHT0, GL_POSITION, light_position);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_DEPTH_TEST);

  glColor3f(0.0f, 0.0f, 0.0f);
  glLoadIdentity();
}
void display(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
  gluPerspective(50, 1, 3, 20);
  gluLookAt(postion.x, postion.y, postion.z, 0, 0, 0, 0, 1, 0);
  
  drawFigure("wineglas.3vn");

  glFlush();
}
void reshape(int w, int h)
{
  glViewport(0, 0, (GLsizei)w, (GLsizei)h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  if (w <= h)
    glOrtho(-1.5, 1.5, -1.5 * (GLfloat)h / (GLfloat)w,
            1.5 * (GLfloat)h / (GLfloat)w, -10.0, 10.0);
  else
    glOrtho(-1.5 * (GLfloat)w / (GLfloat)h,
            1.5 * (GLfloat)w / (GLfloat)h, -1.5, 1.5, -10.0, 10.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}
int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(500, 500);
  glutInitWindowPosition(100, 100);
  glutCreateWindow(argv[0]);
  init();
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutMainLoop();
  return 0;
}