/*
Name: Clayton Suplinski
Project: First-Person Shooter
*/

#version 400

layout (location = 0) in vec3 vertex_position;
layout (location = 3) in vec2 texture_coordinates;

uniform mat4 modelview_matrix;
uniform mat4 mvp;

out vec3 Position;
out vec2 tc;

void main()
{
	Position = vec3( modelview_matrix * vec4(vertex_position,1.0) );
	tc = texture_coordinates;
	vec3 pos = vertex_position;
	gl_Position = mvp * vec4(pos, 1.0);
}