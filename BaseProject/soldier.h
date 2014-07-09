/*
Name: Clayton Suplinski
ID: 906 580 2630
CS 559 Project 3

Creates a shark object out of basic shapes.
*/

#pragma once
#include "object.h"
#include "shader.h"
#include "gengar.h"
#include "person.h"
#include "bullet.h"
#include <vector>

using namespace std;
using namespace glm;

class Soldier : public Object
{
public:
	Soldier();
	~Soldier();
	virtual bool Initialize();
	virtual void Draw(const glm::mat4& projection, glm::mat4 modelview, const glm::ivec2 & size, const float time = 0);
	void DrawTransparent(const glm::mat4& projection, glm::mat4 modelview, const glm::ivec2 & size, const float time = 0);
	void TakeDown();
	void StepShader();
	Shader shader;

	Gengar * soldier;
	Person person;

	bool shooting;

	static const int maxHP = 100;
	static const int maxAmmo = 300;
	static const int maxGrenades = 30;

	int health;
	bool user;
	bool dead; //Change to int if multiple lives
	bool userTeam;
	int ammo;
	int grenades;

	bool userDamageFlag;int userDamageCounter;
	bool userCanisterFlag;int userCanisterCounter;int userCanisterType;

	float lastShot, lastGrenade;

	int kills;string name;

	float distFromUser;

	vec3 pos;
	float hRot, vRot;
	
	int planOfAttack;

	float fallDownTime, fadeTime;

	struct distCalc{
		float dist;
		int frameCount;
		int whenToCheck;
	};

	vector<distCalc> buildings;

private:
	std::vector<VertexAttributesPCN> vertices;
	typedef Object super;
};