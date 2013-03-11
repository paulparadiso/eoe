#version 120

attribute vec4 position;
attribute vec4 color;

varying vec4 the_color;

uniform vec2 offset;
uniform float z_near;
uniform float z_far;
uniform float frustum_scale;

void main()
{

    vec4 camera_pos = position + vec4(offset.x, offset.y, 0.0, 0.0);

    /*

    vec4 clip_pos;

    clip_pos.xy = camera_pos.xy * frustum_scale;

    clip_pos.z = camera_pos.z * (z_near + z_far) / (z_near - z_far);

    clip_pos.z += 2 * z_near * z_far / (z_near - z_far);

    //clip_pos.z = -camera_pos.z;

    //clip_pos.z = z_far;

    clip_pos.w = -camera_pos.z;

    */

    gl_Position = camera_pos;

    the_color = color;
}