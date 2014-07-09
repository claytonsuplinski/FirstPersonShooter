/*
Name: Clayton Suplinski
Project: First-Person Shooter
*/

#include "cave.h"

Cave::Cave() : Object(){initialized = false;}

Cave::~Cave(){}

bool Cave::Initialize()
{
	if(!initialized){
	if (this->GLReturnedError("Cave::Initialize - on entry"))
		return false;

	if (!super::Initialize())
		return false;

	tmpX=0;tmpZ=0;tmpR=0;tmpS=1;

	RectangularObstacle tRect;

	this->tBuilding.Initialize(vec3(0,0,0), vec3(5,30,5), vec3(0,0,0), 4);

	//Statue
	tBuilding.buildingType = 400;
	tBuilding.rotation = -90;
	tBuilding.pos = vec3(0,0,0);
	buildings.push_back(tBuilding);

	//Cave
	tBuilding.buildingType = 401;
	tBuilding.rotation = 0;
	tBuilding.pos = vec3(0,0,0);
	buildings.push_back(tBuilding);

	if (this->GLReturnedError("Cave::Initialize - on exit"))
		return false;
		
		initialized = true;
	}

	return true;
}

void Cave::TakeDown()
{
	super::TakeDown();
}

float Cave::dist(float x1, float y1, float z1, float x2, float y2, float z2){
	float x=x2-x1;float y=y2-y1;float z=z2-z1;
	return sqrt(x*x + y*y + z*z);
}

void Cave::Draw(const mat4 & projection, mat4 modelview, const ivec2 & size, const float time)
{
	if (this->GLReturnedError("Cave::Draw - on entry"))
		return;

	glEnable(GL_DEPTH_TEST);

	mat4 buildingMatrix;

	for(unsigned int i=0; i<buildings.size(); i++){
		buildingMatrix = modelview;
		buildingMatrix = translate(buildingMatrix, buildings.at(i).pos);
		if(dist(buildings.at(i).pos.x,0,buildings.at(i).pos.z, 
			-transX, 0, -transZ) < 300 || buildings.at(i).buildingType == 401){
		this->buildings.at(i).Draw(projection, buildingMatrix, size, 2.5);
		}
	}

	if (this->GLReturnedError("Cave::Draw - on exit"))
		return;
}
