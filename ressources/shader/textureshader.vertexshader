#version 330 core

layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec2 vertexUV;

out vec2 UV;

void main()
{
	gl_Position.xyz = vertexPosition_modelspace;

	UV = vertexUV;
}
