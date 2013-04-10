#version 330

in vec2 c_tex_coord;

uniform sampler2D color_texture;

out vec4 output_color;

void main()
{
	output_color = texture2D(color_texture, c_tex_coord.xy);
}
