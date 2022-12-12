CC = gcc
COMPILEFLAGS = -Wall -c
LINKFLAGS = -lglut -lGL -lGLU -lm
.PHONY: clean

robo: ${LINKFLAGS}
run: 
	./cool
all: comp run

comp:
	g++ t_final.cpp -o cool
clean:
	rm *.png cool