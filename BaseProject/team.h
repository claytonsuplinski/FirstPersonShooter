/*
Name: Clayton Suplinski
ID: 906 580 2630
CS 559 Project 3

Creates a shark object out of basic shapes.
*/

#pragma once
#include "object.h"
#include "shader.h"
#include "soldier.h"
#include "bullet.h"
#include "grenade.h"
#include "canister.h"
#include "building.h"
#include "tree.h"
#include "sphere.h"
#include <vector>
#include "roundObstacles.h"
#include "rectangularObstacles.h"

using namespace glm;

class Team : public Object
{
public:
	Team();
	~Team();
	virtual bool Initialize(int teamNo);
	virtual void Draw(const glm::mat4& projection, glm::mat4 modelview, const glm::ivec2 & size, const float time = 0);
	void reset();
	void TakeDown();
	void StepShader();
	void hpBounds();
	void firedBullet(int index);
	void threwGrenade(int index);
	void moveCpus();

	void ifHitByBullet(Team * otherTeam, Team * otherTeam2, Team * otherTeam3);
	void distFromUser(glm::vec3 userPos);

	bool ranIntoBuilding(glm::vec3 pos, double buffer);
	float distFromBuilding(glm::vec3 pos, RectangularObstacle building, double buffer);
	bool buildingInWay(vec3 user, vec3 targetSoldier, RectangularObstacle closestBuilding);
	bool buildingInFront(Soldier user, RectangularObstacle closestBuilding);

	bool ranIntoTree(vec3 pos, double buffer);
	float distFromTree(vec3 pos, Tree tree, double buffer);
	bool treeInWay(vec3 user, vec3 targetSoldier, Tree tree);
	bool treeInFront(Soldier user, Tree closestTree);

	float dist(float x1, float y1, float z1, float x2, float y2, float z2);

	bool linesIntersect(vec2 a1, vec2 a2, vec2 b1, vec2 b2);

	Shader shader;

	static const int NUM_SOLDIERS = 10;
	Soldier soldiers[NUM_SOLDIERS];
	vector<Bullet> activeBullets;
	vector<Grenade> activeGrenades;
	vector<Canister> activeCanisters;
	vector<RectangularObstacle> buildings;
	vector<Tree> trees;

	int teamNo;string teamColor;

	static const int bulletDamage = 35;
	static const int grenadeDamage = 3;
	static const int healthCanister = 25;
	static const int ammoCanister = 50;
	static const int grenadeCanister = 5;
	static const int numBuildings = 50;

	int numRemaining;

	Soldier tSoldier;
	Bullet tBullet;
	Grenade tGrenade;
	Canister tCanister;
	Tree tTree;

	bool userTeam;bool drawUser;
	bool drawBullet;

	float userX, userY, userZ;

private:
	std::vector<VertexAttributesPCN> vertices;
	typedef Object super;
};