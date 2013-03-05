#include <stdio.h>
#include "GL/gl.h"
#include "GL/glut.h"

typedef struct glsl_blob{
	/*
	Vertex shader source, size, shader handle and compile error handler.
	*/
	char* v_src;
	long int v_size;
	GLuint v_shader;
	GLint v_compiled;
	/*
	Fragment shader source, size, shader handle and compile error handler.
	*/
	char* f_src;
	long int f_size;
	GLuint f_shader;
	GLint f_compiled;
	/*
	GLSL program handle.
	*/
	GLuint program;
} glsl_blob;

/*
Create a new glsl_blob.
*/

glsl_blob* glsl_create_blob();

/*
Free glsl_blob.
*/

void glsl_free_blob(glsl_blob* blob);


/*
Add shader to glsl_blob.
*/

void glsl_add_shader(GLenum shader_type, glsl_blob* blob, const char* file);

/*
Create glsl program from blob.
*/

void glsl_create_program(glsl_blob* blob);

/*
Private function to load individual shaders from blob.
*/

void glsl_compile_src(GLenum shader_type, char* src, long int src_size, GLuint* shader, GLint* compile_status, GLuint program);

/*
Use the program contained within a blob.
*/

void glsl_link_program(glsl_blob* blob);

/*
Remove any shader currently loaded.
*/

void glsl_unlink_program();