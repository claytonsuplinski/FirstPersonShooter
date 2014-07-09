/*
Name: Clayton Suplinski
ID: 906 580 2630
CS 559 Project 3

Create a cylinder object.
*/

#include <iostream>
#include "cylinder.h"

using namespace std;
using namespace glm;

//Creates a cylinder object 
Cylinder::Cylinder() : Object()
{
	this->shader_index = 0;
}


//Initializes a cylinder with the given dimensions.
bool Cylinder::Initialize(int slices, float h, float r1, float r2, char* v, char* f)
{
	if (this->GLReturnedError("Cylinder::Initialize - on entry"))
		return false;

	if (!super::Initialize())
		return false;

	if (slices < 0)
		slices = 1;

	slices *= 4;
	mat4 m;

	const vec3 n = normalize(vec3(0.5f, 1.0f, 0.0f));
	const vec4 x_axis(r1, 0.0f, 0.0f, 1.0f);
	const vec4 x_axis2(r2, 0.0f, 0.0f, 1.0f);
	const vec3 y_axis(0.0f, 1.0f, 0.0f);
	const vec3 z_axis(0.0f, h, 0.0f);
	const vec3 center(0.0f, 0.0f, 0.0f);
	const float increment =  360.0f / float(slices); 

	//Go through each slice of the cylinder and make the triangles
	for (int i = 0; i < slices; ++i){
		VertexAttributesPCN cur_vertex , nxt_vertex, dwn_vertex, dwr_vertex;
		VertexAttributesP cur_vertexN , nxt_vertexN, dwn_vertexN, dwr_vertexN;

		cur_vertex.position = vec3(m * x_axis);cur_vertex.color = color;
		cur_vertex.normal = normalize(cur_vertex.position);

		m = translate(m, z_axis);

		dwn_vertex.position = vec3(m * x_axis2);dwn_vertex.color = color;
		dwn_vertex.normal = normalize(dwn_vertex.position);

		m = translate(m, -z_axis);
		m = rotate(m, increment, y_axis);
		m = translate(m, z_axis);

		dwr_vertex.position = vec3(m * x_axis2);dwr_vertex.color = color;
		dwr_vertex.normal = normalize(dwr_vertex.position);

		m = translate(m, -z_axis);
		m = rotate(m, -increment, y_axis);	
		m = rotate(m, increment, y_axis);
		
		nxt_vertex.position = vec3(m * x_axis);
		nxt_vertex.color = color;
		nxt_vertex.normal = normalize(nxt_vertex.position);

		cur_vertexN.position = cur_vertex.normal;nxt_vertexN.position = nxt_vertex.normal;
		dwn_vertexN.position = dwn_vertex.normal;dwr_vertexN.position = dwr_vertex.normal;
		
		this->vertices.push_back(dwr_vertex);this->vertices.push_back(dwn_vertex);
		this->vertices.push_back(nxt_vertex);this->vertices.push_back(cur_vertex);

		this->normal_vertices.push_back(dwr_vertexN);this->normal_vertices.push_back(dwn_vertexN);
		this->normal_vertices.push_back(nxt_vertexN);this->normal_vertices.push_back(cur_vertexN);
	
		this->vertex_indices.push_back(this->vertices.size() - 1);
		this->vertex_indices.push_back(this->vertices.size() - 2);
		this->vertex_indices.push_back(this->vertices.size() - 3);

		this->vertex_indices.push_back(this->vertices.size() - 3);
		this->vertex_indices.push_back(this->vertices.size() - 2);
		this->vertex_indices.push_back(this->vertices.size() - 4);

		cur_vertex.normal = -cur_vertex.normal;dwr_vertex.normal = -dwr_vertex.normal;
		nxt_vertex.normal = -nxt_vertex.normal;dwn_vertex.normal = -dwn_vertex.normal;

		this->vertices.push_back(dwr_vertex);this->vertices.push_back(dwn_vertex);
		this->vertices.push_back(nxt_vertex);this->vertices.push_back(cur_vertex);
	
		this->vertex_indices.push_back(this->vertices.size() - 4);
		this->vertex_indices.push_back(this->vertices.size() - 2);
		this->vertex_indices.push_back(this->vertices.size() - 3);

		this->vertex_indices.push_back(this->vertices.size() - 3);
		this->vertex_indices.push_back(this->vertices.size() - 2);
		this->vertex_indices.push_back(this->vertices.size() - 1);

		this->normal_indices.push_back(this->vertices.size() - 1);
		this->normal_indices.push_back(this->vertices.size() - 2);
		this->normal_indices.push_back(this->vertices.size() - 3);

		this->normal_indices.push_back(this->vertices.size() - 3);
		this->normal_indices.push_back(this->vertices.size() - 2);
		this->normal_indices.push_back(this->vertices.size() - 4);

		cur_vertexN.position = -cur_vertexN.position;dwr_vertexN.position = -dwr_vertexN.position;
		dwn_vertexN.position = -dwn_vertexN.position;nxt_vertexN.position = -nxt_vertexN.position;

		this->normal_vertices.push_back(dwr_vertexN);this->normal_vertices.push_back(dwn_vertexN);
		this->normal_vertices.push_back(nxt_vertexN);this->normal_vertices.push_back(cur_vertexN);
	
		this->normal_indices.push_back(this->vertices.size() - 4);
		this->normal_indices.push_back(this->vertices.size() - 2);
		this->normal_indices.push_back(this->vertices.size() - 3);

		this->normal_indices.push_back(this->vertices.size() - 3);
		this->normal_indices.push_back(this->vertices.size() - 2);
		this->normal_indices.push_back(this->vertices.size() - 1);
	}

	if (!this->PostGLInitialize(&this->vertex_array_handle, &this->vertex_coordinate_handle, this->vertices.size() * sizeof(VertexAttributesPCN), &this->vertices[0]))
		return false;

	//Create the triangles from the vertices
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexAttributesPCN), (GLvoid *) 0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexAttributesPCN), (GLvoid *) (sizeof(vec3) * 2));	// Note offset - legacy of older code
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(VertexAttributesPCN), (GLvoid *) (sizeof(vec3) * 1));	// Same
	glEnableVertexAttribArray(0);glEnableVertexAttribArray(1);glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, 0);glBindVertexArray(0);

	//Place the normals right after the vertices in the buffer
	if (this->normal_vertices.size() > 0)
	{
		if (!this->PostGLInitialize(&this->normal_array_handle, &this->normal_coordinate_handle, this->normal_vertices.size() * sizeof(VertexAttributesP), &this->normal_vertices[0]))
			return false;

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexAttributesP), (GLvoid *) 0);
		glEnableVertexAttribArray(0);glBindBuffer(GL_ARRAY_BUFFER, 0);glBindVertexArray(0);
	}

	if (!this->phong_shader.Initialize(v,f))
		return false;

	this->shaders.push_back(&this->phong_shader);

	if (this->GLReturnedError("Cylinder::Initialize - on exit"))
		return false;

	return true;
}

//Deletes the cylinder object
void Cylinder::TakeDown()
{
	this->vertices.clear();this->shader.TakeDown();
	this->solid_color.TakeDown();
	super::TakeDown();
}

//Draw the cylinder object
void Cylinder::Draw(const mat4 & projection, mat4 modelview, const ivec2 & size, const float rotY)
{
	if (this->GLReturnedError("Cylinder::Draw - on entry"))
		return;

	glEnable(GL_DEPTH_TEST);

	//Rotate the object to face the light in the corresponding way (if rotating).
	modelview = rotate(modelview, 0.0f, vec3(1.0f, 0.0f, 0.0f));
	modelview = rotate(modelview, rotY+225, vec3(0.0f, 1.0f, 0.0f));
	mat4 mvp = projection * modelview;
	mat3 nm = inverse(transpose(mat3(modelview)));

	//Activate the current shader
	this->shaders[this->shader_index]->Use();
	this->shaders[this->shader_index]->CommonSetup(rotY, value_ptr(size), value_ptr(projection), value_ptr(modelview), value_ptr(mvp), value_ptr(nm));
	this->shaders[this->shader_index]->CustomSetup2(colorA);
	glBindVertexArray(this->vertex_array_handle);
	glDrawElements(GL_TRIANGLES , this->vertex_indices.size(), GL_UNSIGNED_INT , &this->vertex_indices[0]);
	glBindVertexArray(0);glUseProgram(0);

	if (this->GLReturnedError("Cylinder::Draw - on exit"))
		return;
}
