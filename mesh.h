#ifndef __MESH_H__
#define __MESH_H__

#include "vertex.h"
#include "image.h"

#ifdef __APPLE__
	#include <GLUT/glut.h>
	#include <OpenGL/gl.h>
	#include <OpenGL/glu.h>
#else
	#define GL_GLEXT_PROTOTYPES
	#include "GL/gl.h"
	#include "GL/glut.h"
	#include "GL/glu.h"
	#include "GL/freeglut.h"
	#include "GL/freeglut_ext.h"
#endif

typedef struct mesh{
	int num_vertices;
	float* vertices;
	int num_indices;
	int* indices;
	struct mesh* child;
} mesh;

mesh* mesh_create();

void mesh_add_vertex(mesh* m, vertex* v);

void mesh_get_vertex(mesh* m, int i, vertex* v);

void mesh_set_indeces(mesh* m, int num_indices, int* indices);

void mesh_add_texture(mesh* m, image_buffer* buf);

#endif