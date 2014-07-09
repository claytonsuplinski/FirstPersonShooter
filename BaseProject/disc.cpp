/*
Name: Clayton Suplinski
ID: 906 580 2630
CS 559 Project 3

Creates a disc object with a triangle fan
*/

#include <iostream>
#include "disc.h"

using namespace std;
using namespace glm;

//Create a disc object
Disc::Disc() : Object()
{
	this->shader_index = 0;
}

//Initialize a disc object with the corresponding parameters
bool Disc::Initialize(int slices, float radius, char* v, char* f)
{
	if (this->GLReturnedError("Disc::Initialize - on entry"))
		return false;

	if (!super::Initialize())
		return false;

	if (slices < 0)
		slices = 1;

	slices *= 4;
	mat4 m;

	const vec3 n = normalize(vec3(0.5f, 1.0f, 0.0f));
	const vec4 x_axis(radius, 0.0f, 0.0f, 1.0f);
	const vec3 y_axis(0.0f, 1.0f, 0.0f);
	const vec3 center(0.0f, 0.0f, 0.0f);
	const float increment =  360.0f / float(slices); 

	for (int i = 0; i < slices; ++i){
		VertexAttributesPCN cur_vertex , nxt_vertex;
		VertexAttributesP cur_vertexN, nxt_vertexN, centerN;
		cur_vertex.position = vec3(m * x_axis);
		cur_vertex.color = color;cur_vertex.normal = vec3(0,1,0);

		m = rotate(m, increment, y_axis);
		
		nxt_vertex.position = vec3(m * x_axis);nxt_vertex.color = color;
		nxt_vertex.normal = vec3(0,1,0);

		cur_vertexN.position = cur_vertex.normal;
		nxt_vertexN.position = nxt_vertex.normal;
		centerN.position = vec3(0,1,0);
		
		// Top geometry
		this->vertices.push_back(VertexAttributesPCN(center, color, vec3(0,1,0)));
		this->vertices.push_back(nxt_vertex);this->vertices.push_back(cur_vertex);

		this->normal_vertices.push_back(centerN);
		this->normal_vertices.push_back(nxt_vertexN);
		this->normal_vertices.push_back(cur_vertexN);
	
		this->vertex_indices.push_back(this->vertices.size() - 3);
		this->vertex_indices.push_back(this->vertices.size() - 1);
		this->vertex_indices.push_back(this->vertices.size() - 2);

		this->normal_indices.push_back(this->vertices.size() - 3);
		this->normal_indices.push_back(this->vertices.size() - 1);
		this->normal_indices.push_back(this->vertices.size() - 2);

		cur_vertex.normal = -cur_vertex.normal;nxt_vertex.normal = -nxt_vertex.normal;
		cur_vertexN.position = cur_vertex.normal;nxt_vertexN.position = nxt_vertex.normal;

		this->vertices.push_back(VertexAttributesPCN(center, color, vec3(0,-1,0)));
		this->vertices.push_back(nxt_vertex);
		this->vertices.push_back(cur_vertex);

		this->normal_vertices.push_back(centerN);
		this->normal_vertices.push_back(nxt_vertexN);
		this->normal_vertices.push_back(cur_vertexN);
		
		//Bottom geometry
		this->vertex_indices.push_back(this->vertices.size() - 2);
		this->vertex_indices.push_back(this->vertices.size() - 1);
		this->vertex_indices.push_back(this->vertices.size() - 3);

		this->normal_indices.push_back(this->vertices.size() - 2);
		this->normal_indices.push_back(this->vertices.size() - 1);
		this->normal_indices.push_back(this->vertices.size() - 3);
	}

	if (!this->PostGLInitialize(&this->vertex_array_handle, &this->vertex_coordinate_handle, this->vertices.size() * sizeof(VertexAttributesPCN), &this->vertices[0]))
		return false;

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexAttributesPCN), (GLvoid *) 0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexAttributesPCN), (GLvoid *) (sizeof(vec3) * 2));	// Note offset - legacy of older code
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(VertexAttributesPCN), (GLvoid *) (sizeof(vec3) * 1));	// Same
	glEnableVertexAttribArray(0);glEnableVertexAttribArray(1);glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	if (this->normal_vertices.size() > 0)
	{
		if (!this->PostGLInitialize(&this->normal_array_handle, &this->normal_coordinate_handle, this->normal_vertices.size() * sizeof(VertexAttributesP), &this->normal_vertices[0]))
			return false;

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexAttributesP), (GLvoid *) 0);
		glEnableVertexAttribArray(0);glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	if (!this->phong_shader.Initialize(v,f))
		return false;

	this->shaders.push_back(&this->phong_shader);

	if (this->GLReturnedError("Disc::Initialize - on exit"))
		return false;

	return true;
}

//Delete the disc object
void Disc::TakeDown()
{
	this->vertices.clear();this->shader.TakeDown();this->solid_color.TakeDown();
	super::TakeDown();
}

//Draw the disc object
void Disc::Draw(const mat4 & projection, mat4 modelview, const ivec2 & size, const float time)
{
	if (this->GLReturnedError("Disc::Draw - on entry"))
		return;

	glEnable(GL_DEPTH_TEST);

	modelview = rotate(modelview, time * 30.0f, vec3(1.0f, 0.0f, 0.0f));
	modelview = rotate(modelview, time * 120.0f, vec3(0.0f, 1.0f, 0.0f));
	mat4 mvp = projection * modelview;
	mat3 nm = inverse(transpose(mat3(modelview)));

	this->shaders[this->shader_index]->Use();
	this->shaders[this->shader_index]->CommonSetup(time, value_ptr(size), value_ptr(projection), value_ptr(modelview), value_ptr(mvp), value_ptr(nm));
	this->shaders[this->shader_index]->CustomSetup2(colorA);
	glBindVertexArray(this->vertex_array_handle);
	glDrawElements(GL_TRIANGLES , this->vertex_indices.size(), GL_UNSIGNED_INT , &this->vertex_indices[0]);
	glBindVertexArray(0);
	glUseProgram(0);

	if (this->GLReturnedError("Disc::Draw - on exit"))
		return;
}
