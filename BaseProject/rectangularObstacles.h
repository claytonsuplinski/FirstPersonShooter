/*
Name: Clayton Suplinski
ID: 906 580 2630
CS 559 Project 3

Creates a shark object out of basic shapes.
*/

#pragma once

#include "glm\glm.hpp"

using namespace std;
using namespace glm;

class RectangularObstacle
{
public:
	RectangularObstacle();
	~RectangularObstacle();

	bool round;

	vec3 dimensions;//if round, radius will be in the x position of the dimensions vector
	vec3 pos;	
};