/*
Name: Clayton Suplinski
Project: First-Person Shooter
*/

#pragma once
#include "object.h"
#include "shader.h"
#include "gengar.h"
#include "personFixed.h"

using namespace std;
using namespace glm;

class Building : public Object
{
public:
	Building();
	~Building();
	virtual bool Initialize(vec3 color, vec3 dim, vec3 pos, int environment);
	virtual void Draw(const mat4& projection, mat4 modelview, const ivec2 & size, const float time = 0);
	void TakeDown();
	Shader shader;

	int environmentNumber;

	Gengar * building1;
	Gengar * building2;
	Gengar * building3;
	Gengar * building4;
	Gengar * building5;
	Gengar * arch;
	Gengar * statue;

	Gengar * pool;
	Gengar * river;
	Gengar * fern;
	Gengar * pineTree;
	Gengar * rockWall;
	Gengar * treeArch;

	Gengar * pyramid;

	Gengar * volcano;

	Gengar * cave;
	PersonFixed * statueSoldier;

	vec3 pos;
	float rotation;
	int scaler;

	vec3 dimensions;

	int buildingType;

	float distFromUser;

private:
	typedef Object super;
};