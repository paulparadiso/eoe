#include "vec4.h"

void vec4d_print(vec4d* base){
	printf("_________________________\n\t%f\n\t%f\n\t%f\n\t%f\n", base->x, base->y, base->z, base->w);
}

void vec4d_copy(vec4d* to, vec4d* from){
	memcpy(to, from, 4 * sizeof(double));

}

void vec4d_neg(vec4d* to, vec4d* from){
	to[0] = -from[0];
	to[1] = -from[1];
	to[2] = -from[2];
	to[3] = -from[3];
}

void vec4d_add(vec4d *res, vec4d *base, vec4d *m){
	res->x = base->x + m->x;
	res->y = base->y + m->y;
	res->z = base->z + m->z;
	res->w = base->w + m->w;
}

void vec4d_sub(vec4d *res, vec4d *base, vec4d *m){
	res->x = base->x + m->x;
	res->y = base->y + m->y;
	res->z = base->z + m->z;
	res->w = base->w + m->w;
}

void vec4d_scale(vec4d *res, vec4d *base, double m){
	res->x = base->x * m;
	res->y = base->y * m;
	res->z = base->z * m;
	res->w = base->w * m;
}

void vec4d_div(vec4d *res, vec4d *base, double m){
	res->x = base->x / m;
	res->y = base->y / m;
	res->z = base->z / m;
	res->w = base->w / m;
}

double vec4d_mag(vec4d * base){
	double squares = pow(base->x, 2) + pow(base->y, 2) + pow(base->z, 2) + pow(base->w, 2);
	//printf("squares = %f\n", squares);
	double root = sqrt(squares);
	//printf("root = %f\n", root);
	return root;
}

void vec4d_norm(vec4d* res, vec4d* base){
	double mag = vec4d_mag(base);
	vec4d_div(res, base, mag);
}

double vec4d_dist(vec4d* a, vec4d* b){
	double dx = a->x - b->x;
	double dy = a->y - b->y;
	double dz = a->z - b->z;
	double dw = a->w - b->w;
	return sqrt(pow(dx, 2) + pow(dy, 2) + pow(dz, 2) + pow(dw + 2));
}

double vec4d_dot(vec4d* base, vec4d* m){
	double dot = (base->x * m->x) + (base->y * m->y) + (base->z * m->z) + (base->w * m->w);
	return dot;
}

void vec4d_cross(vec4d* res, vec4d* base, vec4d* m){
	res->x = (base->y * m->z) - (base->z * m->y);
	res->y = (base->z * m->x) - (m->z * base->x);
	res->z = (base->x * m->y) - (base->y * m->x);
}

mat4* mat4_create(){
	mat4* mat_ptr = malloc(sizeof(float) * 16);
	memset(mat_ptr, 0, sizeof(float) * 16);
	return mat_ptr;
}

void mat4_free(mat4* matrix){
	free(matrix);
}

void mat4_print(mat4* matrix){
	int i;
	for(i = 0;i < 4; i++){
		printf("%f, %f, %f, %f\n", matrix[i], matrix[i + 4], matrix[i + 8], matrix[i + 12]);
	}
}

mat4* mat4_create_id(){
	mat4* mat_ptr = mat4_create();
	mat_ptr[0] = 1.0;
	mat_ptr[5] = 1.0;
	mat_ptr[10] = 1.0;
	mat_ptr[15] = 1.0;
	return mat_ptr;
}

void mat4_set_column(int column, mat4* matrix, vec4d* vec){
	int start = column * 4;
	matrix[start] = vec->x;
	matrix[start + 1] = vec->y;
	matrix[start + 2] = vec->z;
	matrix[start + 3] = vec->w;
}

void mat4_set_member(int column, char dim, double val, mat4 *matrix){
	int column_conv = column * 4;
	int member = 0;
	if(dim == 'x'){
		member = 0;
	}
	if(dim == 'y'){
		member = 1;
	}
	if(dim == 'z'){
		member = 2;
	}
	if(dim == 'w'){
		member = 3;
	}
	int index = column_conv + member;
	matrix[index] = val;
}

float mat4_get_member(int column, char dim, mat4 *matrix){
	int column_conv = column * 4;
	int member = 0;
	if(dim == 'x'){
		member = 0;
	}
	if(dim == 'y'){
		member = 1;
	}
	if(dim == 'z'){
		member = 2;
	}
	if(dim == 'w'){
		member = 3;
	}
	int index = column_conv + member;
	return matrix[index];
}

void mat4_scale(float x, float y, float z, mat4* matrix){
	mat4_set_member(0, 'x', mat4_get_member(0, 'x', matrix) * x, matrix);
	mat4_set_member(1, 'y', mat4_get_member(1, 'y', matrix) * y, matrix);
	mat4_set_member(2, 'z', mat4_get_member(2, 'z', matrix) * z, matrix);
}

mat4* mat4_from_rotation(float x, float y, float z, float angle){
	float c = cos(DEGREES_TO_RADIANS(angle));
	//printf("c = %f from angle = %f\n", c, angle);
	float s = sin(DEGREES_TO_RADIANS(angle));
	float t = 1.0 - c;
	mat4* rot_mat = mat4_create_id();
	mat4_set_member(0, 'x', t * pow(x, 2) + c, rot_mat);
	mat4_set_member(0, 'y', (t * x * y) + (z * s), rot_mat);
	mat4_set_member(0, 'z', (t * x * z) - (y * s), rot_mat);
	mat4_set_member(1, 'x', (t * x * y) - (z * s), rot_mat);
	mat4_set_member(1, 'y',  t * pow(y, 2) + c, rot_mat);
	mat4_set_member(1, 'z', (t * y * z) + (x * s), rot_mat);
	mat4_set_member(2, 'x', (t * x * z) + (y * s), rot_mat);
	mat4_set_member(2, 'y', (t * y * z) - (x * s), rot_mat);
	mat4_set_member(2, 'z',  t * pow(z, 2) + c, rot_mat);
	return rot_mat;
}