/*
Name: Clayton Suplinski
ID: 906 580 2630
CS 559 Project 3

Creates a disc object with a triangle fan
*/

#pragma once
#include "object.h"
#include "shader.h"

class Disc : public Object
{
public:
	Disc();
	virtual bool Initialize(int slices, float radius, char* v, char* f);
	virtual void Draw(const glm::mat4& projection, glm::mat4 modelview, const glm::ivec2 & size, const float time = 0);
	void TakeDown();
	Shader shader;
	Shader solid_color;
	glm::vec3 color;
	glm::vec4 colorA;

	int shader_index;
	Shader flat_shader;
	Shader gouraud_shader;
	Shader phong_shader;
	std::vector<Shader *> shaders;
	inline void StepShader() {this->shader_index = ++this->shader_index % this->shaders.size();};
private:
	glm::vec4 colors[2];
	std::vector<VertexAttributesPCN> vertices;
	typedef Object super;
};