#version 410

layout (location = 0) in vec3 in_position;
layout (location = 1) in vec3 in_normal;
layout (location = 2) in vec4 in_color;

layout (location = 0) out vec3 out_position;
layout (location = 1) out vec3 out_normal;
layout (location = 2) out vec4 out_color;

uniform mat4 u_projection;
uniform mat4 u_view;
uniform mat4 u_transformation;
  
void main(){
	out_normal = mat3(transpose(inverse(u_transformation))) * in_normal;
	out_position = vec3(u_transformation * vec4(in_position, 1.0));
	out_color = in_color;
	
	gl_Position = u_projection * u_view * vec4(out_position, 1.0);
}