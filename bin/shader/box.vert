#version 410

const vec3 vertices[6] = vec3[6]
(
	vec3(0, 0, 0), vec3(1, 0, 0), vec3(0, 1, 0), vec3(1, 0, 0), vec3(1, 1, 0), vec3(0, 1, 0)
);

uniform mat4 u_transformation;

void main()
{
	gl_Position = u_transformation * vec4(vertices[gl_VertexID], 1.0);
}