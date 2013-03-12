#include <stdio.h>
#include <math.h>

typedef struct eoe_vec4d{
	double x;
	double y;
	double z;
	double w;
} eoe_vec4d;

typedef float mat4;

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

/*
Create a new matrix.
*/

mat4* create_mat4();

/*
Free a matrix.
*/

void free_matrix(mat4* matrix);

/*
Print matrix.
*/

void print_matrix(mat4* matrix);

/*
Create identity matrix.
*/

mat4* create_id_mat4();

/*
Set column to vector.
*/

void mat4_set_column(int column, mat4* matrix, eoe_vec4d* vec);

/*
Set member by column and letter.
*/

void mat4_set_member(int column, char dim, double val, mat4* matrix);