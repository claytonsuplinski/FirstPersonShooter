/*
Name: Clayton Suplinski
ID: 906 580 2630
CS 559 Project 3

Creates the square arena
*/

#pragma once
#include "object.h"
#include "shader.h"
#include "cylinder.h"
#include "building.h"
#include "sphere.h"
#include "disc.h"
#include "team.h"
#include "cube2.h"
#include "precip.h"
#include "ai.h"

//ADD_STADIUM//
#include "squareStadium.h"
#include "forest.h"
#include "desert.h"
#include "volcano.h"
#include "cave.h"

using namespace std;
using namespace glm;

class GameMode1 : public Object
{
public:
	GameMode1();
	~GameMode1();
	mat4 render(mat4 Model);
	mat4 endRender(mat4 Model);
	virtual bool Initialize();
	virtual void Draw(const glm::mat4& projection, glm::mat4 modelview, const glm::ivec2 & size, const float time = 0);
	void DrawStadium(const glm::mat4& projection, glm::mat4 modelview, const glm::ivec2 & size, const float time = 0);
	void DrawTeams(const glm::mat4& projection, glm::mat4 modelview, const glm::ivec2 & size, const float time = 0);
	void DrawUser(const glm::mat4& projection, glm::mat4 modelview, const glm::ivec2 & size, const float time = 0);
	void DrawOrthographic(const glm::mat4& projection, glm::mat4 modelview, const glm::ivec2 & size, bool firstPerson, const float time = 0);
	void DrawPrecipitation(const glm::mat4& projection, glm::mat4 modelview, const glm::ivec2 & size, const float time = 0);
	void TakeDown();
	bool checkGameOver(int &winningTeam, string &winningTeamName, vec4 &winningTeamFontColor);
	void AfterDeath(vector<Soldier *> &remainingSoldiers, float &transX2, float &transY2, float &transZ2);

	bool followCpuSoldier;
	int soldierToFollowIndex;

//x (0=Normal, 1=night, 2=twilight), y(0=normal, 1=underwater, 2=fog)
ivec2 tod;

//Time control variables.
float current_timeDisplay;

//Stuff for orthographic display
Sphere usr;Disc disc;Cylinder healthBar; //Radar
Square3 numberBackground, userDamaged, userHealed, userAmmoed, userGrenaded, 
	reticule, healthIcon, killsIcon, ammoIcon, grenadeIcon, backgroundSquare;  //Special effects
Precip precip;float movingWRTSnow;int weatherType;

//Stuff for the game mode's display
//ADD_STADIUM//
int stadiumSelect;
SquareStadium * stadium;
Forest * forest;
Desert * desert;
Volcano * volcano;
Cave * cave;

Cube2 skybox;Team userTeam, redTeam, blueTeam, greenTeam;
Soldier tSoldier;
AI ai;

	float transX, transY, transZ;
	double RotatedY, RotatedX;
private:
	typedef Object super;
};