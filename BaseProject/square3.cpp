/*
Name: Clayton Suplinski
ID: 906 580 2630
CS 559 Project 3

Creates a center-aligned textured square object
*/

#include <iostream>
#include "square3.h"

using namespace std;
using namespace glm;

Square3::Square3() : Object2(){
	this->shader_index = 0;
}

void Square3::StepShader(){
	this->shader_index = ++this->shader_index % this->shaders.size();
}

bool Square3::Initialize(int x, float s, char* filename, char* v, char* f)
{
	if (this->GLReturnedError("Square3::Initialize - on entry"))
		return false;

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

	if (!super::Initialize())
		return false;

	if (x < 1)
		x = 2;

	mat4 m;

	const vec3 n = normalize(vec3(0.5f, 1.0f, 0.0f));
	const vec4 x_axis(1.0f, 0.0f, 0.0f, 1.0f);
	const vec3 y_axis(0.0f, 1.0f, 0.0f);
	const vec3 z_axis(0.0f, 0.0f, 1.0f);
	const vec3 center(0.0f, 0.0f, 0.0f);
	const float increment =  s / float(x); 
	int incrCount = 0;

	for (int i = 0; i < x; ++i){
		for (int j = 0; j < x; ++j){
			VertexAttributes cur_vertex , nxt_vertex, dwn_vertex, dwr_vertex;			
			cur_vertex.position = vec3(m * x_axis);
			cur_vertex.normal = vec3(0,1,0);
			cur_vertex.texture_coordinate = vec2(1.0f, 1.0f);

			m = translate(m, vec3(0.0f,0.0f,-increment));
			dwn_vertex.position = vec3(m * x_axis);			
			dwn_vertex.normal = vec3(0,1,0);
			dwn_vertex.texture_coordinate = vec2(1.0f, 0.0f);

			m = translate(m, vec3(-increment, 0.0f,0.0f));
			dwr_vertex.position = vec3(m * x_axis);			
			dwr_vertex.normal = vec3(0,1,0);
			dwr_vertex.texture_coordinate = vec2(0.0f, 0.0f);
			
			m = translate(m, vec3(0.0f,0.0f,increment));
			nxt_vertex.position = vec3(m * x_axis);			
			nxt_vertex.normal = vec3(0,1,0);
			nxt_vertex.texture_coordinate = vec2(0.0f, 1.0f);
		
			this->vertices.push_back(dwr_vertex);this->vertices.push_back(dwn_vertex);
			this->vertices.push_back(nxt_vertex);this->vertices.push_back(cur_vertex);

			this->vertex_indices.push_back(this->vertices.size() - 4);
			this->vertex_indices.push_back(this->vertices.size() - 2);
			this->vertex_indices.push_back(this->vertices.size() - 3);

			this->vertex_indices.push_back(this->vertices.size() - 3);
			this->vertex_indices.push_back(this->vertices.size() - 2);
			this->vertex_indices.push_back(this->vertices.size() - 1);

			cur_vertex.normal = -cur_vertex.normal;dwn_vertex.normal = -dwn_vertex.normal;
			dwr_vertex.normal = -dwr_vertex.normal;nxt_vertex.normal = -nxt_vertex.normal;

			this->vertices.push_back(dwr_vertex);this->vertices.push_back(dwn_vertex);
			this->vertices.push_back(nxt_vertex);this->vertices.push_back(cur_vertex);

			this->vertex_indices.push_back(this->vertices.size() - 1);
			this->vertex_indices.push_back(this->vertices.size() - 2);
			this->vertex_indices.push_back(this->vertices.size() - 3);

			this->vertex_indices.push_back(this->vertices.size() - 3);
			this->vertex_indices.push_back(this->vertices.size() - 2);
			this->vertex_indices.push_back(this->vertices.size() - 4);
		}
		m = translate(m, vec3((x*increment), 0.0f,0.0f));
		m = translate(m, vec3(0.0f,0.0f,-increment));
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

	if (this->GLReturnedError("Square3::Initialize - on exit"))
		return false;

	return true;
}

void Square3::TakeDown(){super::TakeDown();}

void Square3::Draw(const mat4 & projection, mat4 modelview, const ivec2 & size, const float time)
{
	if (this->GLReturnedError("Square3::Draw - on entry"))
		return;

	mat4 mvp = projection * modelview;

	this->shaders[this->shader_index]->Use();
	TextureManager::Inst()->BindTexture(texID, 0);
	this->shaders[this->shader_index]->CommonSetup(time, value_ptr(size), value_ptr(projection), value_ptr(modelview), value_ptr(mvp), value_ptr(transpose(inverse(modelview))));
	this->shaders[this->shader_index]->CustomSetup();

	glBindVertexArray(this->vertex_array_handle);
#ifdef DRAW_POINTS
	glDrawArrays(GL_POINTS, 0, this->vertex_indices.size());
#else
	glDrawElements(GL_TRIANGLES , this->vertex_indices.size(), GL_UNSIGNED_INT , &this->vertex_indices[0]);
#endif

	glUseProgram(0);glBindVertexArray(0);

	if (this->GLReturnedError("Square3::Draw - on exit"))
		return;
}
