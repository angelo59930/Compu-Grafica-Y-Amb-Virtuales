#include <stdio.h>
#include <iostream>
#include <cmath>
#include <GL/glu.h>
#include <GL/glut.h>

#define WIDTH 400.0
#define HEIGTH 400.0

using namespace std;

struct vector2d
{
  float x, y;
};

int r = 0, g = 0, b = 0;
int BURSH = 5;
//<<<<<<<<<<<<< Inicialización >>>>>>>>>>>>>
void iniciar(void)
{
  glClearColor(1.0, 1.0, 1.0, 0.0);
  glColor3f(r, g, b);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0.0, WIDTH, 0.0, HEIGTH);
}

//<<<<<<<<<<<<<<<<< Dibujado >>>>>>>>>>>>>>>>
void dibujar(void)
{
  glClear(GL_COLOR_BUFFER_BIT);

  glFlush();
}

void mouse(int x, int y)
{
  // Generamos la brocha
  GLint posx = x, posy = HEIGTH - y;
  glRecti(posx, posy, posx + BURSH, posy + BURSH);
  glRecti(posx, posy, posx + BURSH, posy + BURSH);
  glFlush();
}

void keyboard(unsigned char key, int x, int y)
{
  switch (key)
  {
  case '+':
    BURSH++;
    glFlush();
    break;
  case '-':
    BURSH--;
    glFlush();
    break;
  case 'r':
    glClear(GL_COLOR_BUFFER_BIT);

    glFlush();
    break;
  case 'a':
    r = 255;
    g = 0;
    b = 0;
    break;
  }
}

//<<<<<<<<<<<<<<<<<<< main >>>>>>>>>>>>>>>>>>
int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(WIDTH, HEIGTH);
  glutInitWindowPosition(100, 150);
  glutCreateWindow("Ejercicio-6");
  glutDisplayFunc(dibujar);
  glutMotionFunc(mouse);
  glutKeyboardFunc(keyboard);
  iniciar();
  glutMainLoop();

  return 0;
}

/**
 * @author Angelo59930
 *
 */