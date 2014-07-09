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

class RoundObstacle
{
public:
	RoundObstacle();
	~RoundObstacle();

	vec3 pos;
	float height;
	float radius;	
};