#include <stdio.h>
#include <math.h>

typedef struct eoe_vec4d{
	double x;
	double y;
	double z;
	double w;
} eoe_vec4d;

typedef double eoe_mat4d[16];

/*
Print a vector's values.
*/

void eoe_vec4d_print(eoe_vec4d* base);

/*
Add two vectors together.
*/

void eoe_vec4d_add(eoe_vec4d *res, eoe_vec4d *base, eoe_vec4d *m);

/*
Subtract one vect from another.  
*/

void eoe_vec4d_sub(eoe_vec4d *res, eoe_vec4d *base, eoe_vec4d *m);

/*
Scale a vector.
*/

void eoe_vec4d_scale(eoe_vec4d *res, eoe_vec4d *base, double scale);

/*
Multiply two vectors together.
*/

void eoe_vec4d_div(eoe_vec4d *res, eoe_vec4d *base, double m);

/*
Calculate magnitude of vector.
*/

double eoe_vec4d_mag(eoe_vec4d *base);

/*
Return a vector representing the unit vector.
*/

void eoe_vec4d_unit(eoe_vec4d* res, eoe_vec4d* base);

/*
Return the dot product of two vectors.
*/

double eoe_vec4d_dot(eoe_vec4d* base, eoe_vec4d* m);

/*
Cross product of two vectors.
*/

void eoe_vec4d_cross(eoe_vec4d* res, eoe_vec4d* base, eoe_vec4d* m);