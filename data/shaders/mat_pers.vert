#version 330

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 color;

smooth out vec4 theColor;

uniform vec3 offset;
uniform mat4 perspectiveMatrix;

void main()
{
    vec4 cameraPos = position + vec4(offset.x, offset.y, offset.z, 0.0);
    
    gl_Position = perspectiveMatrix * cameraPos;
    
    //gl_Position = position + vec4(0.5,0.5,-1.5,0.0);

    theColor = color;
}