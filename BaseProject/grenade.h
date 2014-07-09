/*
Name: Clayton Suplinski
ID: 906 580 2630
CS 559 Project 3

Creates a shark object out of basic shapes.
*/

#pragma once
#include "object.h"
#include "shader.h"
#include "sphere.h"
#include "sphere2.h"

using namespace glm;

class Grenade : public Object
{
public:
	Grenade();
	~Grenade();
	virtual bool Initialize(vec3 color);
	virtual void Draw(const glm::mat4& projection, glm::mat4 modelview, const glm::ivec2 & size, const float time = 0);
	void TakeDown();
	void StepShader();
	Shader shader;
	float dist(float x1, float y1, float z1, float x2, float y2, float z2);

	Sphere * grenade;
	Sphere2 * explosion;

	const static int maxExplodeRadius = 30;

	float grenadeRadius;

	float velocityFactor;
	int distance;

	//Get from team class
	float fallingTime, explodeRadius;
	vec3 startPos;
	vec3 currPos;
	vec3 endPos;
	bool doneDrawing, explode;

	int userIndex;

private:
	std::vector<VertexAttributesPCN> vertices;
	typedef Object super;
};