#version 410

layout (location = 0) in vec3 in_position;

uniform mat4 u_projection;
uniform mat4 u_view;
uniform mat4 u_transformation;

void main()
{
	gl_Position = u_projection * u_view * u_transformation * vec4(in_position, 1.0);
}