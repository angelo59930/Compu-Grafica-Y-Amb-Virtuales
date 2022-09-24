# Computación grafica y ambientes virtuales 🖼️

Todos los programas realizados en este repositorio, o al menos la mayoria, se encontraran escritos en el lenguaje de programacion **C y C++**.

La libreria grafica que se usara(o se esta usando a dia de hoy en la materia) es OpenGl.

La guia de instalacion y uso de OpenGl en Linux se encuentra al final del README

## ⚠️ TENER EN CUENTA ⚠️
- Este repositorio servira para tener todos los ejercicios, de cada trabajo practico, de la materia computacion grafica y ambientes virtuales.

- Por el momento el repositorio **esta en construccion**, por lo tanto, no se encontran todos los ejercicios

- No necesariamente los algoritmos propuestos esten lo mas optimizados ni mucho menos

- En el caso de querer proponer una solucion, o un cambio, realizar un Pull request

## Contenido

### Ejemplo base 📖
- [Ejemplo Base](./ejemplo_base/ejemplo.cpp)

### Trabajos practicos 📒
- [Introduccion a OpenGL. Tp-1](./Tp1)
- [Visualizacion 2D. Tp-2](./Tp2)
- [Modelo y trasnformacion](./Tp3/)
	- Nota: El Ej-5 esta a la mitad

### Bibliografia 📚
- [PDFs](./Material%20Bibleografico/)
	- [OpenGL y Glut](./Material%20Bibleografico/05_apuntes_opengl.pdf)
	- [Introduccion a OpenGl](./Material%20Bibleografico/03-2_body-OpenGL.pdf)
	- [OpenGl:Red Book](./Material%20Bibleografico/04_RedBook.pdf)

## Guia de uso de OpenGL
### Instalacion en linux(Ubuntu 22.04/21.04)
Simplemente se tiene que instalar las siguientes librerias.
```bash
sudo apt-get install libgl1-mesa-dev libglu1-mesa-dev freeglut3-dev
```
Una vez instaladas las librerias solo tendremos que ejecutar el archivo **make** que se va a encontrar en la misma carpeta que nuestro codigo fuente.

Para ejecutar el archivo solo tendremos que hacer:
```bash
make
```
---
El archivo make contiene lo siguiente.

Este contenido sirve si quieren **usar unicamente C**

```bash
CC=gcc
CFLAGS=-O2 -g -Wall
CC=gcc
LDLIBS= -lGL -lGLU -lglut -lm
PROGRAMS=$(basename $(wildcard *.c)) 
all: $(PROGRAMS)
clean:
	rm -f $(PROGRAMS) *.o
new: clean all
```
---
Este de aqui sirve para C++

Notar que se utiliza el compilador gpp
```bash
CC=gpp
CFLAGS=-o
CC=gpp
LDLIBS= -lGL -lGLU -lglut -lm
PROGRAMS=$(basename $(wildcard *.cpp)) 
all: $(PROGRAMS)
clean:
	rm -f $(PROGRAMS) *.o
new: clean all
```
---
### Instalacion en windows
Solucion sencilla:
1) Instalar OpenGl en su computadora(si es de jugar seguramente ya lo tengas)
2) Instalar Zinjai
3) Crear un nuevo proyecto OpenGl