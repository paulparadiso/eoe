#include "eoe_vector.h"

void eoe_vec4d_print(eoe_vec4d* base){
	printf("_________________________\n\t%f\n\t%f\n\t%f\n\t%f\n", base->x, base->y, base->z, base->w);
}

void eoe_vec4d_add(eoe_vec4d *res, eoe_vec4d *base, eoe_vec4d *m){
	res->x = base->x + m->x;
	res->y = base->y + m->y;
	res->z = base->z + m->z;
	res->w = base->w + m->w;
}

void eoe_vec4d_sub(eoe_vec4d *res, eoe_vec4d *base, eoe_vec4d *m){
	res->x = base->x + m->x;
	res->y = base->y + m->y;
	res->z = base->z + m->z;
	res->w = base->w + m->w;
}

void eoe_vec4d_scale(eoe_vec4d *res, eoe_vec4d *base, double m){
	res->x = base->x * m;
	res->y = base->y * m;
	res->z = base->z * m;
	res->w = base->w * m;
}

void eoe_vec4d_div(eoe_vec4d *res, eoe_vec4d *base, double m){
	res->x = base->x / m;
	res->y = base->y / m;
	res->z = base->z / m;
	res->w = base->w / m;
}

double eoe_vec4d_mag(eoe_vec4d * base){
	double squares = pow(base->x, 2) + pow(base->y, 2) + pow(base->z, 2) + pow(base->w, 2);
	printf("squares = %f\n", squares);
	double root = sqrt(squares);
	printf("root = %f\n", root);
	return root;
}

void eoe_vec4d_unit(eoe_vec4d* res, eoe_vec4d* base){
	double mag = eoe_vec4d_mag(base);
	eoe_vec4d_div(res, base, mag);
}

double eoe_vec4d_dot(eoe_vec4d* base, eoe_vec4d* m){
	double dot = (base->x * m->x) + (base->y * m->y) + (base->z * m->z) + (base->w * m->w);
	return dot;
}

void eoe_vec4d_cross(eoe_vec4d* res, eoe_vec4d* base, eoe_vec4d* m){
	res->x = (base->y * m->z) - (base->z * m->y);
	res->y = (base->z * m->x) - (m->z * base->x);
	res->z = (base->x * m->y) - (base->y * m->x);
}