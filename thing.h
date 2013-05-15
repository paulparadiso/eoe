#include "mesh.h"
#include "vertex.h"

typedef struct thing{
	mesh* m;
	vec4d pos;
	mat4 transform;
} thing;

thing* thing_create();

void thing_set_mesh_from_file(thing *t, const char* file_name);

