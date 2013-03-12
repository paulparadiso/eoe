#version 330

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 color;

smooth out vec4 the_color;

uniform mat4 perspective_matrix;
uniform mat4 clip_matrix;

void main()
{
	vec4 camera_pos = perspective_matrix * position;

	gl_Position = clip_matrix * camera_pos;
	the_color = color;
}
