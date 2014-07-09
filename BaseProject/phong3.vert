/*
Name: Clayton Suplinski
Project: First-Person Shooter

A phong shader that depends on dynamic rgba input values
*/

#version 400
layout (location = 0) in vec3 VertexPosition;
layout (location = 1) in vec3 VertexNormal;

out vec4 color;
out vec3 Position;
out vec3 Normal;

uniform mat4 modelview_matrix;
uniform mat3 normal_matrix;
uniform mat4 mvp;

uniform float red;
uniform float green;
uniform float blue;
uniform float alpha;
void main()
{
color = vec4(red, green, blue, alpha);
Normal = normalize( normal_matrix * VertexNormal);
Position = vec3( modelview_matrix * vec4(VertexPosition,1.0) );
gl_Position = mvp * vec4(VertexPosition,1.0);
}