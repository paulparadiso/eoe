#include "eoe_vector.h"
#include "glsl_loader.h"
#include <stdio.h>
#ifdef __APPLE__
	#include <GLUT/glut.h>
	#include <OpenGL/gl.h>
	#include <OpenGL/glu.h>
#else
	#include "GL/gl.h"
	#include "GL/glut.h"
#endif

int b_loader_shaders = 0;

void init(){
	/* set clear color to black */ 
	glClearColor (0.0, 0.0, 0.0, 0.0);

	/* set fill color to white */
	glColor3f(1.0, 1.0, 1.0); 

	/* set up standard orthogonal view with clipping */
	/* box as cube of side 2 centered at origin */
	/* This is default view and these statement could be removed */
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
}

void display(){

	/* clear window */
	glClear(GL_COLOR_BUFFER_BIT); 

	/* draw unit square polygon */
	glBegin(GL_POLYGON);
	glVertex2f(-0.5, -0.5);
	glVertex2f(-0.5, 0.5);
	glVertex2f(0.5, 0.5);
	glVertex2f(0.5, -0.5);
	glEnd();

	/* flush GL buffers */
	glFlush(); 

	if(!b_loader_shaders){
		glsl_blob* blob = glsl_create_blob();
		glsl_add_shader(GL_VERTEX_SHADER, blob, "one.vert");
		printf("Loaded Shader:\n%s", blob->v_src);
		//glsl_add_shader(GL_FRAGMENT_SHADER, blob, "one.frag");
		//printf("Loaded Shader:\n%s", blob->f_src);
		glsl_create_program(blob);
		printf("Shaders loaded.\n");
		b_loader_shaders = 1;
	}
}

int main(int argc, char **argv){
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
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB); 
	glutInitWindowSize(500,500);
	glutInitWindowPosition(0,0);
	glutCreateWindow("simple"); 
	glutDisplayFunc(display);
	init();
	glutMainLoop();
	return 0;
}