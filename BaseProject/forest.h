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
#include <fstream>
#include <vector>
#include "gengar.h"
#include "rectangularObstacles.h"
#include "roundObstacles.h"

using namespace glm;
using namespace std;

class Forest : public Object
{
public:
	Forest();
	~Forest();
	virtual bool Initialize();
	virtual void Draw(const glm::mat4& projection, glm::mat4 modelview, const glm::ivec2 & size, const float time = 0);
	void TakeDown();
	void StepShader();
	void saveBuildingVertices();
	float dist(float x1, float y1, float z1, float x2, float y2, float z2);
	Shader shader;Shader solid_color;
	Square3 * roof;Square3 * wall;
	Gengar floor;
	Cylinder * base;

	bool initialized;

	Building tBuilding;
	vector<Building> buildings;
	vector<RectangularObstacle> rectangularObstacles;

	static const int NUM_TREES = 0;

	float tmpX, tmpZ, tmpR, tmpS;

	float transX, transY, transZ;
private:
	std::vector<VertexAttributesPCN> vertices;
	typedef Object super;
};