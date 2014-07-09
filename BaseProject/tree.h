/*
Name: Clayton Suplinski
ID: 906 580 2630
CS 559 Project 3

Creates a shark object out of basic shapes.
*/

#pragma once
#include "object.h"
#include "shader.h"
#include "cylinder2.h"
#include "sphere2.h"

using namespace glm;

class Tree : public Object
{
public:
	Tree();
	~Tree();
	virtual bool Initialize();
	virtual void Draw(const glm::mat4& projection, glm::mat4 modelview, const glm::ivec2 & size, const float time = 0);
	void TakeDown();
	void StepShader();
	Shader shader;

	Cylinder2 * treeTrunk;
	Sphere2 * treeLeaves;

	float radius;
	vec3 pos;
	float height;
	int randBranch;

	float distFromUser;

private:
	typedef Object super;
};