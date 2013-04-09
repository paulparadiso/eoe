#version 330

smooth in vec4 the_color;

out vec4 output_color;

void main()
{
	output_color = the_color;
	//output_color = vec4(1.0,0.0,0.0,0.0);
}