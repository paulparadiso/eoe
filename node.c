#include "node.h"

node3d* node3d_create(){
	node3d* node = malloc(sizeof(node3d));
	node->transform = create_id_mat4();
	node->position.x = 0.0;
	node->position.y = 0.0;
	node->position.z = 0.0;
	node->position.w = 1.0;
}

void node3d_free(node3d* node){}

void node3d_load(node3d* node, void* data, int data_type){}