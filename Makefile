FRAMEWORK = -framework OpenGL
FRAMEWORK += -framework GLUT

COMPILERFLAGS = -Wall -g -std=c99 -pedantic
CC = gcc
CFLAGS = $(COMPILERFLAGS)

OBJECTS = eoe_vector.o glsl_loader.o node.o

LIBS = -lGL -lglut -lm 

INCLUDES = -I/usr/include/GL 

osx: vec_OSX glsl_OSX node_OSX app_OSX 

linux: vec_LINUX glsl_LINUX node_LINUX app_LINUX

clean:
	rm $(OBJECTS) vec_test

vec_OSX:
	$(CC) $(CFLAGS) $(FRAMEWORK) -c eoe_vector.c 

glsl_OSX:
	$(CC) $(CFLAGS) $(FRAMEWORK) -c glsl_loader.c

node_OSX:
	$(CC) $(CFLAGS) $(FRAMEWORK) -c node.c

app_OSX:
	$(CC) $(CFLAGS) $(FRAMEWORK) $(OBJECTS) eoe_vector_test.c -o vec_test

vec_LINUX:
	$(CC) $(CFLAGS) $(LIBS) -c eoe_vector.c 

glsl_LINUX:
	$(CC) $(CFLAGS) $(LIBS) -c glsl_loader.c

node_LINUX:
	$(CC) $(CFLAGS) $(LIBS) -c node.c

app_LINUX:
	$(CC) $(CFLAGS) $(LIBS) $(OBJECTS) $(INCLUDES) eoe_vector_test.c -o vec_test