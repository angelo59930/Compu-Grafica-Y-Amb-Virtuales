
#include <GL/glu.h>
#include <GL/glut.h>

//<<<<<<<<<<<<< Inicialización >>>>>>>>>>>>>
void iniciar(void)
{
  glClearColor(1.0,1.0,1.0,0.0);
  glColor3f(0.0f, 0.0f, 0.0f);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0.0, 640.0, 0.0, 480.0);
}


//<<<<<<<<<<<<<<<<< Dibujado >>>>>>>>>>>>>>>>
void dibujar(void)
{
  // Dibujo de 3 puntos en las posiciones (100,50), (100,130) y (150,130)
  glClear(GL_COLOR_BUFFER_BIT);
  // Definimos el tamaño de los puntos
  glPointSize(10);
  
  // Empezamos el dibujado de puntos
  glBegin(GL_POINTS);
  // Ubicamos los puntos
  glVertex2d(100, 50);
  glVertex2d(100, 130);
  glVertex2d(150, 130);
  // Terminamos el dibujado de los puntos
  glEnd();

  glFlush();
}


//<<<<<<<<<<<<<<<<<<< main >>>>>>>>>>>>>>>>>>
void main(int argc, char** argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); 
  glutInitWindowSize(640,480);
  glutInitWindowPosition(100, 150); 
  glutCreateWindow("Ejercicio-2"); 
  glutDisplayFunc(dibujar);
  iniciar();
  glutMainLoop();
}

