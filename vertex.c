#include "vertex.h"

vertex* vertex_create(){
	vertex* v = malloc(sizeof(vertex));
	v->p.x = 0.0;
	v->p.y = 0.0;
	v->p.z = 0.0;
	v->p.w = 1.0;
	v->c.r = 1.0;
	v->c.g = 1.0;
	v->c.b = 1.0;
	v->c.a = 1.0;
	v->t.u = 0.0;
	v->t.v = 0.0;
	return v;
}

void vertex_set_position(vertex* v, int num_elements, float* p){
	if(num_elements > 0){
		v->p.x = p[0];
	}
	if(num_elements > 1){
		v->p.y = p[1];
	}
	if(num_elements > 2){
		v->p.z = p[2];
	}
	if(num_elements > 3){
		v->p.w = p[3];
	}
}

void vertex_set_color(vertex* v, int num_elements, float* c){
	if(num_elements > 0){
		v->c.r = c[0];
	}
	if(num_elements > 1){
		v->c.g = c[1];
	}
	if(num_elements > 2){
		v->c.b = c[2];
	}
	if(num_elements > 3){
		v->c.a = c[3];
	}
}

void vertex_set_tex_coords(vertex* v, int num_elements, float *t){
	if(num_elements > 0){
		v->t.u = t[0];
	}
	if(num_elements > 1){
		v->t.v = t[1];
	}
}

void vertex_free(vertex* v){
	free(v);
}