/*
Name: Clayton Suplinski
ID: 906 580 2630
CS 559 Project 3

Texture shader - Used almost everywhere in 
the project for applying images to shapes. Also
changes to correspond with the time of day and 
environment.
*/
#version 400

layout (location = 0) in vec3 vertex_position;
layout (location = 2) in vec3 VertexNormal;
layout (location = 3) in vec2 texture_coordinates;

uniform mat4 modelview_matrix;
uniform mat3 normal_matrix;
//uniform mat4 projection_matrix;
uniform mat4 mvp;
uniform ivec2 size;
uniform float time;

out vec3 Position;
out vec3 Normal;
out vec2 tc;

uniform sampler2D picture;

void main()
{
	Normal = normalize( normal_matrix * VertexNormal);
	Position = vec3( modelview_matrix * vec4(vertex_position,1.0) );
	vec2 t = texture_coordinates;
	float ct = size.y;
	/*t.x += 0.01;//sin(ct/100000);
	if(t.x < 0){
		t.x = t.x + 1;
	}
	if(t.x > 1){
		t.x = t.x - 1;
	}*/
	tc = t;

	/*vec4 color = texture(picture, tc);
	ct = 0;
	if(color.x < 0.225 && color.y < 0.225 && color.z < 0.225){
		ct = 1;
	}*/
	
	vec3 pos = vec3(vertex_position.x, vertex_position.y, vertex_position.z);
	gl_Position = mvp * vec4(pos, 1.0);
}