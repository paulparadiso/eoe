#include "mesh.h"

mesh* mesh_create(){
	mesh* m = malloc(sizeof(mesh));
	m->num_vertices = 0;
	m->num_indices = 0;
	m->vertices = malloc(1);
	m->indices = NULL;
	m->child = NULL;
	return m;
}

void mesh_add_vertex(mesh* m, vertex* v){
	m->vertices = realloc(m->vertices, sizeof(vertex));
	memcpy(m->vertices + (sizeof(vertex) * m->num_vertices), v, sizeof(vertex));
	m->num_vertices += 1;
}

void mesh_add_texture(mesh* m, texture* t){
	m->texture = t;
}

void mesh_get_vertex(mesh* m, vertex* v, int index){
	memcpy(v, m->vertices + (index - 1) * sizeof(vertex), sizeof(vertex));
}

void mesh_set_indeces(mesh* m, int num_indices, int* indices){
	if(m->indices != NULL){
		free(m->indices);
		m->indices = NULL;
	}
	m->indices = malloc(sizeof(int) * num_indices);
	memcpy(m->indices, indices, sizeof(int) * num_indices);
}