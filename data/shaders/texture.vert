#version 330

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 tex_coord;

uniform mat4 perspective_matrix;
uniform mat4 clip_matrix;
uniform vec4 offset;

out vec2 c_tex_coord;

void main()
{
	vec4 camera_pos = perspective_matrix * position;
	gl_Position = clip_matrix * camera_pos;
	c_tex_coord = tex_coord;
}
