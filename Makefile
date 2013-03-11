FRAMEWORK = -framework OpenGL
FRAMEWORK += -framework GLUT

COMPILERFLAGS = -Wall -g 
CC = gcc
CFLAGS = $(COMPILERFLAGS)

OBJECTS = eoe_vector.o glsl_loader.o

LIBRARIES = -lGL -lglut 

osx: vec_OSX glsl_OSX app_OSX 

clean:
	rm $(OBJECTS) vec_test

vec_OSX:
	$(CC) $(CFLAGS) $(FRAMEWORK) -c eoe_vector.c 

glsl_OSX:
	$(CC) $(CFLAGS) $(FRAMEWORK) -c glsl_loader.c

app_OSX:
	$(CC) $(CFLAGS) $(FRAMEWORK) $(OBJECTS) eoe_vector_test.c -o vec_test
