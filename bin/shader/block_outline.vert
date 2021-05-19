#version 410

const vec3 vertices[20] = vec3[20]
(
	vec3( -0.01, -0.01, -0.01 ), vec3( 1.01, -0.01, -0.01 ), vec3( 1.01, 1.01, -0.01 ), vec3( -0.01, 1.01, -0.01 ),
	vec3( -0.01, -0.01, -0.01 ), vec3( -0.01, -0.01, -0.01 ), vec3( -0.01, -0.01, 1.01 ), vec3( -0.01, 1.01, 1.01 ),
	vec3( -0.01, 1.01, -0.01 ), vec3( -0.01, -0.01, -0.01 ), vec3( -0.01, -0.01, 1.01 ), vec3( 1.01, -0.01, 1.01 ),
	vec3( 1.01, 1.01, 1.01 ), vec3( -0.01, 1.01, 1.01 ), vec3( -0.01, -0.01, 1.01 ), vec3( 1.01, -0.01, 1.01 ),
	vec3( 1.01, 1.01, 1.01 ), vec3( 1.01, 1.01, -0.01 ), vec3( 1.01, -0.01, -0.01 ), vec3( 1.01, -0.01, 1.01 )
);

uniform mat4 u_projection;
uniform mat4 u_view;
uniform mat4 u_transformation;

void main()
{
	gl_Position = u_projection * u_view * u_transformation * vec4(vertices[gl_VertexID], 1.0);
}