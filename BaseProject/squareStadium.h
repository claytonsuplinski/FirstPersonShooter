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
#include "square3.h"
#include "building.h"
#include "gengar.h"
#include <fstream>
#include <vector>
#include "rectangularObstacles.h"

using namespace glm;
using namespace std;

class SquareStadium : public Object
{
public:
	SquareStadium();
	~SquareStadium();
	virtual bool Initialize(int weatherIndex);
	virtual void Draw(const glm::mat4& projection, glm::mat4 modelview, const glm::ivec2 & size, const float time = 0);
	void TakeDown();
	void StepShader();
	void saveBuildingVertices();
	Shader shader;Shader solid_color;
	Square3 * roof;Square3 * wall;
	Gengar floor;
	Cylinder * base;

	bool initialized;

	vector<Building> buildings;
	vector<RectangularObstacle> rectangularObstacles;

	float tmpX, tmpZ, tmpR, tmpS;

	vector<vec4> roadStraightXZRS;

	Building tBuilding;
	Square3 roadStraight;

	float transX, transY, transZ;
private:
	std::vector<VertexAttributesPCN> vertices;
	typedef Object super;
};