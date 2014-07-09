/*
Name: Clayton Suplinski
ID: 906 580 2630
CS 559 Project 3

Creates a textured square object
*/
#include <iostream>
#include "square2.h"

using namespace std;
using namespace glm;

Square2::Square2() : Object2(){
	this->shader_index = 0;
}

void Square2::StepShader(){
	this->shader_index = ++this->shader_index % this->shaders.size();
}

bool Square2::Initialize(float x, int sub, char* filename, char* vert, char* frag)
{
	if (this->GLReturnedError("Square2::Initialize - on entry"))
		return false;

	if(sub<1){sub = 1;}

#pragma region Shader code should not be here for better O.O.

	if (!this->basic_texture_shader.Initialize(vert, frag))
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

	float offset = x/sub;

	for (int i = 0; i < sub; ++i){
		for (int j = 0; j < sub; ++j){
			VertexAttributes cur_vertex , nxt_vertex, dwn_vertex, dwr_vertex;
			cur_vertex.position = vec3(i*offset + x/(2*sub), j*offset + x/(2*sub), 0.0f);
			cur_vertex.normal = vec3(0.0f, 0.0f, 1.0f);
			cur_vertex.texture_coordinate = vec2(1.0f, 1.0f);

			dwn_vertex.position = vec3(i*offset - x/(2*sub), j*offset + x/(2*sub), 0.0f);			
			dwn_vertex.normal = vec3(0.0f, 0.0f, 1.0f);
			dwn_vertex.texture_coordinate = vec2(0.0f, 1.0f);

			dwr_vertex.position = vec3(i*offset - x/(2*sub), j*offset - x/(2*sub), 0.0f);			
			dwr_vertex.normal = vec3(0.0f, 0.0f, 1.0f);
			dwr_vertex.texture_coordinate = vec2(0.0f, 0.0f);

			nxt_vertex.position = vec3(i*offset + x/(2*sub), j*offset - x/(2*sub), 0.0f);			
			nxt_vertex.normal = vec3(0.0f, 0.0f, 1.0f);
			nxt_vertex.texture_coordinate = vec2(1.0f, 0.0f);
		
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

	if (this->GLReturnedError("Square2::Initialize - on exit"))
		return false;

	return true;
}

void Square2::TakeDown(){super::TakeDown();}

void Square2::Draw(const mat4 & projection, mat4 modelview, const ivec2 & size, const float time)
{
	if (this->GLReturnedError("Square2::Draw - on entry"))
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

	glUseProgram(0);
	glBindVertexArray(0);

	if (this->GLReturnedError("Square2::Draw - on exit"))
		return;
}
