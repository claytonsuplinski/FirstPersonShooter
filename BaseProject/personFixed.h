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

class PersonFixed : public Object
{
public:
	PersonFixed();
	~PersonFixed();
	virtual bool Initialize(char* v, char* f);
	virtual void Draw(const glm::mat4& projection, glm::mat4 modelview, const glm::ivec2 & size, const float time = 0);
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
	
private:
	typedef Object super;
};