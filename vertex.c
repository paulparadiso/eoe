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
	if(vl->tail->v == NULL){
		vl->tail->v = malloc(sizeof(vertex))
	}
	vertex_add_primitive(vl->tail->v, type, size, data);
}

void vertex_add_primitive(vertex* v, int type, int size, void* data){
	if(v->vp == NULL){}
}

void vertex_list_reset(vertex_list *vl);

int vertex_list_advance(vertex_list *vl);