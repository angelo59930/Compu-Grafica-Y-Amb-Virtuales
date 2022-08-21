# Computación grafica y ambientes virtuales 🖼️

Todos los programas realizados en este repositorio, o al menos la mayoria, se encontraran escritos en el lenguaje de programacion **C++**.
La libreria grafica que se usara(o se esta usando a dia de hoy en la materia) es OpenGl

## ⚠️ TENER EN CUENTA ⚠️
- Este repositorio servira para tener todos los ejercicios, de cada trabajo practico, de la materia computacion grafica y ambientes virtuales.

- Por el momento el repositorio **esta en construccion**, por lo tanto, no se encontran todos los ejercicios

- No necesariamente los algoritmos propuestos esten lo mas optimizados ni mucho menos

- En el caso de querer proponer una solucion, o un cambio, realizar un Pull request

## Ejemplo base
- [Ejemplo Base](./ejemplo_base/ejemplo.cpp)

## Trabajos practicos
- [Tp-1](./Tp1)
- [Tp-2]()
- ...

## Guia de uso de OpenGL
### Linux
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
