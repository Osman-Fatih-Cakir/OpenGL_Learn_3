#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 vNormal;
layout (location = 2) in vec2 vtexCoord;

uniform mat4 projection;
uniform mat4 model;
uniform mat4 view;
uniform mat4 normal_matrix;

out vec3 fNormal;
out vec3 fPos;
out vec2 ftexCoord;

void main()
{
	fNormal = mat3(normal_matrix) * vNormal;  // Multiply with normal matrix (in case of non-uniform scaling)
	fPos = vec3((view * model) * vec4(position, 1.0f));
	ftexCoord = vtexCoord;

	gl_Position = projection * view * model * vec4(position, 1.0f);
}