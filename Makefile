FRAMEWORK = -framework OpenGL
FRAMEWORK += -framework GLUT

COMPILERFLAGS = -Wall -g -std=c99 -pedantic
CC = gcc
CFLAGS = $(COMPILERFLAGS)

OBJECTS = vec4.o glsl_loader.o node.o model_loader.o image.o

LIBS = -lGL -lglut -lm -lassimp -ljpeg

INCLUDES = -I/usr/include/GL

osx: vec_OSX glsl_OSX node_OSX model_loader_OSX app_OSX 

base_linux: vec_LINUX glsl_LINUX node_LINUX model_loader_LINUX image_LINUX

linux: base_linux app_LINUX

mesh_test_linux: base_linux mesh_test_LINUX

clean:
	rm $(OBJECTS) vec_test

vec_OSX:
	$(CC) $(CFLAGS) $(FRAMEWORK) -c vec4.c 

glsl_OSX:
	$(CC) $(CFLAGS) $(FRAMEWORK) -c glsl_loader.c

node_OSX:
	$(CC) $(CFLAGS) $(FRAMEWORK) -c node.c

model_loader_OSX:
	$(CC) $(CFLAGS) $(FRAMEWORK) -I./assimp/include/ -lassimp -c model_loader.c

app_OSX:
	$(CC) $(CFLAGS) $(FRAMEWORK) $(OBJECTS) -I./assimp/include/ eoe_vector_test.c -o vec_test -lassimp

vec_LINUX:
	$(CC) $(CFLAGS) $(LIBS) -c vec4.c 

glsl_LINUX:
	$(CC) $(CFLAGS) $(LIBS) -c glsl_loader.c

node_LINUX:
	$(CC) $(CFLAGS) $(LIBS) -c node.c

image_LINUX:
	$(CC) -g -c -ljpeg image.c

model_loader_LINUX:
	$(CC) $(CFLAGS) $(LIBS) -I./assimp/include/ -c model_loader.c

vertex_LINUX:
	$(CC) $(CFLAGS) $(LIBS) -c vertex.c

mesh_LINUX:
	$(CC) $(CFLAGS) $(LIBS) -c mesh.c

app_LINUX:
	$(CC) $(CFLAGS) $(LIBS) $(OBJECTS) $(INCLUDES) eoe_vector_test.c -o vec_test

mesh_test_LINUX:
	$(CC) $(CFLAGS) $(LIBS) $(OBJECTS) $(INCLUDES) mesh_test.c -o mesh_test
