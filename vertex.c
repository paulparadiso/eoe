#include "vertex.h"

vertex_list* vertex_list_create(){
	vertex_list* p_vl = malloc(sizeof(vertex_list));
	p_vl->head = malloc(sizeof(vertex_list_element));
	p_vl->head->this = NULL;
	p_vl->head->next = NULL;
	p_vl->tail = p_vl->current = p_vl->head;
}

void vertex_list_exp(vertex_list* vl){
	vl->tail->next = malloc(sizeof(vertex_list_element));
	vl->tail = vl->tail->next;
	vl->tail->this = NULL;
	vl->tail->this = NULL;
}

void vertex_list_exp_with_primitive(vertex_list* vl, int type; int size; void* data);

void vertex_list_add_primitive(vertex_list* vl, int type; int size; void* data){
	if(vl->tail->this == NULL){
		vl->tail->this = malloc(sizeof(vertex))
		vl->tail->this->this = malloc(sizeof(vertex_primitive));
	}
	if(vl->tail->this->this == NULL){
		vl->tail->this->this = malloc(sizeof(vertex_primitive));
	}
}

void vertex_list_reset(vertex_list *vl);

int vertex_list_advance(vertex_list *vl);