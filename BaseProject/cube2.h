/*
Name: Clayton Suplinski
ID: 906 580 2630
CS 559 Project 3

Creates a textured cube with 6 different images
*/

#pragma once
#include "object.h"
#include "shader.h"
#include "square2.h"

class Cube2 : public Object
{
public:
	Cube2();
	~Cube2();
	virtual bool Initialize(int skyboxID, int baseTexID, char* v, char* f);
	virtual void Draw(const glm::mat4& projection, glm::mat4 modelview, const glm::ivec2 & size, const float time = 0);
	void TakeDown();
	void StepShader();
	Shader shader;
	Shader solid_color;
	Square2 * left;Square2 * right;Square2 * up;Square2 * down;Square2 * front;Square2 * back;

private:
	void BuildNormalVisualizationGeometry();
	glm::vec4 colors[2];
	std::vector<VertexAttributesPCN> vertices;
	typedef Object super;
};