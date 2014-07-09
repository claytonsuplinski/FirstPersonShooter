/*
Name: Clayton Suplinski
ID: 906 580 2630
CS 559 Project 3

Makes a textured sphere
*/


#include <iostream>
#include "sphere2.h"

using namespace std;
using namespace glm;

Sphere2::Sphere2() : Object2(){
	this->shader_index = 0;
}

void Sphere2::StepShader(){
	this->shader_index = ++this->shader_index % this->shaders.size();
}

bool Sphere2::Initialize(int slices, float radius, char* filename, char* v, char* f)
{
	if (this->GLReturnedError("Sphere2::Initialize - on entry"))
		return false;

	if(slices<1){slices = 1;}

#pragma region Shader code should not be here for better O.O.

	if (!this->basic_texture_shader.Initialize(v,f))
		return false;

	this->shaders.push_back(&this->basic_texture_shader);
#pragma endregion

#pragma region Code to make FreeImage work

	if (!TextureManager::Inst()->LoadTexture((const char *) filename, texID))
		return false;

	glTexEnvf(GL_TEXTURE_ENV , GL_TEXTURE_ENV_MODE , GL_REPLACE);
	glTexParameterf(GL_TEXTURE_2D , GL_TEXTURE_WRAP_S , GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D , GL_TEXTURE_WRAP_T , GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D , GL_TEXTURE_MAG_FILTER , GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D , GL_TEXTURE_MIN_FILTER , GL_LINEAR);
#pragma endregion

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
	int changeDir = 0;

	for (int i = 0; i < slices; ++i){
		for (int j = 0; j < slices; ++j){
			VertexAttributes cur_vertex , nxt_vertex, dwn_vertex, dwr_vertex;

			cur_vertex.position = vec3(m * x_axis);
			cur_vertex.normal = normalize(cur_vertex.position);
			cur_vertex.texture_coordinate = vec2(0.5 + atan(2*dot(cur_vertex.normal.x, cur_vertex.normal.z))/(2*3.14),
				0.5 - 2*asin(cur_vertex.normal.y)/(2*3.14));

			m = rotate(m, -increment, z_axis);

			dwn_vertex.position = vec3(m * x_axis);
			dwn_vertex.normal = normalize(dwn_vertex.position);
			dwn_vertex.texture_coordinate = vec2(0.5 + atan(2*dot(dwn_vertex.normal.x, dwn_vertex.normal.z))/(2*3.14),
				0.5 - 2*asin(dwn_vertex.normal.y)/(2*3.14));
			
			m = rotate(m, increment, z_axis);
			m = rotate(m, -incrCount*increment, z_axis);
			m = rotate(m, increment, y_axis);
			m = rotate(m, incrCount*increment, z_axis);
			m = rotate(m, -increment, z_axis);

			dwr_vertex.position = vec3(m * x_axis);
			dwr_vertex.normal = normalize(dwr_vertex.position);
			dwr_vertex.texture_coordinate = vec2(0.5 + atan(2*dot(dwr_vertex.normal.x, dwr_vertex.normal.z))/(2*3.14),
				0.5 - 2*asin(dwr_vertex.normal.y)/(2*3.14));

			m = rotate(m, increment, z_axis);
		
			nxt_vertex.position = vec3(m * x_axis);
			nxt_vertex.normal = normalize(nxt_vertex.position);
			nxt_vertex.texture_coordinate = vec2(0.5 + atan(2*dot(nxt_vertex.normal.x, nxt_vertex.normal.z))/(2*3.14),
				0.5 - 2*asin(nxt_vertex.normal.y)/(2*3.14));
		
			this->vertices.push_back(dwr_vertex);
			this->vertices.push_back(dwn_vertex);
			this->vertices.push_back(nxt_vertex);
			this->vertices.push_back(cur_vertex);
	
			this->vertex_indices.push_back(this->vertices.size() - 1);
			this->vertex_indices.push_back(this->vertices.size() - 2);
			this->vertex_indices.push_back(this->vertices.size() - 3);

			this->vertex_indices.push_back(this->vertices.size() - 3);
			this->vertex_indices.push_back(this->vertices.size() - 2);
			this->vertex_indices.push_back(this->vertices.size() - 4);

			changeDir++;
		}
		m = rotate(m, increment, z_axis);
		incrCount++;
	}

	if (!this->PostGLInitialize(&this->vertex_array_handle, &this->vertex_coordinate_handle, this->vertices.size() * sizeof(VertexAttributes), &this->vertices[0]))
		return false;

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexAttributes), (GLvoid *) 0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexAttributes), (GLvoid *) (sizeof(vec3)));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(VertexAttributes), (GLvoid *) (sizeof(vec3) * 2));
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(VertexAttributes), (GLvoid *) (sizeof(vec3) * 3));

	//	Each of the attributes to be used must be enabled.
	glEnableVertexAttribArray(0);glEnableVertexAttribArray(1);glEnableVertexAttribArray(2);glEnableVertexAttribArray(3);

	glBindBuffer(GL_ARRAY_BUFFER, 0);glBindVertexArray(0);

	if (this->GLReturnedError("Sphere2::Initialize - on exit"))
		return false;

	return true;
}

void Sphere2::TakeDown(){super::TakeDown();}

void Sphere2::Draw(const mat4 & projection, mat4 modelview, const ivec2 & size, const float time)
{
	if (this->GLReturnedError("Sphere2::Draw - on entry"))
		return;

	modelview = rotate(modelview, time * 90.0f, vec3(0.0f, 1.0f, 0.0f));
	mat4 mvp = projection * modelview;
	mat3 nm = inverse(transpose(mat3(modelview)));

	this->shaders[this->shader_index]->Use();
	TextureManager::Inst()->BindTexture(texID, 0);
	this->shaders[this->shader_index]->CommonSetup(time, value_ptr(size), value_ptr(projection), value_ptr(modelview), value_ptr(mvp), value_ptr(nm));
	this->shaders[this->shader_index]->CustomSetup();

	glBindVertexArray(this->vertex_array_handle);
#ifdef DRAW_POINTS
	glDrawArrays(GL_POINTS, 0, this->vertex_indices.size());
#else
	glDrawElements(GL_TRIANGLES , this->vertex_indices.size(), GL_UNSIGNED_INT , &this->vertex_indices[0]);
#endif

	glUseProgram(0);glBindVertexArray(0);

	if (this->GLReturnedError("Sphere2::Draw - on exit"))
		return;
}
