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

#define ARRAY_COUNT( array ) (sizeof( array ) / (sizeof( array[0] ) * (sizeof( array ) != sizeof(void*) || sizeof( array[0] ) <= sizeof(void*))))


int b_loader_shaders = 0;
int matrix_size = 16;
char vertex_shader[128];
char fragment_shader[128];

void compute_offsets(float * _offsets);

GLint offset_location = 2;
GLint matrix_location;

float offsets[3];
float results[2];

float perspective_matrix[16];

float frustum_scale = 0.5f; 
float z_near = 0.5f; 
float z_far = 3.0f;

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

const int number_of_vertices = 36;

#define RIGHT_EXTENT 0.8f
#define LEFT_EXTENT -RIGHT_EXTENT
#define TOP_EXTENT 0.20f
#define MIDDLE_EXTENT 0.0f
#define BOTTOM_EXTENT -TOP_EXTENT
#define FRONT_EXTENT -1.25f
#define REAR_EXTENT -1.75f

#define GREEN_COLOR 0.75f, 0.75f, 1.0f, 1.0f
#define BLUE_COLOR 	0.0f, 0.5f, 0.0f, 1.0f
#define RED_COLOR 1.0f, 0.0f, 0.0f, 1.0f
#define GREY_COLOR 0.8f, 0.8f, 0.8f, 1.0f
#define BROWN_COLOR 0.5f, 0.5f, 0.0f, 1.0f

const float vertex_data[] = {
	//Object 1 positions
	LEFT_EXTENT,	TOP_EXTENT,		REAR_EXTENT,
	LEFT_EXTENT,	MIDDLE_EXTENT,	FRONT_EXTENT,
	RIGHT_EXTENT,	MIDDLE_EXTENT,	FRONT_EXTENT,
	RIGHT_EXTENT,	TOP_EXTENT,		REAR_EXTENT,

	LEFT_EXTENT,	BOTTOM_EXTENT,	REAR_EXTENT,
	LEFT_EXTENT,	MIDDLE_EXTENT,	FRONT_EXTENT,
	RIGHT_EXTENT,	MIDDLE_EXTENT,	FRONT_EXTENT,
	RIGHT_EXTENT,	BOTTOM_EXTENT,	REAR_EXTENT,

	LEFT_EXTENT,	TOP_EXTENT,		REAR_EXTENT,
	LEFT_EXTENT,	MIDDLE_EXTENT,	FRONT_EXTENT,
	LEFT_EXTENT,	BOTTOM_EXTENT,	REAR_EXTENT,

	RIGHT_EXTENT,	TOP_EXTENT,		REAR_EXTENT,
	RIGHT_EXTENT,	MIDDLE_EXTENT,	FRONT_EXTENT,
	RIGHT_EXTENT,	BOTTOM_EXTENT,	REAR_EXTENT,

	LEFT_EXTENT,	BOTTOM_EXTENT,	REAR_EXTENT,
	LEFT_EXTENT,	TOP_EXTENT,		REAR_EXTENT,
	RIGHT_EXTENT,	TOP_EXTENT,		REAR_EXTENT,
	RIGHT_EXTENT,	BOTTOM_EXTENT,	REAR_EXTENT,

	//Object 2 positions
	TOP_EXTENT,		RIGHT_EXTENT,	REAR_EXTENT,
	MIDDLE_EXTENT,	RIGHT_EXTENT,	FRONT_EXTENT,
	MIDDLE_EXTENT,	LEFT_EXTENT,	FRONT_EXTENT,
	TOP_EXTENT,		LEFT_EXTENT,	REAR_EXTENT,

	BOTTOM_EXTENT,	RIGHT_EXTENT,	REAR_EXTENT,
	MIDDLE_EXTENT,	RIGHT_EXTENT,	FRONT_EXTENT,
	MIDDLE_EXTENT,	LEFT_EXTENT,	FRONT_EXTENT,
	BOTTOM_EXTENT,	LEFT_EXTENT,	REAR_EXTENT,

	TOP_EXTENT,		RIGHT_EXTENT,	REAR_EXTENT,
	MIDDLE_EXTENT,	RIGHT_EXTENT,	FRONT_EXTENT,
	BOTTOM_EXTENT,	RIGHT_EXTENT,	REAR_EXTENT,
					
	TOP_EXTENT,		LEFT_EXTENT,	REAR_EXTENT,
	MIDDLE_EXTENT,	LEFT_EXTENT,	FRONT_EXTENT,
	BOTTOM_EXTENT,	LEFT_EXTENT,	REAR_EXTENT,
					
	BOTTOM_EXTENT,	RIGHT_EXTENT,	REAR_EXTENT,
	TOP_EXTENT,		RIGHT_EXTENT,	REAR_EXTENT,
	TOP_EXTENT,		LEFT_EXTENT,	REAR_EXTENT,
	BOTTOM_EXTENT,	LEFT_EXTENT,	REAR_EXTENT,

	//Object 1 colors
	GREEN_COLOR,
	GREEN_COLOR,
	GREEN_COLOR,
	GREEN_COLOR,

	BLUE_COLOR,
	BLUE_COLOR,
	BLUE_COLOR,
	BLUE_COLOR,

	RED_COLOR,
	RED_COLOR,
	RED_COLOR,

	GREY_COLOR,
	GREY_COLOR,
	GREY_COLOR,

	BROWN_COLOR,
	BROWN_COLOR,
	BROWN_COLOR,
	BROWN_COLOR,

	//Object 2 colors
	RED_COLOR,
	RED_COLOR,
	RED_COLOR,
	RED_COLOR,

	BROWN_COLOR,
	BROWN_COLOR,
	BROWN_COLOR,
	BROWN_COLOR,

	BLUE_COLOR,
	BLUE_COLOR,
	BLUE_COLOR,

	GREEN_COLOR,
	GREEN_COLOR,
	GREEN_COLOR,

	GREY_COLOR,
	GREY_COLOR,
	GREY_COLOR,
	GREY_COLOR,
};

const GLshort index_data[] = {
	0, 2, 1,
	3, 2, 0,

	4, 5, 6,
	6, 7, 4,

	8, 9, 10,
	11, 13, 12,

	14, 16, 15,
	17, 16, 14,
};

glsl_blob* blob;

GLuint position_buffer_object;
GLuint vertex_buffer_object;
GLuint index_buffer_object;
GLuint vao1;
GLuint vao2;

void initialize_vertex_buffer()
{
	glGenBuffers(1, &vertex_buffer_object);
	
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_data), vertex_data, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &index_buffer_object);

	glBindBuffer(GL_ARRAY_BUFFER, index_buffer_object);
	glBufferData(GL_ARRAY_BUFFER, sizeof(index_data), index_data, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

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

	memset(perspective_matrix, 0, sizeof(float) * matrix_size);
	perspective_matrix[0] = frustum_scale;
	perspective_matrix[5] = frustum_scale;
	perspective_matrix[10] = (z_far + z_near) / (z_near - z_far);
	perspective_matrix[14] = (2 * z_far * z_near) / (z_near - z_far);
	perspective_matrix[11] = -1.0f;

	if(!b_loader_shaders){
		blob = glsl_create_blob();
		glsl_add_shader(GL_VERTEX_SHADER, blob, vertex_shader);
		printf("Loaded Shader:\n%s", blob->v_src);
		glsl_add_shader(GL_FRAGMENT_SHADER, blob, fragment_shader);
		printf("Loaded Shader:\n%s", blob->f_src);
		glsl_create_program(blob);
		printf("Shaders loaded.\n");
		b_loader_shaders = 1;
		//offset_location = glGetUniformLocation(blob->program, "offset");
		//matrix_location = glGetUniformLocation(blob->program, "perspectiveMatrix");
		//printf("Uniform offset location set to %i\n", offset_location);
		//printf("Uniform matrix set to %i\n", matrix_location);
		
		glUseProgram(blob->program);
		glUniformMatrix4fv(matrix_location, 1, GL_FALSE, perspective_matrix);
		glUseProgram(0);
	}

	printf("SHADERS INITTED\n");

	initialize_vertex_buffer();

	glGenVertexArrays(1, &vao1);
	glBindVertexArray(vao1);
    
    size_t color_data_offset = sizeof(float) * 3 * number_of_vertices;
    
    glBindBuffer(GL_ARRAY_BUFFER, position_buffer_object);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)color_data_offset);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer_object);
    
    glBindVertexArray(0);
    
    glGenVertexArrays(1, &vao2);
    glBindVertexArray(vao2);
    
    size_t pos_data_offset = sizeof(float) * 3 * (number_of_vertices/2);
    color_data_offset += sizeof(float) * 4 * (number_of_vertices/2);

	glEnable(GL_DEPTH_TEST);
	
	glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CW);

    printf("INIT DONE\n");
	
}

float loop_duration = 0.0;
float scale = 0.0;
float time = 0.0;

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

	offsets[0] = 0.0;
	offsets[1] = 0.0;

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	printf("Binding VAO1\n");

	glUseProgram(blob->program);
	glBindVertexArray(vao1);

	printf("VAO1 bound\n");

	offsets[2] = 0.0;
	glUniform3fv(offset_location, 1, offsets);

	printf("drawing vao1\n");

	//glDrawElements(GL_TRIANGLES, ARRAY_COUNT(index_data), GL_UNSIGNED_SHORT, 0);

	printf("vao1 drawn\n");

	printf("Binding VAO2\n");

	glBindVertexArray(vao2);
    offsets[2] = -1.0;
	glUniform3fv(offset_location, 1, offsets);
    glDrawElements(GL_TRIANGLES, ARRAY_COUNT(index_data), GL_UNSIGNED_SHORT, 0);

    glBindVertexArray(0);
    glUseProgram(0);

	glutSwapBuffers();
	glutPostRedisplay();

}

void reshape (int w, int h)
{
	perspective_matrix[0] = frustum_scale / (w / (float)h);
	perspective_matrix[5] = frustum_scale;

	glUseProgram(blob->program);
	glUniformMatrix4fv(matrix_location, 1, GL_FALSE, perspective_matrix);

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

void mouse(int button, int state, int x, int y){
	//printf("Mouse:\n\t:%i\n\t:%i\n\t:%i\n\t:%i\n", button, state, x, y);
}

void mouse_motion(int x, int y){
	//printf("Mouse Movement:\n\t:%i\n\t%i\n", x, y);
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
	//glutInitContextVersion (3, 3);
	//glutInitContextProfile(GLUT_CORE_PROFILE);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(0,0);
	glutCreateWindow(argv[0]); 
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutMotionFunc(mouse_motion);
	glutPassiveMotionFunc(mouse_motion);

	/*

	glewInit();
    if (glewIsSupported("GL_VERSION_3_3"))
        printf("Ready for OpenGL 3.3\n");
    else {
        printf("OpenGL 3.0 not supported\n");
        exit(1);
    }

	*/

	glutMainLoop();
	return 0;
}