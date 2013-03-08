#include "eoe_vector.h"
#include "glsl_loader.h"
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#ifdef __APPLE__
	#include <GLUT/glut.h>
	#include <OpenGL/gl.h>
	#include <OpenGL/glu.h>
#else
	#include "GL/gl.h"
	#include "GL/glut.h"
	#include "GL/freeglut_ext.h"
#endif

/*
Shader perspective.  Not working.
*/

int b_loader_shaders = 0;
char vertex_shader[128];
char fragment_shader[128];

void compute_offsets(float * _offsets);

GLint offset_location = 2;
GLint time_location;
GLint loop_location;
GLint frag_loop_location;
GLint z_near_location;
GLint z_far_location;
GLint frustum_scale_location;

float offsets[2];

float results[2];

float time = 0.0;
float loop_duration = 5.0;
float frag_loop_duration = 2.0;

float frustum_scale = 1.0;
float z_near = 1.0;
float z_far = 3.0;

const float vertex_positions[] = {
	0.25f,  0.25f, 0.75f, 1.0f,
	 0.25f, -0.25f, 0.75f, 1.0f,
	-0.25f,  0.25f, 0.75f, 1.0f,

	 0.25f, -0.25f, 0.75f, 1.0f,
	-0.25f, -0.25f, 0.75f, 1.0f,
	-0.25f,  0.25f, 0.75f, 1.0f,

	 0.25f,  0.25f, -0.75f, 1.0f,
	-0.25f,  0.25f, -0.75f, 1.0f,
	 0.25f, -0.25f, -0.75f, 1.0f,

	 0.25f, -0.25f, -0.75f, 1.0f,
	-0.25f,  0.25f, -0.75f, 1.0f,
	-0.25f, -0.25f, -0.75f, 1.0f,

	-0.25f,  0.25f,  0.75f, 1.0f,
	-0.25f, -0.25f,  0.75f, 1.0f,
	-0.25f, -0.25f, -0.75f, 1.0f,

	-0.25f,  0.25f,  0.75f, 1.0f,
	-0.25f, -0.25f, -0.75f, 1.0f,
	-0.25f,  0.25f, -0.75f, 1.0f,

	 0.25f,  0.25f,  0.75f, 1.0f,
	 0.25f, -0.25f, -0.75f, 1.0f,
	 0.25f, -0.25f,  0.75f, 1.0f,

	 0.25f,  0.25f,  0.75f, 1.0f,
	 0.25f,  0.25f, -0.75f, 1.0f,
	 0.25f, -0.25f, -0.75f, 1.0f,

	 0.25f,  0.25f, -0.75f, 1.0f,
	 0.25f,  0.25f,  0.75f, 1.0f,
	-0.25f,  0.25f,  0.75f, 1.0f,

	 0.25f,  0.25f, -0.75f, 1.0f,
	-0.25f,  0.25f,  0.75f, 1.0f,
	-0.25f,  0.25f, -0.75f, 1.0f,

	 0.25f, -0.25f, -0.75f, 1.0f,
	-0.25f, -0.25f,  0.75f, 1.0f,
	 0.25f, -0.25f,  0.75f, 1.0f,

	 0.25f, -0.25f, -0.75f, 1.0f,
	-0.25f, -0.25f, -0.75f, 1.0f,
	-0.25f, -0.25f,  0.75f, 1.0f,




	0.0f, 0.0f, 1.0f, 1.0f,
	0.0f, 0.0f, 1.0f, 1.0f,
	0.0f, 0.0f, 1.0f, 1.0f,

	0.0f, 0.0f, 1.0f, 1.0f,
	0.0f, 0.0f, 1.0f, 1.0f,
	0.0f, 0.0f, 1.0f, 1.0f,

	0.8f, 0.8f, 0.8f, 1.0f,
	0.8f, 0.8f, 0.8f, 1.0f,
	0.8f, 0.8f, 0.8f, 1.0f,

	0.8f, 0.8f, 0.8f, 1.0f,
	0.8f, 0.8f, 0.8f, 1.0f,
	0.8f, 0.8f, 0.8f, 1.0f,

	0.0f, 1.0f, 0.0f, 1.0f,
	0.0f, 1.0f, 0.0f, 1.0f,
	0.0f, 1.0f, 0.0f, 1.0f,

	0.0f, 1.0f, 0.0f, 1.0f,
	0.0f, 1.0f, 0.0f, 1.0f,
	0.0f, 1.0f, 0.0f, 1.0f,

	0.5f, 0.5f, 0.0f, 1.0f,
	0.5f, 0.5f, 0.0f, 1.0f,
	0.5f, 0.5f, 0.0f, 1.0f,

	0.5f, 0.5f, 0.0f, 1.0f,
	0.5f, 0.5f, 0.0f, 1.0f,
	0.5f, 0.5f, 0.0f, 1.0f,

	1.0f, 0.0f, 0.0f, 1.0f,
	1.0f, 0.0f, 0.0f, 1.0f,
	1.0f, 0.0f, 0.0f, 1.0f,

	1.0f, 0.0f, 0.0f, 1.0f,
	1.0f, 0.0f, 0.0f, 1.0f,
	1.0f, 0.0f, 0.0f, 1.0f,

	0.0f, 1.0f, 1.0f, 1.0f,
	0.0f, 1.0f, 1.0f, 1.0f,
	0.0f, 1.0f, 1.0f, 1.0f,

	0.0f, 1.0f, 1.0f, 1.0f,
	0.0f, 1.0f, 1.0f, 1.0f,
	0.0f, 1.0f, 1.0f, 1.0f,
};

glsl_blob* blob;

GLuint position_buffer_object;
GLuint vao;

void init(){
	/* set clear color to black */ 
	//glClearColor (0.0, 0.0, 0.0, 0.0);

	/* set fill color to white */
	//glColor3f(1.0, 1.0, 1.0); 

	/* set up standard orthogonal view with clipping */
	/* box as cube of side 2 centered at origin */
	/* This is default view and these statement could be removed */
	//glMatrixMode (GL_PROJECTION);
	//glLoadIdentity ();
	//glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

	if(!b_loader_shaders){
		blob = glsl_create_blob();
		glsl_add_shader(GL_VERTEX_SHADER, blob, vertex_shader);
		printf("Loaded Shader:\n%s", blob->v_src);
		glsl_add_shader(GL_FRAGMENT_SHADER, blob, fragment_shader);
		printf("Loaded Shader:\n%s", blob->f_src);
		glsl_create_program(blob);
		printf("Shaders loaded.\n");
		b_loader_shaders = 1;
		offset_location = glGetUniformLocation(blob->program, "offset");
		z_far_location = glGetUniformLocation(blob->program, "z_far");
		z_near_location = glGetUniformLocation(blob->program, "z_near");
		frustum_scale_location = glGetUniformLocation(blob->program, "frustum_scale");
		printf("Uniform frustrum scale location set to %i\n", frustum_scale_location);
		printf("Uniform z_far set to %i\n", z_far_location);
		printf("Uniform offset location set to %i\n", offset_location);
		printf("Uniform z_near set to %i\n", z_near_location);
		glUseProgram(blob->program);
		glUniform1fv(frustum_scale_location, 1, &frustum_scale);
		glUniform1fv(z_far_location, 1, &z_far);
		glUniform1fv(z_near_location, 1, &z_near);
		glUseProgram(0);
	}

	initialize_vertex_buffer();

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CW);

}

void initialize_vertex_buffer()
{
	glGenBuffers(1, &position_buffer_object);
	glBindBuffer(GL_ARRAY_BUFFER, position_buffer_object);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_positions), vertex_positions, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void compute_offsets(float *_offset){
	loop_duration = 5.0f;
	const float scale = 3.14159f * 2.0f / loop_duration;

	float elapsed_time = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
	time = fmodf(elapsed_time, loop_duration);

	_offset[0] = cosf(time * scale) * 0.5f;
	_offset[1] = sinf(time * scale) * 0.5f;
}

void display(){
	//compute_offsets(offsets);
	//printf("offsets = %f, %f\n", offsets[0], offsets[1]);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	offsets[0] = 0.5;
	offsets[1] = 0.5;

	glUseProgram(blob->program);
	glUniform2fv(offset_location, 1, offsets);
	size_t color_data = sizeof(vertex_positions) / 2;
	glBindBuffer(GL_ARRAY_BUFFER, position_buffer_object);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)color_data);

	/*
	float zz = 2.0;
	glGetUniformfv(blob->program, frustrum_scale_location, &zz);
	printf("fs = %f\n", zz);
	*/

	glDrawArrays(GL_TRIANGLES, 0, 36);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glUseProgram(0);

	glutSwapBuffers();
	glutPostRedisplay();
}

void reshape (int w, int h)
{
	glViewport(0, 0, (GLsizei) w, (GLsizei) h);
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	  case 27:
		  exit(0);
	}
}

int main(int argc, char **argv){
	memset(&vertex_shader[0],0,128);
	memset(&fragment_shader[0],0,128);
	if(argc > 1){
		printf("creating new files.\n");
		sprintf(vertex_shader, "%s.vert", argv[1]);
		sprintf(fragment_shader, "%s.frag", argv[1]);
	} else {
		printf("using default files.\n");
		sprintf(vertex_shader, "%s.vert", "default");
		sprintf(fragment_shader, "%s.frag", "default");
	}
	eoe_vec4d vec1 = {.x = 2.1, 
				   	  .y = 3.2, 
				   	  .z = 45.2};
	eoe_vec4d vec1unit;
	eoe_vec4d_print(&vec1);
	eoe_vec4d_unit(&vec1unit, &vec1);
	double mag = eoe_vec4d_mag(&vec1);
	printf("Vec1 has a magnitude of %f\n", mag);
	eoe_vec4d_print(&vec1unit);
	glutInit(&argc,argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH | GLUT_STENCIL); 
	glutInitContextVersion (3, 3);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(0,0);
	glutCreateWindow(argv[0]); 
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;
}