/*
Name: Clayton Suplinski
Project: First-Person Shooter
*/

#pragma once
#include "object.h"
#include "building.h"
#include "rectangularObstacles.h"
#include <vector>

using namespace std;
using namespace glm;

class Cave : public Object
{
public:
	Cave();
	~Cave();
	virtual bool Initialize();
	virtual void Draw(const glm::mat4& projection, glm::mat4 modelview, const glm::ivec2 & size, const float time = 0);
	void TakeDown();
	float dist(float x1, float y1, float z1, float x2, float y2, float z2);

	bool initialized;

	Building tBuilding;
	vector<Building> buildings;
	vector<RectangularObstacle> rectangularObstacles;

	float tmpX, tmpZ, tmpR, tmpS;

	float transX, transY, transZ;
private:
	typedef Object super;
};