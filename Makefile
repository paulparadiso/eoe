FRAMEWORK = -framework OpenGL
FRAMEWORK += -framework GLUT

COMPILERFLAGS = -Wall -g 
CC = gcc
CFLAGS = $(COMPILERFLAGS)

OBJECTS = eoe_vector.o glsl_loader.o

LIBS = -lGL -lglut -lm 

INCLUDES = -I/usr/include/GL 

osx: vec_OSX glsl_OSX app_OSX 

linux: vec_LINUX glsl_LINUX app_LINUX

clean:
	rm $(OBJECTS) vec_test

vec_OSX:
	$(CC) $(CFLAGS) $(FRAMEWORK) -c eoe_vector.c 

glsl_OSX:
	$(CC) $(CFLAGS) $(FRAMEWORK) -c glsl_loader.c

app_OSX:
	$(CC) $(CFLAGS) $(FRAMEWORK) $(OBJECTS) eoe_vector_test.c -o vec_test

vec_LINUX:
	$(CC) $(CFLAGS) $(LIBS) -c eoe_vector.c 

glsl_LINUX:
	$(CC) $(CFLAGS) $(LIBS) -c glsl_loader.c

app_LINUX:
	$(CC) $(CFLAGS) $(LIBS) $(OBJECTS) $(INCLUDES) eoe_vector_test.c -o vec_test