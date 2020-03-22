#version 410

layout (location = 0) in vec3 in_normal;
layout (location = 1) in vec4 in_color;

out vec4 out_color;

void main(){
	out_color = in_color;
}
