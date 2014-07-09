/*
Name: Clayton Suplinski
Project: First-Person Shooter
*/

#include "snow.h"

Snow::Snow() : Object(){
	this->shader_index = 0;
}

bool Snow::Initialize(int slices, float radius, char* v, char* f)
{
	if (this->GLReturnedError("Snow::Initialize - on entry"))
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
	const vec3 z_axis(0.0f, 0.0f, 1.0f);
	const vec3 center(0.0f, 0.0f, 0.0f);
	const float increment =  360.0f / float(slices); 
	int incrCount = 0;

	for (int i = 0; i < slices; ++i){
		for (int j = 0; j < slices; ++j){
			VertexAttributesPCNT cur_vertex , nxt_vertex, dwn_vertex, dwr_vertex;
			VertexAttributesP cur_vertexN , nxt_vertexN, dwn_vertexN, dwr_vertexN;
			cur_vertex.position = vec3(m * x_axis);
			cur_vertex.color = color;
			cur_vertex.normal = normalize(cur_vertex.position);
			cur_vertex.texture_coordinate = vec2(i, j);

			m = rotate(m, -increment, z_axis);

			dwn_vertex.position = vec3(m * x_axis);
			dwn_vertex.color = color;
			dwn_vertex.normal = normalize(dwn_vertex.position);
			dwn_vertex.texture_coordinate = vec2((i+1), (j));

			m = rotate(m, increment, z_axis);
			m = rotate(m, -incrCount*increment, z_axis);
			m = rotate(m, increment, y_axis);
			m = rotate(m, incrCount*increment, z_axis);
			m = rotate(m, -increment, z_axis);

			dwr_vertex.position = vec3(m * x_axis);dwr_vertex.color = color;
			dwr_vertex.normal = normalize(dwr_vertex.position);
			dwr_vertex.texture_coordinate = vec2((i+1), (j+1));

			m = rotate(m, increment, z_axis);
		
			nxt_vertex.position = vec3(m * x_axis);nxt_vertex.color = color;
			nxt_vertex.normal = normalize(nxt_vertex.position);
			nxt_vertex.texture_coordinate = vec2((i), (j+1));

			cur_vertexN.position = cur_vertex.normal;nxt_vertexN.position = nxt_vertex.normal;
			dwn_vertexN.position = dwn_vertex.normal;dwr_vertexN.position = dwr_vertex.normal;
		
			this->vertices.push_back(dwr_vertex);this->vertices.push_back(dwn_vertex);
			this->vertices.push_back(nxt_vertex);this->vertices.push_back(cur_vertex);

			this->normal_vertices.push_back(dwr_vertexN);this->normal_vertices.push_back(dwn_vertexN);
			this->normal_vertices.push_back(nxt_vertexN);this->normal_vertices.push_back(cur_vertexN);

			this->vertex_indices.push_back(this->vertices.size() - 3);
			this->vertex_indices.push_back(this->vertices.size() - 2);
			this->vertex_indices.push_back(this->vertices.size() - 4);

			this->normal_indices.push_back(this->vertices.size() - 3);
			this->normal_indices.push_back(this->vertices.size() - 2);
			this->normal_indices.push_back(this->vertices.size() - 4);
		}
		m = rotate(m, increment, z_axis);
		incrCount++;
	}

	if (!this->PostGLInitialize(&this->vertex_array_handle, &this->vertex_coordinate_handle, this->vertices.size() * sizeof(VertexAttributesPCNT), &this->vertices[0]))
		return false;

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexAttributesPCNT), (GLvoid *) 0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexAttributesPCNT), (GLvoid *) (sizeof(vec3) * 2));	
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(VertexAttributesPCNT), (GLvoid *) (sizeof(vec3) * 1));	
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(VertexAttributesPCNT), (GLvoid *) (sizeof(vec2) * 1));	
	glEnableVertexAttribArray(0); //Position
	glEnableVertexAttribArray(1); //Color
	glEnableVertexAttribArray(2); //Normal
	glEnableVertexAttribArray(3); //Texture
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	if (this->normal_vertices.size() > 0)
	{
		if (!this->PostGLInitialize(&this->normal_array_handle, &this->normal_coordinate_handle, this->normal_vertices.size() * sizeof(VertexAttributesP), &this->normal_vertices[0]))
			return false;

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexAttributesP), (GLvoid *) 0);
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	if (!this->phong_shader.Initialize(v,f))
		return false;

	this->shaders.push_back(&this->phong_shader);

	if (this->GLReturnedError("Snow::Initialize - on exit"))
		return false;

	return true;
}

void Snow::TakeDown()
{
	this->vertices.clear();this->shader.TakeDown();
	super::TakeDown();
}

void Snow::Draw(const mat4 & projection, mat4 modelview, const ivec2 & size, const float time)
{
	if (this->GLReturnedError("Snow::Draw - on entry"))
		return;

	glEnable(GL_DEPTH_TEST);

	modelview = rotate(modelview, time * 30.0f, vec3(1.0f, 0.0f, 0.0f));
	modelview = rotate(modelview, time * 120.0f, vec3(0.0f, 1.0f, 0.0f));
	mat4 mvp = projection * modelview;mat3 nm = inverse(transpose(mat3(modelview)));

	this->shaders[this->shader_index]->Use();
	this->shaders[this->shader_index]->CommonSetup(time, value_ptr(size), value_ptr(projection), value_ptr(modelview), value_ptr(mvp), value_ptr(nm));
	glBindVertexArray(this->vertex_array_handle);
	glDrawElements(GL_TRIANGLES , this->vertex_indices.size(), GL_UNSIGNED_INT , &this->vertex_indices[0]);
	glBindVertexArray(0);
	glUseProgram(0);

	if (this->GLReturnedError("Snow::Draw - on exit"))
		return;
}
