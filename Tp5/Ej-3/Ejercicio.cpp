#include <stdio.h>
#include <iostream>
#include <fstream>
#include <GL/glu.h>
#include <GL/glut.h>
#include <cmath>

float CAMERA_VEL = 0.25;

using namespace std;

struct vector3d
{
  float x;
  float y;
  float z;
};

int aux = 0, figure = 0;

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

  /*------------------------------------------*/

  // rellenamos el arreglo de normales
  for (int i = 0; i < nNormales; i++)
  {
    normales[i].x = stof(line.substr(0, line.find(' ')));
    normales[i].y = stof(line.substr(line.find(' '), line.rfind(' ')));
    normales[i].z = stof(line.substr(line.rfind(' '), line.length()));
    getline(file, line);
  }

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
    for (int j = 0; j < verticesSuperficie; j++)
    {
      int k = stoi(line.substr(0, line.find(' ')));
      line.erase(0, line.find(' ') + 1);

      glVertex3d(vertices[k].x, vertices[k].y, vertices[k].z);
    }
    glEnd();

    getline(file, line);

    int normalesSuperficie = stoi(line);
    // lista de normales
    for (int j = 0; j < verticesSuperficie; j++)
    {
      int k = stoi(line.substr(0, line.find(' ')));
      line.erase(0, line.find(' ') + 1);
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

  glOrtho(0.0, 500.0, 0.0, 500.0, -100, 100);

  glColor3f(0.0f, 0.0f, 0.0f);
  glLoadIdentity();
  glMatrixMode(GL_MODELVIEW);
}
void display(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
  glEnable(GL_DEPTH_TEST);
  glLoadIdentity();

  gluPerspective(50, 1, 3, 20);
  gluLookAt(postion.x, postion.y, postion.z, 0, 0, 0, 0, 1, 0);

  if (figure == 0)
    drawFigure("wineglas.3vn");

  if (figure == 1)
    glutSolidTetrahedron();

  if (figure == 2)
    glutSolidIcosahedron();

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

  case 'x':
    figure++;
    if (figure > 2)
      figure = 0;
    break;
  }

  glutPostRedisplay();
}

int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(500, 500);
  glutInitWindowPosition(100, 100);
  glutCreateWindow(argv[0]);
  init();
  glutKeyboardFunc(keyboard);
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutMainLoop();
  return 0;
}