#version 330

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 color;

smooth out vec4 the_color;

uniform mat4 perspective_matrix;
uniform mat4 clip_matrix;
uniform vec4 offset;

void main()
{
	vec4 camera_pos = perspective_matrix * position;

	gl_Position = clip_matrix * camera_pos;
	the_color = vec4(1.0,1.0,1.0,1.0);
}

