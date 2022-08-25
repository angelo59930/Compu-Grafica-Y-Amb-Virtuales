CC=gpp
CFLAGS=-o -Wall
CC=gpp 
LDLIBS= -lGL -lGLU -lglut -lm

PROGRAMS=$(basename $(wildcard *.cpp)) 

all: $(PROGRAMS)

clean:
	rm -f $(PROGRAMS) *.o

new: clean all

