/*
Name: Clayton Suplinski
Project: First-Person Shooter
*/

#version 400
layout (location = 0) in vec3 VertexPosition;
layout (location = 1) in vec3 VertexNormal;
layout (location = 2) in vec3 vertex_color;
out vec3 color;
out vec3 Position;
out vec3 Normal;
uniform mat4 modelview_matrix;
uniform mat3 normal_matrix;
uniform mat4 projection_matrix;
uniform mat4 mvp;
void main()
{
color = vertex_color;
Normal = normalize( normal_matrix * VertexNormal);
Position = vec3( modelview_matrix * vec4(VertexPosition,1.0) );
gl_Position = mvp * vec4(VertexPosition,1.0);
}