/*
Name: Clayton Suplinski
ID: 906 580 2630
CS 559 Project 2

Creates a cube object
*/

#pragma once
#include "object2.h"
#include "shader2.h"
#include "texturedshader.h"
#include "TextureManager.h"

class Cube3 : public Object2
{
public:
	Cube3();
	virtual bool Initialize(float l, float w, float h, char* filename, char* v, char* f);
	virtual void Draw(const glm::mat4& projection, glm::mat4 modelview, const glm::ivec2 & size, const float time);
	void TakeDown();
	Shader2 shader;
	Shader2 solid_color;
	unsigned int texID;

	glm::vec4 colorA;

	int shader_index;
private:
	typedef Object2 super;
	
	TexturedShader basic_texture_shader;
	std::vector<Shader2 *> shaders;
};