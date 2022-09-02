#include <GL/glu.h>
#include <GL/glut.h>
#include <cmath>
#include <iostream>

using namespace std;

#define MAX_WIDTH 300
#define MAX_HEIGHT 240

struct Point
{
    int x;
    int y;
};

int mouseX, mouseY, mouseStatus, color = 1;
bool isFirstVertexDrew = false;
Point P, Q;

//<<<<<<<<<<<<< Inicialización >>>>>>>>>>>>>
void iniciar(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glColor3f(0.0f, 0.0f, 0.0f);
    glPointSize(5);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, MAX_WIDTH, 0.0, MAX_HEIGHT);
}

void drawLine(int x1, int y1, int x2, int y2)
{
    GLfloat M, p, dx, dy, x, y, t;

    if ((x2 - x1) == 0)
        M = (y2 - y1);
    else
        M = (y2 - y1) / (x2 - x1);

    if (fabs(M) < 1)
    {
        if (x1 > x2)
        {
            t = x1;
            x1 = x2;
            x2 = t;

            t = y1;
            y1 = y2;
            y2 = t;
        }

        dx = fabs(x2 - x1);
        dy = fabs(y2 - y1);

        p = 2 * dy - dx;

        x = x1;
        y = y1;

        glBegin(GL_POINTS);
        while (x <= x2)
        {
            glVertex2f(x, y);
            x = x + 1;

            if (p >= 0)
            {
                if (M < 1)
                    y = y + 1;
                else
                    y = y - 1;
                p = p + 2 * dy - 2 * dx;
            }
            else
            {
                y = y;
                p = p + 2 * dy;
            }
        }
        glEnd();
    }

    if (fabs(M) >= 1)
    {
        if (y1 > y2)
        {
            t = x1;
            x1 = x2;
            x2 = t;

            t = y1;
            y1 = y2;
            y2 = t;
        }

        dx = fabs(x2 - x1);
        dy = fabs(y2 - y1);

        p = 2 * dx - dy;

        x = x1;
        y = y1;

        glBegin(GL_POINTS);
        while (y <= y2)
        {
            glVertex2f(x, y);
            y = y + 1;

            if (p >= 0)
            {
                if (M >= 1)
                    x = x + 1;
                else
                    x = x - 1;
                p = p + 2 * dx - 2 * dy;
            }
            else
            {
                x = x;
                p = p + 2 * dx;
            }
        }
        glEnd();
    }

    glFlush();
}

// Funcion auxiliar para mostrar un texto por pantalla
void displayText(string textToDisplay, int x, int y)
{
    glColor3f(0, 0, 0);
    glRasterPos2d(x, y);

    for (char character : textToDisplay)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, character);
    }
}

void showColor()
{
    string colorText;
    switch (color)
    {
    case 1:
        // Negro
        colorText = "Negro";
        break;
    case 2:
        // Negro
        colorText = "Rojo";
        break;
    case 3:
        // Negro
        colorText = "Azul";
        break;
    case 4:
        // Negro
        colorText = "Rosa";
        break;
    case 5:
        // Negro
        colorText = "Celeste";
        break;
    }

    displayText("Color: " + colorText, 10, MAX_HEIGHT - 20);
}

void fillRectangle(Point p, Point q, int color)
{
    switch (color)
    {
    case 1:
        glColor3f(0, 0, 0);
        break;
    case 2:
        glColor3f(255, 0, 0);
        break;
    case 3:
        glColor3f(0, 0, 255);
        break;
    case 4:
        glColor3f(200, 0, 255);
        break;
    case 5:
        glColor3f(0, 255, 247);
        break;
    }
    int xMin, yMin, xMax, yMax;

    if (p.x < q.x)
    {
        xMin = p.x;
        xMax = q.x;
    }
    else
    {
        xMin = q.x;
        xMax = p.x;
    }

    if (p.y < q.y)
    {
        yMin = p.y;
        yMax = q.y;
    }
    else
    {
        yMin = q.y;
        yMax = p.y;
    }

    for (int y = yMin; y <= yMax; y++)
    {
        for (int x = xMin; x <= xMax; x++)
        {
            glBegin(GL_POINTS);
            glVertex2d(x, y);
            glEnd();
            glFlush();
        }
    }
}

void drawRectangle(Point P, Point Q, bool painted)
{
    // Primer linea
    drawLine(P.x, P.y, P.x, Q.y);

    // Segunda linea
    drawLine(P.x, Q.y, Q.x, Q.y);

    // Tercer linea
    drawLine(P.x, P.y, Q.x, P.y);

    // Cuarta linea y final
    drawLine(Q.x, P.y, Q.x, Q.y);

    if (painted)
    {
        fillRectangle(P, Q, color);
    }
    showColor();
}

void drawPoint(Point point)
{
    glBegin(GL_POINTS);
    glVertex2d(point.x, point.y);
    glEnd();
    glFlush();
}

void handleKeyboardAction(unsigned char keyPressed, int x, int y)
{
    switch (keyPressed)
    {
    case 49:
        color = 1;
        break;
    case 50:
        color = 2;
        break;
    case 51:
        color = 3;
        break;
    case 52:
        color = 4;
        break;
    case 53:
        color = 5;
        break;
    }

    glScissor(0, MAX_HEIGHT - 30, 90, 30);
    glEnable(GL_SCISSOR_TEST);
    glClear(GL_COLOR_BUFFER_BIT);
    glDisable(GL_SCISSOR_TEST);
    showColor();
    glFlush();
}

void handlePassiveMotion(int x, int y)
{
    if (isFirstVertexDrew)
    {
        mouseX = x;
        mouseY = abs(y - MAX_HEIGHT);
        Point temporalPoint = {mouseX, mouseY};

        glClear(GL_COLOR_BUFFER_BIT);
        drawRectangle(P, temporalPoint, false);
    }
}

void handleMouseAction(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON)
    {
        if (state == GLUT_DOWN)
        {
            // Cuando haga click
            if (mouseStatus == 0)
            {
                // Significa que tiene que hacer el punto P
                P.x = x;
                P.y = abs(y - MAX_HEIGHT);
                drawPoint(P);
                isFirstVertexDrew = true;
                mouseStatus = 1;
            }
            else
            {
                // Significa que tiene que hacer el punto Q
                Q.x = x;
                Q.y = abs(y - MAX_HEIGHT);
                drawRectangle(P, Q, true);
                isFirstVertexDrew = false;
                mouseStatus = 0;
            }
        }
    }
}

//<<<<<<<<<<<<<<<<< Dibujado >>>>>>>>>>>>>>>>
void draw(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    showColor();

    glEnd();
    glFlush();
}

//<<<<<<<<<<<<<<<<<<< main >>>>>>>>>>>>>>>>>>
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(MAX_WIDTH, MAX_HEIGHT);
    glutInitWindowPosition(100, 150);
    glutCreateWindow("Ejercicio 4");
    glutDisplayFunc(draw);
    glutMouseFunc(handleMouseAction);
    glutPassiveMotionFunc(handlePassiveMotion);
    glutKeyboardFunc(handleKeyboardAction);
    iniciar();
    glutMainLoop();
}