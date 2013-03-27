#version 330

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 color;

smooth out vec4 the_color;

uniform mat4 perspective_matrix;
uniform mat4 clip_matrix;
uniform vec4 offset;

float rand(vec2 co){
    return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
}

void main()
{
	vec4 camera_pos = perspective_matrix * position;

	gl_Position = clip_matrix * camera_pos;
	//the_color = color;

	//the_color = noise4(position.x * 1000.0);
	the_color = vec4(1.0,1.0,1.0,1.0);
}

