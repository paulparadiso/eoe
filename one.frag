#version 120

varying vec4 outputColor;
varying vec4 gl_FragCoord;

void main()
{
	float lerpValue = gl_FragCoord.y / 500.0;
		
	outputColor = mix(vec4(1.0, 1.0, 1.0, 1.0), vec4(0.2, 0.2, 0.2, 1.0), lerpValue);
}
