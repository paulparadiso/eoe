#include "node.h"

node3d* node3d_create(){
	node3d* node = malloc(sizeof(node3d));
	node->transform = create_id_mat4();
	node->position.x = 0.0;
	node->position.y = 0.0;
	node->position.z = 0.0;
	node->position.w = 1.0;
	node->mesh = malloc(sizeof(mesh_data));
	return node;
}

void node3d_free(node3d* node){
	free(node->mesh->vertex_data);
	free(node->mesh->mesh_offsets);
	free_mat4(node->transform);
	free(node);
}

void node3d_load(node3d* node, void* data, int data_type){}

void node3d_gen_vao(node3d* node){
	
	glGenBuffers(1, &node->mesh->vertex_buffer_object);
	glBindBuffer(GL_ARRAY_BUFFER, node->mesh->vertex_buffer_object);
	glBufferData(GL_ARRAY_BUFFER, node->mesh->num_vertices * 3, node->mesh->vertex_data, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	printf("Node has buffer - %i\n", node->mesh->vertex_buffer_object);

	/*
	glGenVertexArrays(1, &node->mesh->vao);
	glBindBuffer(GL_ARRAY_BUFFER, node->mesh->vertex_buffer_object);
	glEnableVertexAttribArray(0, 3, GL_FLOAT, GL_FALSE, 0, 0); 
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	*/
}

void node3d_draw(node3d* node){
	int i;
	glBindBuffer(GL_ARRAY_BUFFER, node->mesh->vertex_buffer_object);
	/*
	for(i = 0; i < node->mesh->num_meshes; i++){
		int num_points;
		if(i < node->mesh->num_meshes - 2){
			num_points = node->mesh->mesh_offsets[i + 1] - node->mesh->mesh_offsets[i];
		} else {
			num_points = node->mesh->num_vertices - node->mesh->mesh_offsets[i];
		}
		//glDrawElementsBaseVertex(GL_POINTS, num_points, GL_UNSIGNED_SHORT, 0, node->mesh->mesh_offsets[i]);
		//int b = node->mesh->mesh_offsets[i];
		//int s = node->mesh->mesh_offsets[i] + num_points;
		//printf("drawing from %i to %i\n", b, s);
		glDrawArrays(GL_POINTS, b, s);
	}
	*/
	//glVertexPointer(3, GL_FLOAT, 0, node->mesh->)
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_POLYGON, 0, node->mesh->num_vertices);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
