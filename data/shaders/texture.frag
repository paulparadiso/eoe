#version 330

in vec2 color_coord;

uniform sampler2D color_texture;

out vec4 output_color;

void main()
{
	output_color = texture(color_texture, color_coord);
}
