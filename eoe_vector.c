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
	//printf("squares = %f\n", squares);
	double root = sqrt(squares);
	//printf("root = %f\n", root);
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

mat4* create_mat4(){
	mat4* mat_ptr = malloc(sizeof(float) * 16);
	memset(mat_ptr, 0, sizeof(float) * 16);
	return mat_ptr;
}

void free_mat4(mat4* matrix){
	free(matrix);
}

void print_matrix(mat4* matrix){
	int i;
	for(i = 0;i < 4; i++){
		printf("%f, %f, %f, %f\n", matrix[i], matrix[i + 4], matrix[i + 8], matrix[i + 12]);
	}
}

mat4* create_id_mat4(){
	mat4* mat_ptr = create_mat4();
	mat_ptr[0] = 1.0;
	mat_ptr[5] = 1.0;
	mat_ptr[10] = 1.0;
	mat_ptr[15] = 1.0;
	return mat_ptr;
}

void mat4_set_column(int column, mat4* matrix, eoe_vec4d* vec){
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

mat4* create_rotation_mat4(float x, float y, float z, float angle){
	float c = cos(DEGREES_TO_RADIANS(angle));
	//printf("c = %f from angle = %f\n", c, angle);
	float s = sin(DEGREES_TO_RADIANS(angle));
	float t = 1.0 - c;
	mat4* rot_mat = create_id_mat4();
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