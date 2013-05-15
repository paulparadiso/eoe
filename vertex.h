#ifndef __VERTEX_H__
#define __VERTEX_H__

#include "string.h"
#include "stdlib.h"
#include "stdio.h"

typedef struct v_color{
	float r;
	float g;
	float b;
	float a;
} v_color;

typedef struct v_position{
	float x;
	float y;
	float z;
	float w;
} v_position;

typedef struct v_tex_coord{
	float u;
	float v;
} v_tex_coord;

typedef struct vertex{
	v_position p;
	v_color c;
	v_tex_coord t;
} vertex;

vertex* vertex_create();

void vertex_set_position(vertex *v, int num_elements, float* p);

void vertex_set_color(vertex *v, int num_elements, float* p);

void vertex_set_tex_coords(vertex *v, int num_elements, float* p);

void vertex_free(vertex* v);

#endif