/*
Name: Clayton Suplinski
Project: First-Person Shooter
*/

#pragma once

using namespace std;

#include "team.h"
#include "building.h"
#include "rectangularObstacles.h"

class AI
{
public:
	AI();
	~AI();
	virtual void MoveComputers(Team * yellow, Team * blue, Team * green, Team * red, vector<Building> * buildings, 
		vector<RectangularObstacle> * rectangularObstacles); 
	};