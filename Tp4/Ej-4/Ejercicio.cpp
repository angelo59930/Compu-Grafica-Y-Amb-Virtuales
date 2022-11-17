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

vector3d postion = {22, 5, 22};

void draw(vector3d *vector, int nVertices, float angulo)
{

  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  glBegin(GL_POLYGON);

  for(int i = 0; i < nVertices; i++){
    cout << "punto actual: [" << vector[i].x << ", " << vector[i].y << ", " << vector[i].z << "]" << endl;

    glVertex3d(vector[i].x * 2, (vector[i].y - 4.8) * 2, 0);
  }

}

void readFile(int angulo)
{
  vector3d actualPoint = {0, 0, 0};

  // -- Lectura del archivo .3vn
  string filename = "mahal.dat", line = "";
  ifstream file(filename.c_str());
  getline(file, line);

  int points = stoi(line);

  cout << "puntos: " << points << endl;

  vector3d tajLine[points];

  for (int i = 0; i < points; i++)
  {
    getline(file, line);

    actualPoint.y = stof(line.substr(0, line.find(' ')));
    actualPoint.x = stof(line.substr(line.find(' '), line.length()));

    //cout << "punto actual: [" << actualPoint.x << ", " << actualPoint.y << ", " << actualPoint.z << "]" << endl;

    tajLine[i] = actualPoint;
  }

  draw(tajLine,points, angulo);

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
  gluLookAt(postion.x, postion.y, postion.z, 0, 0, 0, 0, 1, 0);

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

  for (int i = 0; i <= 360; i += 25)
    readFile(i);

  glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y)
{

  /**
   * w -> subir
   * s -> bajar
   * a -> rotar izq
   * d -> rotar der
   * q -> acercar
   * e -> alejar
   */

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
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
  glutInitWindowSize(WIDTH, HEIGTH);
  glutInitWindowPosition(100, 150);
  glutCreateWindow("Ejercicio-4");
  glutDisplayFunc(dibujar);
  glutKeyboardFunc(keyboard);
  iniciar();
  glutMainLoop();

  return 0;
}
/**
 * @author Angelo59930
 *
 */