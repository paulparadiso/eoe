#ifndef __NODE_H__
#define __NODE_H__

#include "eoe_vector.h"

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

/*
Struct to hold model data.
*/

typedef struct mesh_data{
	float* vertex_data;
	GLuint vertex_buffer_object;
	GLuint vao;
	unsigned int* mesh_offsets;
	unsigned int num_meshes;
	unsigned int num_vertices;
} mesh_data;

/*
Struct to hold node data include model, position and transforms.
*/

typedef struct node3d{
	mesh_data* mesh;
	eoe_vec4d position;
	mat4* transform;
} node3d;

#endif

/*
Create a new node3d.
*/

node3d* node3d_create();

/*
Free a node3d
*/

void node3d_free(node3d* node);

/*
Load a node with data.  Data load method will be detemined by data_type.
*/

void node3d_load(node3d* node, void* data, int data_type);

/*
Generate the vao that will be used to draw the model.
*/

void node3d_gen_vao(node3d* node);

/*
Draw the model.
*/

void node3d_draw(node3d* node);