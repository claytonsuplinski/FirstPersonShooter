/*
Name: Clayton Suplinski
ID: 906 580 2630
CS 559 Project 3

Creates the UFO arena
*/

#pragma once
#include "object.h"
#include "shader.h"
#include "impostor.h"
#include "gengar.h"

class Person : public Object
{
public:
	Person();
	~Person();
	virtual bool Initialize();
	virtual void Draw(const glm::mat4& projection, glm::mat4 modelview, const glm::ivec2 & size, const float time = 0);
	void DrawTransparent(const glm::mat4& projection, glm::mat4 modelview, const glm::ivec2 & size, const float time = 0);
	void DrawAlive(const glm::mat4& projection, glm::mat4 modelview, const glm::ivec2 & size, const float time = 0);
	void DrawDead(const glm::mat4& projection, glm::mat4 modelview, const glm::ivec2 & size, const float time = 0);
	void TakeDown();
	void StepShader();
	Shader shader;
	Shader solid_color;

	Gengar * head;
	Gengar * torso;
	Gengar * upperArm;
	Gengar * lowerArm;
	Gengar * upperLeg;
	Gengar * lowerLeg;
	Gengar * gun;
	Gengar * shoe;

	Impostor * deathEffect;

	bool transparentPass;

	float tmpZoom;
	float tmpX, tmpY, tmpZ;

	float editX, editY;

	float velocity;
	float MAX_VELOCITY;

	static const int MAX_FALLDOWNTIME = 45;
	float fallDownTime, fadeTime;bool dead;

	bool user;
	
private:
	std::vector<VertexAttributesPCN> vertices;
	typedef Object super;
};