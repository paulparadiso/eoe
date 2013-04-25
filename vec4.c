#include "vec4.h"

void vec4d_print(vec4d* base){
	printf("_________________________\n\t%f\n\t%f\n\t%f\n\t%f\n", base->x, base->y, base->z, base->w);
}

void vec4d_copy(vec4d* to, vec4d* from){
	memcpy(to, from, 4 * sizeof(double));

}

void vec4d_neg(vec4d* dest, vec4d* src){
	dest->x = -(src->x);
	dest->y = -(src->y);
	dest->z = -(src->z);
	dest->w = -(src->w);
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
	double px = pow((a->x - b->x), 2);
	double py = pow((a->y - b->y), 2);
	double pz = pow((a->z - b->z), 2);
	double pw = pow((a->w - b->w), 2);
	return sqrt(px + py + pz + pw);
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

quat* quat_create(){
	quat* q = malloc(sizeof(quat));
	quat_set_angle(q, 0.0);
	quat_set_axis(q, 0.0,0.0,0.0);
	return q;
}

quat* quat_create_id(){
	quat* q = quat_create();
	quat_set_angle(q, 1.0);
	return q;
}

void quat_print(quat* q){
	printf("-----QUATERNION----------\n");
	printf("\tangle = %f, x = %f, y = %f, z = %f\n", q->angle, q->axis.x, q->axis.y, q->axis.z);
}

void quat_free(quat* q){
	free(q);
}

void quat_set_angle(quat* q, float angle){
	q->angle = angle;
}

float quat_get_angle(quat* q){
	return q->angle;
}

void quat_set_axis(quat* q, float x, float y, float z){
	q->axis.x = x;
	q->axis.y = y;
	q->axis.z = z;
}

void quat_set_axis_from_vec(quat* q, vec4d* v){
	q->axis = *v;
}

vec4d quat_get_axis(quat* q){
	return q->axis;
}

void quat_rotate_x(quat* q, float angle){
	float half_angle = angle * 0.5;
	q->angle = cos(half_angle);
	q->axis.x = sin(half_angle);
	q->axis.y = 0.0;
	q->axis.z = 0.0;
}

void quat_rotate_y(quat* q, float angle){
	float half_angle = angle * 0.5;
	q->angle = cos(half_angle);
	q->axis.x = 0.0;
	q->axis.y = sin(half_angle);
	q->axis.z = 0.0;
}
void quat_rotate_z(quat* q, float angle){
	float half_angle = angle * 0.5;
	q->angle = cos(half_angle);
	q->axis.x = 0.0;
	q->axis.y = 0.0;
	q->axis.z = sin(half_angle);
}

void quat_rotate_axis(quat* q, float angle, vec4d* axis){
	if(fabs(vec4d_mag(axis) - 1.0) > 0.1){
		vec4d_norm(axis, axis);
	}
	
	float half_angle = angle * 0.5;
	float sin_half_angle = sin(half_angle);

	q->angle = cos(half_angle);
	q->axis.x = axis->x * sin_half_angle;
	q->axis.y = axis->y * sin_half_angle;
	q->axis.z = axis->z * sin_half_angle;
}

float quat_dot(quat* q, quat* p){
	return q->angle * p->angle + q->axis.x * p->axis.x + q->axis.y * p->axis.y + q->axis.z * p->axis.z;
}

void quat_cross(quat* q, quat* p, quat* out){
	out->angle = q->angle  * p->angle - q->axis.x * p->axis.x - q->axis.y * p->axis.y - q->axis.z * p->axis.z;
	out->axis.x = q->angle * p->axis.x + q->axis.x * p->angle + q->axis.z * p->axis.y - q->axis.y * p->axis.z;
	out->axis.y = q->angle * p->axis.y + q->axis.y * p->angle + q->axis.x * p->axis.z - q->axis.z * p->axis.x;
	out->axis.z = q->angle * p->axis.z + q->axis.z * p->angle + q->axis.y * p->axis.x - q->axis.x * p->axis.y;
}

void quat_normalize(quat* q, quat* out){
	float mag = sqrt(pow(q->angle, 2) + pow(q->axis.x, 2) + pow(q->axis.y, 2) + pow(q->axis.z, 2));

	if(mag > 0.0){
		float one_over_mag = 1.0 / mag;
		out->angle = q->angle * one_over_mag;
		out->axis.x = q->axis.x * one_over_mag;
		out->axis.y = q->axis.y * one_over_mag;
		out->axis.z = q->axis.z * one_over_mag;
	} else {
		quat_free(out);
		out = quat_create_id();
	}
}

void quat_conjugate(quat* q, quat* out){
	out->angle = q->angle;
	out->axis.x = -q->axis.x;
	out->axis.y = -q->axis.y;
	out->axis.z = -q->axis.z;
}

void quat_pow(quat* q, float exp, quat* out){
	if(q->angle > 0.9999){
		quat_free(out);
		out = quat_create_id();
		return;
	} else {
		float alpha = acos(q->angle);
		float new_alpha = alpha * exp;
		out->axis.x = cos(new_alpha);
		float mult = sin(new_alpha) / sin(alpha);
		out->axis.x = q->axis.x * mult;
		out->axis.y = q->axis.y * mult;
		out->axis.z = q->axis.z * mult;
	}
}

void quat_slerp(quat* q, quat* p, quat* out, float t){
	if(t <= 0.0){
		*out = *q;
		return;
	}
	if(t >= 1.0){
		*out = *q;
		return;
	}
	float cos_omega = quat_dot(q, p);
	float qa = q->angle;
	float qx = q->axis.x;
	float qy = q->axis.y;
	float qz = q->axis.z;
	if(cos_omega){
		qa = -qa;
		qx = -qx;
		qy = -qy;
		qz = -qz;
		cos_omega = -cos_omega;
	}

	float k0, k1;
	if(cos_omega > 0.9999){
		k0 = 1.0 - t;
		k1 = t;
	} else {
		float sin_omega = sqrt(1.0 - pow(cos_omega, 2));
		float omega = atan2(sin_omega, cos_omega);
		float one_over_sin_omega = 1.0 / sin_omega;
		k0 = sin((1.0 - t) * omega) * one_over_sin_omega;
		k1 = sin(t * omega) * one_over_sin_omega;
	}
	out->axis.x = k0 * q->axis.x + k1 * qx;
	out->axis.y = k0 * q->axis.y + k1 * qy;
	out->axis.z = k0 * q->axis.z + k1 * qz;
	out->angle = k0 * q->angle + k1 * qa;
}