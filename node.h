#ifndef __NODE_H__
#define __NODE_H__

#include "vec4.h"
#include "image.h"

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

/*
Struct to hold model data.
*/

typedef struct mesh_data{
	GLfloat* vertex_data;
	GLushort* index_data;
	GLuint vertex_buffer_object;
	GLuint index_buffer_object;
	GLuint vao;
	GLuint texture;
	GLenum draw_mode;
	int b_indexed_draw;
	int b_has_vertex_colors;
	int color_index_offset;
	int b_has_texture;
	int texture_index_offset;
	int texture_unit;
	int sampler;
	unsigned int* mesh_offsets;
	unsigned int num_meshes;
	unsigned int num_vertices;
	unsigned int num_indeces;
} mesh_data;

/*
Struct to hold node data include model, position and transforms.
*/

typedef struct node3d{
	mesh_data* mesh;
	vec4d position;
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
Load a pre-composed image as a texture.
*/

void node3d_load_texture(node3d* node, image_buffer* img, int offset);

/*
Generate the vao that will be used to draw the model.
*/

void node3d_gen_vao(node3d* node);

/*
Generate the vbo from array of vertices and indeces.
*/

void node3d_gen_vbo(node3d* node, float* vertices, int* indeces, int i_count, int v_depth);

/*
Draw the model.
*/

void node3d_draw(node3d* node);

