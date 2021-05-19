#version 410

layout (location = 0) in vec3 in_position;

out vec4 out_color;

uniform vec4 u_color;

void main(){
	out_color = u_color;
}
