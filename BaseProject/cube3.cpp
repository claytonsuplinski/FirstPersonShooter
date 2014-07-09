/*
Name: Clayton Suplinski
ID: 906 580 2630
CS 559 Project 2

Creates a cube object
*/

#include <iostream>
#include "cube3.h"

using namespace std;
using namespace glm;

//Creates a cube object
Cube3::Cube3() : Object2()
{
	this->shader_index = 0;
}

//Initialize a cube with the given dimensions
bool Cube3::Initialize(float l, float w, float h, char* filename, char* v, char* f)
{
	if (this->GLReturnedError("Cube3::Initialize - on entry"))
		return false;

	if (!super::Initialize())
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

	const vec3 n = normalize(vec3(0.5f, 1.0f, 0.0f));

	VertexAttributes buR, buL, fuR, fuL , bdL, bdR, fdL, fdR; // (b/f = back/front, u/d = up/down, L/R = left/right)

	float uX = l/2;float uY = w;float uZ = h/2;
	float bX = -l/2;float bY = 0;float bZ = -h/2;

	//d = back; u = front; b = up; f = down; R = right; L = left
		
	fdL.position = vec3(bX,bY,bZ);
	fdR.position = vec3(uX,bY,bZ);
	bdL.position = vec3(bX,uY,bZ);
	fuL.position = vec3(bX,bY,uZ);
	buR.position = vec3(uX,uY,uZ);
	buL.position = vec3(bX,uY,uZ);
	fuR.position = vec3(uX,bY,uZ);
	bdR.position = vec3(uX,uY,bZ);

	//Back Face
	fdL.normal = vec3(0,0,-1);
	fdR.normal = vec3(0,0,-1);
	bdR.normal = vec3(0,0,-1);
	bdL.normal = vec3(0,0,-1);
	fdL.texture_coordinate = vec2(1,0);
	fdR.texture_coordinate = vec2(0,0);
	bdR.texture_coordinate = vec2(0,1);
	bdL.texture_coordinate = vec2(1,1);
	fdL.color = vec3(1,1,0);
	fdR.color = vec3(1,1,0);
	bdR.color = vec3(1,1,0);
	bdL.color = vec3(1,1,0);
	this->vertices.push_back(bdL);
	this->vertices.push_back(bdR);
	this->vertices.push_back(fdL);
	this->vertex_indices.push_back(this->vertices.size() - 3); 
	this->vertex_indices.push_back(this->vertices.size() - 2); 
	this->vertex_indices.push_back(this->vertices.size() - 1); 

	this->vertices.push_back(fdL);
	this->vertices.push_back(bdR);
	this->vertices.push_back(fdR);
	this->vertex_indices.push_back(this->vertices.size() - 3); 
	this->vertex_indices.push_back(this->vertices.size() - 2); 
	this->vertex_indices.push_back(this->vertices.size() - 1);	

	//Front Face
	fuL.normal = vec3(0,0,1);
	fuR.normal = vec3(0,0,1);
	buL.normal = vec3(0,0,1);
	buR.normal = vec3(0,0,1);
	fuL.texture_coordinate = vec2(0,0);
	fuR.texture_coordinate = vec2(1,0);
	buL.texture_coordinate = vec2(0,1);
	buR.texture_coordinate = vec2(1,1);
	fuL.color = vec3(1,0,0);
	fuR.color = vec3(1,0,0);
	buR.color = vec3(1,0,0);
	buL.color = vec3(1,0,0);
	this->vertices.push_back(fuL);
	this->vertices.push_back(fuR);
	this->vertices.push_back(buL);
	this->vertex_indices.push_back(this->vertices.size() - 3); 
	this->vertex_indices.push_back(this->vertices.size() - 2); 
	this->vertex_indices.push_back(this->vertices.size() - 1);

	
	this->vertices.push_back(buL);
	this->vertices.push_back(fuR);
	this->vertices.push_back(buR);
	this->vertex_indices.push_back(this->vertices.size() - 3); 
	this->vertex_indices.push_back(this->vertices.size() - 2); 
	this->vertex_indices.push_back(this->vertices.size() - 1);

	//Bottom Face
	fdL.normal = vec3(0,-1,0);
	fdR.normal = vec3(0,-1,0);
	fuR.normal = vec3(0,-1,0);
	fuL.normal = vec3(0,-1,0);
	fdL.texture_coordinate = vec2(0,0);
	fdR.texture_coordinate = vec2(1,0);
	fuR.texture_coordinate = vec2(1,1);
	fuL.texture_coordinate = vec2(0,1);
	fdL.color = vec3(1,1,1);
	fdR.color = vec3(1,1,1);
	fuR.color = vec3(1,1,1);
	fuL.color = vec3(1,1,1);
	this->vertices.push_back(fdL);
	this->vertices.push_back(fdR);
	this->vertices.push_back(fuL);
	this->vertex_indices.push_back(this->vertices.size() - 3); 
	this->vertex_indices.push_back(this->vertices.size() - 2); 
	this->vertex_indices.push_back(this->vertices.size() - 1);

	this->vertices.push_back(fuL);
	this->vertices.push_back(fdR);
	this->vertices.push_back(fuR);
	this->vertex_indices.push_back(this->vertices.size() - 3); 
	this->vertex_indices.push_back(this->vertices.size() - 2); 
	this->vertex_indices.push_back(this->vertices.size() - 1);

	//Left Face
	fdR.normal = vec3(1,0,0);
	bdR.normal = vec3(1,0,0);
	buR.normal = vec3(1,0,0);
	fuR.normal = vec3(1,0,0);
	fdR.texture_coordinate = vec2(1,0);
	bdR.texture_coordinate = vec2(1,1);
	buR.texture_coordinate = vec2(0,1);
	fuR.texture_coordinate = vec2(0,0);
	fuR.color = vec3(0,1,0);
	fdR.color = vec3(0,1,0);
	buR.color = vec3(0,1,0);
	bdR.color = vec3(0,1,0);
	this->vertices.push_back(fdR);
	this->vertices.push_back(bdR);
	this->vertices.push_back(fuR);
	this->vertex_indices.push_back(this->vertices.size() - 3); 
	this->vertex_indices.push_back(this->vertices.size() - 2); 
	this->vertex_indices.push_back(this->vertices.size() - 1);

	this->vertices.push_back(fuR);
	this->vertices.push_back(bdR);
	this->vertices.push_back(buR);
	this->vertex_indices.push_back(this->vertices.size() - 3); 
	this->vertex_indices.push_back(this->vertices.size() - 2); 
	this->vertex_indices.push_back(this->vertices.size() - 1);

	//Top Face
	bdR.normal = vec3(0,1,0);
	bdL.normal = vec3(0,1,0);
	buL.normal = vec3(0,1,0);
	buR.normal = vec3(0,1,0);
	bdR.texture_coordinate = vec2(0,1);
	bdL.texture_coordinate = vec2(0,0);
	buL.texture_coordinate = vec2(1,0);
	buR.texture_coordinate = vec2(1,1);
	buL.color = vec3(1,0,1);
	buR.color = vec3(1,0,1);
	bdR.color = vec3(1,0,1);
	bdL.color = vec3(1,0,1);
	this->vertices.push_back(bdR);
	this->vertices.push_back(bdL);
	this->vertices.push_back(buR);
	this->vertex_indices.push_back(this->vertices.size() - 3); 
	this->vertex_indices.push_back(this->vertices.size() - 2); 
	this->vertex_indices.push_back(this->vertices.size() - 1);

	this->vertices.push_back(buR);
	this->vertices.push_back(bdL);
	this->vertices.push_back(buL);
	this->vertex_indices.push_back(this->vertices.size() - 3); 
	this->vertex_indices.push_back(this->vertices.size() - 2); 
	this->vertex_indices.push_back(this->vertices.size() - 1);

	//Right Face
	bdL.normal = vec3(-1,0,0);
	fdL.normal = vec3(-1,0,0);
	buL.normal = vec3(-1,0,0);
	fuL.normal = vec3(-1,0,0);
	bdL.texture_coordinate = vec2(0,1);
	fdL.texture_coordinate = vec2(0,0);
	buL.texture_coordinate = vec2(1,1);
	fuL.texture_coordinate = vec2(1,0);
	fuL.color = vec3(0,0,1);
	fdL.color = vec3(0,0,1);
	buL.color = vec3(0,0,1);
	bdL.color = vec3(0,0,1);
	this->vertices.push_back(bdL);
	this->vertices.push_back(fdL);
	this->vertices.push_back(buL);
	this->vertex_indices.push_back(this->vertices.size() - 3); 
	this->vertex_indices.push_back(this->vertices.size() - 2); 
	this->vertex_indices.push_back(this->vertices.size() - 1);

	this->vertices.push_back(buL);
	this->vertices.push_back(fdL);
	this->vertices.push_back(fuL);
	this->vertex_indices.push_back(this->vertices.size() - 3); 
	this->vertex_indices.push_back(this->vertices.size() - 2); 
	this->vertex_indices.push_back(this->vertices.size() - 1);

	if (!this->PostGLInitialize(&this->vertex_array_handle, &this->vertex_coordinate_handle, this->vertices.size() * sizeof(VertexAttributes), &this->vertices[0]))
		return false;

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexAttributes), (GLvoid *) 0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexAttributes), (GLvoid *) (sizeof(vec3)));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(VertexAttributes), (GLvoid *) (sizeof(vec3) * 2));
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(VertexAttributes), (GLvoid *) (sizeof(vec3) * 3));

	//	Each of the attributes to be used must be enabled.
	glEnableVertexAttribArray(0);glEnableVertexAttribArray(1);glEnableVertexAttribArray(2);glEnableVertexAttribArray(3);

	glBindBuffer(GL_ARRAY_BUFFER, 0);glBindVertexArray(0);

	if (this->GLReturnedError("Cube::Initialize - on exit"))
		return false;

	return true;
}

//Delete the cube object
void Cube3::TakeDown()
{
	this->vertices.clear();
	this->shader.TakeDown();
	this->solid_color.TakeDown();
	super::TakeDown();
}

//Draw the cube object
void Cube3::Draw(const mat4 & projection, mat4 modelview, const ivec2 & size, const float time)
{
	if (this->GLReturnedError("Cube3::Draw - on entry"))
		return;

	glEnable(GL_DEPTH_TEST);

	modelview = rotate(modelview, time * 30.0f, vec3(1.0f, 0.0f, 0.0f));
	modelview = rotate(modelview, time * 120.0f, vec3(0.0f, 1.0f, 0.0f));
	mat4 mvp = projection * modelview;
	mat3 nm = inverse(transpose(mat3(modelview)));

	this->shaders[this->shader_index]->Use();
	TextureManager::Inst()->BindTexture(texID, 0);
	this->shaders[this->shader_index]->CommonSetup(time, value_ptr(size), value_ptr(projection), value_ptr(modelview), value_ptr(mvp), value_ptr(nm));
	this->shaders[this->shader_index]->CustomSetup2(colorA);
	glBindVertexArray(this->vertex_array_handle);
	glDrawElements(GL_TRIANGLES , this->vertex_indices.size(), GL_UNSIGNED_INT , &this->vertex_indices[0]);
	glBindVertexArray(0);
	glUseProgram(0);

	if (this->GLReturnedError("Cube3::Draw - on exit"))
		return;
}
