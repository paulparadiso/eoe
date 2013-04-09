#include "vec4.h"
#include "glsl_loader.h"
#include "node.h"
#include "model_loader.h"
#include "image.h"
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#ifdef __APPLE__
	#include <GLUT/glut.h>
	#include <OpenGL/gl.h>
	#include <OpenGL/glu.h>
#else
	#define GL_GLEXT_PROTOTYPES
	#include "GL/gl.h"
	#include "GL/glut.h"
	#include "GL/glu.h"
	#include "GL/freeglut.h"
	#include "GL/freeglut_ext.h"
#endif

#define ARRAY_COUNT( array ) (sizeof( array ) / (sizeof( array[0] ) * (sizeof( array ) != sizeof(void*) || sizeof( array[0] ) <= sizeof(void*))))

#define SCROLL_UP 3
#define SCROLL_DOWN 4
#define Z_MAX 10.0
#define Z_MIN -200.0
#define Z_DELTA 0.01

void compute_offsets(float * _offsets);
float calc_frustum_scale(float fov_deg);
void construct_matrix(mat4 matrix);

int b_loader_shaders = 0;
int matrix_size = 16;
char vertex_shader[128];
char fragment_shader[128];

GLint clip_matrix_location;
GLint perspective_matrix_location;
GLint rotation_matrix_location;
GLint offset_location;

float offsets[4];
float offsets2[3];
float results[2];

mat4* perspective_matrix;
mat4* camera_to_clip_matrix;

float z_near = 1.0f; 
float z_far = 3.0f;

int b_depth_clamping_active = 1;

int width = 500;
int height = 500;

node3d* goblin;

node3d* cube;

node3d* plane;

image_buffer image;

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

const GLfloat cube_vertex_positions[] = {
	/*0*/ -0.5,  0.5, -0.5, // vertex
	/*1*/  0.5,  0.5, -0.5, // vertex
	/*2*/  0.5,  0.5,  0.5, // vertex
	/*3*/ -0.5,  0.5,  0.5, // vertex
	/*4*/ -0.5, -0.5, -0.5, // vertex
	/*5*/  0.5, -0.5, -0.5, // vertex
	/*6*/  0.5, -0.5,  0.5, // vertex
	/*7*/ -0.5, -0.5,  0.5, // vertex
	/*0*/  1.0,  0.0,  0.0, // color
	/*1*/  0.0,  1.0,  0.0, // color
	/*2*/  0.0,  0.0,  1.0, // color
	/*3*/  1.0,  1.0,  0.0, // color
	/*4*/  0.0,  1.0,  1.0, // color
	/*5*/  1.0,  0.0,  1.0, // color
	/*6*/  1.0,  1.0,  1.0, // color
	/*7*/  1.0,  0.0,  0.0, // color
};

const GLfloat plane_vertex_positions[] = {
	-0.5, 0.5, -0.5,
	 0.5, 0.5, -0.5,
	 0.5, 0.5,  0.5,
	-0.5, 0.5, 	0.5,
	 -0.5, 0.5, -0.5,
	 0.5, 0.5, -0.5,
	 0.5, 0.5,  0.5,
	-0.5, 0.5, 	0.5,
};	

const GLfloat cube_vertex_positions2[] = {
	-1.0, -1.0,  1.0,
    1.0, -1.0,  1.0,
    -1.0,  1.0,  1.0,
    1.0,  1.0,  1.0,
    -1.0, -1.0, -1.0,
    1.0, -1.0, -1.0,
    -1.0,  1.0, -1.0,
    1.0,  1.0, -1.0,
};

/*
const int cube_index_data2[] = {
	0, 1, 2,
	2, 3, 0,
	0, 3, 4,
	4, 7, 3,
	3, 2, 7,
	7, 6, 2,
	2, 1, 6,
	6, 5, 1,
	1, 0, 4,
	4, 5, 1,
	4, 5, 6,
	6, 7, 4
};
*/

const GLshort cube_index_data[] = {
	0, 1, 2,
	2, 3, 0,
	0, 3, 4,
	4, 7, 3,
	3, 2, 7,
	7, 6, 2,
	2, 1, 6,
	6, 5, 1,
	1, 0, 4,
	4, 5, 1,
	4, 5, 6,
	6, 7, 4	
};

const GLshort plane_index_data[] = {
	0, 1, 2,
	2, 3, 0,
};

const GLushort cube_index_data2[] = {
	0, 1, 2,
	2, 3, 0,
	0, 3, 4,
	4, 7, 3,
	3, 2, 7,
	7, 6, 2,
	2, 1, 6,
	6, 5, 1,
	1, 0, 4,
	4, 5, 1,
	4, 5, 6,
	6, 7, 4	
	/*4, 7, 3,*/
};

int nci = 36;

const int number_of_vertices = 8;

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
	+1.0f, +1.0f, +1.0f,
	-1.0f, -1.0f, +1.0f,
	-1.0f, +1.0f, -1.0f,
	+1.0f, -1.0f, -1.0f,

	-1.0f, -1.0f, -1.0f,
	+1.0f, +1.0f, -1.0f,
	+1.0f, -1.0f, +1.0f,
	-1.0f, +1.0f, +1.0f,

	GREEN_COLOR,
	BLUE_COLOR,
	RED_COLOR,
	BROWN_COLOR,

	GREEN_COLOR,
	BLUE_COLOR,
	RED_COLOR,
	BROWN_COLOR,
};

const GLushort index_data[] = {
	0, 1, 2,
	1, 0, 3,
	2, 3, 0,
	3, 2, 1,

	5, 4, 6,
	4, 5, 7,
	7, 6, 4,
	6, 7, 5,
};

glsl_blob* blob;

GLuint position_buffer_object;
GLuint vertex_buffer_object;
GLuint index_buffer_object;
GLuint vao1;
GLuint vao2;

GLuint texture;

float rot = 0.0;

float calc_frustum_scale(float fov_deg){
    const float deg_to_rad = 3.14159f * 2.0f / 360.0f;
    float fov_rad = fov_deg * deg_to_rad;
    return 1.0f / tan(fov_rad / 2.0f);
}

float frustum_scale; 

void initialize_vertex_buffer(){
	glGenBuffers(1, &vertex_buffer_object);
	
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_data), vertex_data, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &index_buffer_object);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer_object);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index_data), index_data, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
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

	perspective_matrix = mat4_create_id();
	camera_to_clip_matrix = mat4_create_id();
	//frustum_scale = calc_frustum_scale(-45.0);
	frustum_scale = 1.0;
	mat4_set_member(0,'x', frustum_scale, camera_to_clip_matrix);
	mat4_set_member(1,'y', frustum_scale, camera_to_clip_matrix);
	double factor = (z_far + z_near) / (z_near - z_far);
	mat4_set_member(2,'z', factor, camera_to_clip_matrix);
	mat4_set_member(2,'w', -1.0, camera_to_clip_matrix);
	factor = (2 * z_far * z_near) / (z_near - z_far);
	mat4_set_member(3,'z', factor, camera_to_clip_matrix);
	//mat4_scale(0.1,0.1,0.1, camera_to_clip_matrix);
	mat4_print(camera_to_clip_matrix);

	if(!b_loader_shaders){
		blob = glsl_create_blob();
		glsl_add_shader(GL_VERTEX_SHADER, blob, vertex_shader);
		printf("Loaded Shader:\n%s", blob->v_src);
		glsl_add_shader(GL_FRAGMENT_SHADER, blob, fragment_shader);
		printf("Loaded Shader:\n%s", blob->f_src);
		glsl_create_program(blob);
		printf("Shaders loaded.\n");
		b_loader_shaders = 1;
		clip_matrix_location = glGetUniformLocation(blob->program, "clip_matrix");
		perspective_matrix_location = glGetUniformLocation(blob->program, "perspective_matrix");
		rotation_matrix_location = glGetUniformLocation(blob->program, "rot_matrix");
		offset_location = glGetUniformLocation(blob->program, "offset");
		//printf("Uniform offset location set to %i\n", offset_location);
		//printf("Uniform matrix set to %i\n", matrix_location);
		
		glUseProgram(blob->program);
		glUniformMatrix4fv(clip_matrix_location, 1, GL_FALSE, camera_to_clip_matrix);
		glUseProgram(0);
	}

	glEnable(GL_DEPTH_TEST);
	if(b_depth_clamping_active){
		glEnable(GL_DEPTH_CLAMP);
	}

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_POLYGON_SMOOTH);

	glDepthMask(GL_TRUE);
	glDepthFunc(GL_LEQUAL);
	glDepthRange(0.0f, 1.0f);

	//glEnable(GL_CULL_FACE);
    //glCullFace(GL_BACK);
    //glFrontFace(GL_CW);

	printf("OpenGL version - %s\n", glGetString(GL_VERSION));

	image_open("../images/8610413449_693cf0505d_m.jpg", &image);

	cube = node3d_create();
	cube->mesh->vertex_data = cube_vertex_positions;
	cube->mesh->index_data = cube_index_data2;
	cube->mesh->draw_mode = GL_TRIANGLES;
	cube->mesh->b_indexed_draw = 1;
	cube->mesh->b_has_vertex_colors = 1;
	cube->mesh->num_vertices = 24;
	cube->mesh->num_indeces = nci;

	plane = node3d_create();
	plane->mesh->vertex_data = plane_vertex_positions;
	plane->mesh->index_data = plane_index_data;
	plane->mesh->draw_mode = GL_TRIANGLES;
	plane->mesh->b_indexed_draw = 1;
	plane->mesh->b_has_vertex_colors = 1;
	plane->mesh->num_vertices = 12;
	plane->mesh->num_indeces = 6;
	glUseProgram(blob->program);
	plane->mesh->texture_unit = glGetUniformLocation(blob->program, "gaussianTexture");
	glUniform1i(plane->mesh->texture_unit, 0);
	glUseProgram(0);
	node3d_load_texture(plane, &image, 0);

	node3d_gen_vao(cube);	
	node3d_gen_vao(plane);
	//node3d_gen_vbo(cube, cube_vertex_positions, cube_index_data2, nci, 3);
	/*

	initialize_vertex_buffer();

	glGenVertexArrays(1, &vao1);

	glBindVertexArray(vao1);
    
    size_t color_data_offset = sizeof(float) * 3 * number_of_vertices;
    
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)color_data_offset);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer_object);

    glBindVertexArray(0);

	*/

    /*
    int e = glGetError();
	printf("GL error - %s\n", gluErrorString(e));
	*/

	//glPolygonMode ( GL_FRONT_AND_BACK, GL_LINE ) ;

    offsets[0] = 0.0;
    offsets[1] = 0.0;
    offsets[2] = -2.0;
    offsets[3] = 1.0;
}

float loop_duration = 0.0;
float scale = 0.0;
float time = 0.0;

void construct_matrix(mat4 matrix){

}

void compute_offsets(float *_offset){
	loop_duration = 1.0f;
	const float scale = 3.14159f * 2.0f / loop_duration;

	float elapsed_time = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
	time = fmodf(elapsed_time, loop_duration);

	//_offset[0] = cosf(time * scale) * 0.5f;
	//_offset[1] = sinf(time * scale) * 0.5f;
	_offset[0] = sinf(time * scale) * 0.5f;
	//printf("offset z = %f\n", _offset[2]);
}

void display(){
	//compute_offsets(offsets);
	//printf("offsets = %f, %f\n", offsets[0], offsets[1]);

	//offsets[0] = 0.0;
	//offsets[1] = 0.0;

	/*
	mat4_set_member(3, 'x', offsets[0], perspective_matrix);
	mat4_set_member(3, 'y', offsets[1], perspective_matrix);
	mat4_set_member(3, 'z', offsets[2], perspective_matrix);
	*/

	/*
	mat4_set_member(3, 'x', offsets2[0], camera_to_clip_matrix);
	mat4_set_member(3, 'y', offsets2[1], camera_to_clip_matrix);
	mat4_set_member(3, 'z', offsets2[2], camera_to_clip_matrix);
	*/

	//glBindVertexArray(vao1);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(blob->program);
		
	//offsets[2] = 0.8;
	//glUniform3fv(offset_location, 1, offsets);
	
	rot += 0.5;
	if(rot > 360.0){
		rot = 0.0;
	}

	mat4* rot_mat = mat4_from_rotation(0.0,1.0,0.0,rot);
	//mat4* rot_mat = create_id_mat4();
	vec4d vec1 = {.x = offsets[0], 
				   	  .y = offsets[1], 
				   	  .z = offsets[2],
				   	  .w = offsets[3]};
	mat4_set_column(3, rot_mat, &vec1);
	//print_matrix(rot_mat);

	//glUniformMatrix4fv(clip_matrix_location, 1, GL_FALSE, camera_to_clip_matrix);
	glUniformMatrix4fv(perspective_matrix_location, 1, GL_FALSE, rot_mat);
	//glUniform4fv(offset_location, 1, offsets);
	//glUniformMatrix4fv(rotation_matrix_location, 1, GL_FALSE, rot_mat);

	//node3d_draw(goblin);
	//node3d_draw(cube);
	node3d_draw(plane);
	GLenum gl_error = glGetError();
	if(gl_error > 0){
		printf("GL error = %i\n", gl_error);
	}

	mat4_free(rot_mat);

	//glDrawElements(GL_TRIANGLES, ARRAY_COUNT(index_data), GL_UNSIGNED_SHORT, 0);

	//node3d_draw(goblin);

    //float offsets2[3] = {0.0,0.0,0.8};
	//glUniform3fv(offset_location, 1, offsets);
    //glDrawElementsBaseVertex(GL_TRIANGLES, ARRAY_COUNT(index_data), GL_UNSIGNED_SHORT, 0, number_of_vertices / 2);

    //glBindVertexArray(0);
    glUseProgram(0);

	glutSwapBuffers();
	glutPostRedisplay();

}

void reshape (int w, int h)
{
	width = w;
	height = h;
	
	mat4_set_member(0, 'x', frustum_scale / (w / (float)h), perspective_matrix);
	mat4_set_member(1, 'y', frustum_scale, perspective_matrix);

	perspective_matrix[0] = frustum_scale / (w / (float)h);
	perspective_matrix[5] = frustum_scale;

	glUseProgram(blob->program);
	glUniformMatrix4fv(perspective_matrix_location, 1, GL_FALSE, perspective_matrix);
	glUseProgram(0);

	glViewport(0, 0, (GLsizei) w, (GLsizei) h);
}

void keyboard(unsigned char key, int x, int y)
{
	printf("Keyboard key = %i\n", key);
	switch (key)
	{
		case 27:
			exit(0);
		case 32:
			if(b_depth_clamping_active){
				glDisable(GL_DEPTH_CLAMP);
			}
			else{
				glEnable(GL_DEPTH_CLAMP);
        	}
        	b_depth_clamping_active = !b_depth_clamping_active;
        	break;
        default:
        	break;
    }
}

void mouse(int button, int state, int x, int y){
	printf("Mouse:\n\t:%i\n\t:%i\n\t:%i\n\t:%i\n", button, state, x, y);
	if(button == SCROLL_UP){
		offsets[2] += Z_DELTA;
		if(offsets[2] > Z_MAX){
			offsets[2] = Z_MAX;
		}
		printf("Z = %f\n", offsets[2]);
	}
	if(button == SCROLL_DOWN){
		offsets[2] -= Z_DELTA;
		if(offsets[2] < Z_MIN){
			offsets[2] = Z_MIN;
		}
		printf("Z = %f\n", offsets[2]);
	}
}

void mouse_motion(int x, int y){
	//printf("Mouse Movement:\n\t:%i\n\t%i\n", x, y);
	offsets[0] = ((((float)x / (float)width) * 10.0) - 5.0);
	offsets[1] = ((((float)y / (float)height) * 10.0) - 5.0) * -1.0;
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
	vec4d vec1 = {.x = 2.1, 
				   	  .y = 3.2, 
				   	  .z = 45.2};
	vec4d vec1norm;
	vec4d_print(&vec1);
	vec4d_norm(&vec1norm, &vec1);
	double mag = vec4d_mag(&vec1);
	printf("Vec1 has a magnitude of %f\n", mag);
	vec4d_print(&vec1norm);

	glutInit(&argc,argv);
	#ifdef __APPLE__
		glutInitDisplayMode (GLUT_3_2_CORE_PROFILE | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH | GLUT_STENCIL); 
	#else
		glutInitDisplayMode (GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH | GLUT_STENCIL);
	#endif
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

	//goblin = load_model("data/models/goblin_obj.obj");

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