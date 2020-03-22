#version 410

layout (location = 0) in vec3 in_position;
layout (location = 1) in vec3 in_normal;
layout (location = 2) in vec4 in_color;

out vec4 out_color;

uniform vec3 u_directionalLightPosition;
uniform float u_directionalLightPower;
uniform float u_ambientLightPower;

void main(){
	vec3 norm = normalize(in_normal);
	float diff = max(dot(norm, normalize(u_directionalLightPosition - in_position)), 0.0);
	vec4 result = vec4(vec3(u_ambientLightPower + diff), 1.0) * in_color;

	out_color = result;
}
