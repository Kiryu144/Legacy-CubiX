#version 410

layout (location = 0) in vec3 in_vertex;
layout (location = 1) in vec3 in_normal;
layout (location = 2) in vec4 in_color;

layout (location = 0) out vec3 out_normal;
layout (location = 1) out vec4 out_color;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 transformation;
  
void main(){
	out_normal = in_normal;
	out_color = in_color;
	gl_Position = (projection * view * transformation * vec4(in_vertex, 1));
}