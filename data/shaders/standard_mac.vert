#version 

attribute vec4 position;
attribute vec4 color;

varying vec4 the_color;

uniform mat4 clip_matrix;
uniform mat4 perspective_matrix;

void main()
{
	vec4 camera_pos = perspective_matrix * position;

	gl_Position = clip_matrix * camera_pos;
	the_color = color;
}
