/*
Name: Clayton Suplinski
Project: First-Person Shooter
*/

#pragma once
#include "object.h"
#include "shader.h"
#include "cylinder.h"

using namespace std;
using namespace glm;

class Canister : public Object
{
public:
	Canister();
	~Canister();
	virtual bool Initialize(int type);
	virtual void Draw(const mat4& projection, mat4 modelview, const ivec2 & size, const float time = 0);
	void TakeDown();
	void StepShader();
	Shader shader;

	int type;

	Cylinder * canister;

	float canisterRadius, canisterHeight;

	//Get from team class
	vec3 pos;
	bool doneDrawing;

	int lifetime;

private:
	typedef Object super;
};