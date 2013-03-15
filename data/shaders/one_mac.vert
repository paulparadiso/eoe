#version 330

attribute vec4 position;
attribute vec4 color;

uniform vec2 offset;

void main()
{
    vec4 totalOffset = vec4(offset.x, offset.y, 0.0, 0.0);

    gl_Position = position + totalOffset;
}