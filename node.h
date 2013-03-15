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
Enum for data loading.
*/

enum{
	NODE_DATA_XML = 1,
	NODE_DATA_JSON = 2
};

/*
Struct to hold model data.
*/

typedef struct mesh_data{
	float* vertex_data;
	float* index_data;
	GLuint vao;
} mesh_data;

/*
Struct to hold node data include model, position and transforms.
*/

typedef struct node3d{
	mesh_data* mesh;
	eoe_vec4d position;
	mat4* transform;
} node3d;

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