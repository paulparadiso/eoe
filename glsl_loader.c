#include "glsl_loader.h"

#include <stdio.h>
#ifdef __APPLE__
	#include <GLUT/glut.h>
	#include <OpenGL/gl.h>
	#include <OpenGL/glu.h>
#else
	#include "GL/gl.h"
	#include "GL/glut.h"
	#include <GL/glew.h>
#endif
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

glsl_blob* glsl_create_blob(){
	glsl_blob *blob = malloc(sizeof(glsl_blob));
	blob->v_src = NULL;
	blob->v_size = 0;
	blob->v_shader = glCreateShader(GL_VERTEX_SHADER);
	printf("added shader - %i.\n", blob->v_shader);
	blob->f_src = NULL;
	blob->f_size = 0;
	blob->f_shader = glCreateShader(GL_FRAGMENT_SHADER);
	printf("added shader - %i.\n", blob->f_shader);
	blob->program = glCreateProgram();
	return blob;
}

void glsl_free_blob(glsl_blob* blob){
	free(blob->v_src);
	free(blob->f_src);
	free(blob);
}

void glsl_add_shader(GLenum shader_type, glsl_blob* blob, const char* file){
	printf("adding shader - %s", file);
	FILE* glsl_file = fopen(file, "r");
	char** shader_ptr;
	long int *size_ptr;	
	if(shader_type == GL_VERTEX_SHADER){
		printf("Setting vertex shader.\n");
		shader_ptr = &blob->v_src;
		size_ptr = &blob->v_size;
	} else {
		printf("Setting fragment shader.\n");
		shader_ptr = &blob->f_src;
		size_ptr = &blob->f_size;
	}
	//long int file_size;
	//fseek(glsl_file, 0, SEEK_END);
	//file_size = ftell(glsl_file);
	//rewind(glsl_file);
	//free(shader_ptr);
	struct stat f_stat;
	if(fstat(fileno(glsl_file), &f_stat) < 0){
		printf("error statting file.\n");
		return;
	}
	long int file_size = f_stat.st_size;
	printf("%s size = %i\n", file, file_size);
	*shader_ptr = calloc(file_size + 1, sizeof(char));	
	*size_ptr = file_size;
	fread(*shader_ptr, sizeof(char), file_size, glsl_file);
	fclose(glsl_file);
}

void glsl_create_program(glsl_blob* blob){
	int b_link_program = 0;
	if(blob->v_src != NULL){
		glsl_compile_src(GL_VERTEX_SHADER, blob->v_src, blob->v_size, &blob->v_shader, &blob->v_compiled, blob->program);
		b_link_program = 1;
	} else {
		printf("No vertex shader.\n");
	}
	if(blob->f_src != NULL){
		glsl_compile_src(GL_FRAGMENT_SHADER, blob->f_src, blob->f_size, &blob->f_shader, &blob->f_compiled, blob->program);
		b_link_program = 1;
	} else {
		printf("No fragment shader.\n");
	}
	if(b_link_program){
		printf("Linking program.\n");
		GLint status;
		glLinkProgram(blob->program);
		glGetProgramiv (blob->program, GL_LINK_STATUS, &status);
		if(status == GL_FALSE){
			printf("Linking failed.\n");
			GLint infoLogLength;
			glGetProgramiv(blob->program, GL_INFO_LOG_LENGTH, &infoLogLength);
			char *strInfoLog = calloc(infoLogLength + 1, sizeof(char));
			glGetProgramInfoLog(blob->program, infoLogLength, NULL, strInfoLog);
			printf("Linker failure: %s\n", strInfoLog);
			free(strInfoLog);
		} else {
			printf("Linking succeeded.\n");
		}
	}
}

void glsl_compile_src(GLenum shader_type, char* src, long int src_size, GLuint* shader, GLint* compile_status, GLuint program){
	printf("compiling shader - %i.\n%s", *shader, src);
	glShaderSource(*shader, 1, &src, &src_size);
	glCompileShader(*shader);
	glGetObjectParameterivARB(*shader, GL_COMPILE_STATUS, compile_status);
	if(*compile_status == GL_FALSE){
		printf("compile status = %i\n", *compile_status);
		GLint blen = 0;	
		GLsizei slen = 0;
		glGetShaderiv(*shader, GL_INFO_LOG_LENGTH , &blen);
		printf("BLEN = %i\n", blen);
		if (blen > 1){	
			GLchar* compiler_log = (GLchar*)malloc(blen);
			glGetInfoLogARB(*shader, blen, &slen, compiler_log);
			printf("Shader failed to compile:\n\t%s", compiler_log);
			free (compiler_log);
		}	
	} else {
		printf("Shader compiled.\n");
		glAttachShader(program, *shader);
	}
}

void glsl_link_program(glsl_blob* blob){
	glLinkProgram(blob->program);
}

void glsl_unlink_program(){
	glLinkProgram(0);
}