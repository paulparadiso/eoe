#ifndef __VEC_4_H__
#define __VEC_4_H__

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#define DEGREES_TO_RADIANS(angle) ((angle) / 180.0 * M_PI)
#define RADIANS_TO_DEGREES(radians) ((radians) * (180.0 / M_PI))

typedef struct vec4d{
	double x;
	double y;
	double z;
	double w;
} vec4d;

typedef float mat4;

typedef struct quat{
	float angle;
	vec4d axis;
} quat;

/*
Print a vector's values.
*/

void vec4d_print(vec4d* base);

/*
Copy values of one vector to another.
*/

void vec4d_copy(vec4d* to, vec4d* from);

/*
Negate vector.
*/

void vec4d_neg(vec4d* to, vec4d* from);

/*
Add two vectors together.
*/


void vec4d_add(vec4d *res, vec4d *base, vec4d *m);

/*
Subtract one vect from another.  
*/

void vec4d_sub(vec4d *res, vec4d *base, vec4d *m);

/*
Scale a vector.
*/

void vec4d_scale(vec4d *res, vec4d *base, double scale);

/*
Multiply two vectors together.
*/

void vec4d_div(vec4d *res, vec4d *base, double m);

/*
Calculate magnitude of vector.
*/

double vec4d_mag(vec4d *base);

/*
Return a vector representing the unit vector.
*/

void vec4d_norm(vec4d* res, vec4d* base);

/*
Calculate distance between to vectors.
*/

double vec4d_dist(vec4d* a, vec4d* b);

/*
Return the dot product of two vectors.
*/

double vec4d_dot(vec4d* base, vec4d* m);

/*
Cross product of two vectors.
*/

void vec4d_cross(vec4d* res, vec4d* base, vec4d* m);

/*
Create a new matrix.
*/

mat4* mat4_create();

/*
Free a matrix.
*/

void mat4_free(mat4* matrix);

/*
Print matrix.
*/

void mat4_print(mat4* matrix);

/*
Create identity matrix.
*/

mat4* mat4_create_id();

/*
Set column to vector.
*/

void mat4_set_column(int column, mat4* matrix, vec4d* vec);

/*
Set member by column and letter.
*/

void mat4_set_member(int column, char dim, double val, mat4* matrix);

/*
Get member by column and letter.
*/

float mat4_get_member(int column, char dim, mat4* matrix);

/*
Scale matrix.
*/

void mat4_scale(float x, float y, float z, mat4* matrix);

/*
Rotation matrix.
*/

mat4* mat4_from_rotation(float x, float y, float z, float angle);

/*
Create a blank quaternion.
*/


quat* quat_create();

/*
print.
*/

void quat_print(quat* q);

/*
Free.
*/

void quat_free(quat* q);

/*
Create an identity quaternion.
*/

quat* quat_create_id();

/*
Set and get quaternion angle.
*/

void quat_set_angle(quat* q, float angle);
float quat_get_angle(quat* q);

/*
Set and get Quaternion axis.
*/

void quat_set_axis(quat* q, float x, float y, float z);
vec4d quat_get_axis(quat* q);

/*
Rotation functions.
*/

void quat_rotate_x(quat* q, float angle);
void quat_rotate_y(quat* q, float angle);
void quat_rotate_z(quat* q, float angle);
void quat_rotate_axis(quat* q, float angle, vec4d* axis);

/*
Products.
*/

float quat_dot(quat* q, quat* p);
void quat_cross(quat* q, quat* p, quat* out);

/*
Normalize.
*/

void quat_normalize(quat* q, quat* out);

/*
Conjugate.
*/

void quat_conjugate(quat* q, quat* out);

/*
Exponential.
*/

void quat_pow(quat* q, float exp, quat* out);

/*
Slerp.
*/

void quat_slerp(quat* q, quat* p, quat* out, float t);

#endif