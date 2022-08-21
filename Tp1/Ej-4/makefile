CC=gcc
CFLAGS=-O2 -g -Wall
CC=gcc
LDLIBS= -lGL -lGLU -lglut -lm

PROGRAMS=$(basename $(wildcard *.c)) 

all: $(PROGRAMS)

clean:
	rm -f $(PROGRAMS) *.o

new: clean all

