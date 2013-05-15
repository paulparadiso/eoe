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

glsl_blob* blob;

void init(){
}

void display(){

	glClearColor(1.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/*
	Draw meshes.
	*/

	glutSwapBuffers();
	glutPostRedisplay();

}

void reshape (int w, int h){
}

void keyboard(unsigned char key, int x, int y){
}

void mouse(int button, int state, int x, int y){
}

void mouse_motion(int x, int y){
}

int main(int argc, char **argv){

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
	glutMainLoop();
	return 0;
}