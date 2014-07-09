/*
Name: Clayton Suplinski
ID: 906 580 2630
CS 559 Project 3

Creates the square arena
*/

#include <iostream>
#include "desert.h"

using namespace std;
using namespace glm;

//Create the Desert object
Desert::Desert() : Object(){initialized = false;}

Desert::~Desert(){}

//Initialize all the elements of the Desert
bool Desert::Initialize()
{

	if(!initialized){
		if (this->GLReturnedError("Desert::Initialize - on entry"))
			return false;

		if (!super::Initialize())
			return false;

		this->wall = new Square3();

		//this->base->color = vec3(1,0,0);
		//this->base->Initialize(10, 50, 30, 30, "phong3.vert", "phong3.frag");

		tmpX=0;tmpZ=0;tmpR=0;tmpS=1;
	
		this->floor.Initialize(100, 1000.0f, "./textures/floorPatternDesert.jpg", "basic_texture_shader.vert", "basic_texture_shader.frag");
		//this->roof->Initialize(1, 1000.0f, "./textures/wall3.jpg", "basic_texture_shader.vert", "roof_shader.frag");

		this->wall->Initialize(5, 50.0f, "./textures/waterfallSand.png", "sphereShader.vert", "sphereShader.frag");

		RectangularObstacle tRect;

		this->tBuilding.Initialize(vec3(0,0,0), vec3(5,30,5), vec3(0,0,0), 2);

		//Statue
		tBuilding.buildingType = 200;
		tBuilding.rotation = -90;
		tBuilding.pos = vec3(0,0,0);
		buildings.push_back(tBuilding);

		//Pyramids
		tBuilding.buildingType = 201;
		tBuilding.dimensions = vec3(1,1,1);
		tBuilding.rotation = 0;
		tBuilding.pos = vec3(0,0,0);
		buildings.push_back(tBuilding);

		tBuilding.buildingType = 201;
		tBuilding.dimensions = vec3(0.5, 0.5, 0.5);
		tBuilding.rotation = 0;
		tBuilding.pos = vec3(250, 0, 250);
		buildings.push_back(tBuilding);

		tBuilding.dimensions = vec3(0.5, 0.5, 0.5);
		tBuilding.rotation = 0;
		tBuilding.pos = vec3(-250, 0, -250);
		buildings.push_back(tBuilding);

		tBuilding.dimensions = vec3(0.35, 0.35, 0.35);
		tBuilding.rotation = 0;
		tBuilding.pos = vec3(250, 0, -250);
		buildings.push_back(tBuilding);

		tBuilding.dimensions = vec3(0.35, 0.35, 0.35);
		tBuilding.rotation = 0;
		tBuilding.pos = vec3(-250, 0, 250);
		buildings.push_back(tBuilding);

		if (this->GLReturnedError("Desert::Initialize - on exit"))
			return false;

		initialized = true;
	}

	return true;
}

//Delete the Desert
void Desert::TakeDown()
{
	this->floor.TakeDown();
	tBuilding.TakeDown();
	tBuilding.~Building();
	this->wall->TakeDown();
	this->buildings.clear();
	buildings.~vector();
	this->floor.TakeDown();
	super::TakeDown();
}

float Desert::dist(float x1, float y1, float z1, float x2, float y2, float z2){
	float x=x2-x1;float y=y2-y1;float z=z2-z1;
	return sqrt(x*x + y*y + z*z);
}

//Draw and position the elements of the Desert
void Desert::Draw(const mat4 & projection, mat4 modelview, const ivec2 & size, const float time)
{
	if (this->GLReturnedError("Desert::Draw - on entry"))
		return;

	glEnable(GL_DEPTH_TEST);

	mat4 another, floorMatrix, wallMatrix, wallMatrixReset;

	int ct = glutGet(GLUT_ELAPSED_TIME)%1000;

	mat4 buildingMatrix;

	for(int i=0; i<buildings.size(); i++){
		buildingMatrix = modelview;
		buildingMatrix = translate(buildingMatrix, buildings.at(i).pos);
		if(dist(buildings.at(i).pos.x,0,buildings.at(i).pos.z, 
			-transX, 0, -transZ) < 300 || buildings.at(i).buildingType == 201){
		this->buildings.at(i).Draw(projection, buildingMatrix, size, 2.5);
		}
	}

	modelview = translate(modelview, vec3(499.f,0.f,500.f));
	

	//Elements of the arena.
	floorMatrix = modelview;
	this->floor.Draw(projection, modelview, size, time);

	int subWallSpacing = 50;
	int numSubWalls = 21;

	ivec2 tod = ivec2(size.y, ct);

	wallMatrix = modelview;
	wallMatrix = rotate(wallMatrix, 180.f, vec3(0,1,0));
	wallMatrixReset = wallMatrix;
	for(int i=0; i<numSubWalls; i++){
		wallMatrix = translate(wallMatrixReset, vec3(i*subWallSpacing, 50, 0));
		wallMatrix = rotate(wallMatrix, 90.f, vec3(1,0,0));
		wallMatrix = rotate(wallMatrix, 180.f, vec3(0,1,0));
		wallMatrix = rotate(wallMatrix, 180.f, vec3(0,0,1));
		wallMatrix = translate(wallMatrix, vec3(0,0,200));
		wallMatrix = scale(wallMatrix, vec3(1,1,5));
		this->wall->Draw(projection, wallMatrix, tod, 2.5*i/numSubWalls);
	}
	
	wallMatrix = translate(modelview, vec3(1, 0, -1000));
	wallMatrix = rotate(wallMatrix, 270.f, vec3(0,1,0));
	wallMatrixReset = wallMatrix;
	for(int i=0; i<numSubWalls; i++){
		wallMatrix = translate(wallMatrixReset, vec3(i*subWallSpacing, 50, 0));
		wallMatrix = rotate(wallMatrix, 90.f, vec3(1,0,0));
		wallMatrix = translate(wallMatrix, vec3(0,1000,0));
		wallMatrix = rotate(wallMatrix, 180.f, vec3(0,1,0));
		wallMatrix = translate(wallMatrix, vec3(0,0,200));
		wallMatrix = scale(wallMatrix, vec3(1,1,5));
		this->wall->Draw(projection, wallMatrix, tod, 2.5*(1-(float)((float)i/(float)numSubWalls))+2.5);
	}

	wallMatrix = translate(modelview, vec3(1, 0, -1000));
	wallMatrix = rotate(wallMatrix, 270.f, vec3(0,1,0));
	wallMatrixReset = wallMatrix;
	for(int i=0; i<numSubWalls; i++){
		wallMatrix = translate(wallMatrixReset, vec3(i*subWallSpacing, 50, 0));
		wallMatrix = rotate(wallMatrix, 90.f, vec3(1,0,0));
		wallMatrix = rotate(wallMatrix, 180.f, vec3(0,1,0));
		wallMatrix = rotate(wallMatrix, 180.f, vec3(0,0,1));
		wallMatrix = translate(wallMatrix, vec3(0,0,200));
		wallMatrix = scale(wallMatrix, vec3(1,1,5));
		this->wall->Draw(projection, wallMatrix, tod, (2.5*i/numSubWalls)+7.5);
	}

	wallMatrix = translate(modelview, vec3(0, 0, -1000));
	wallMatrix = rotate(wallMatrix, 180.f, vec3(0,1,0));
	wallMatrixReset = wallMatrix;
	for(int i=0; i<numSubWalls; i++){
		wallMatrix = translate(wallMatrixReset, vec3(i*subWallSpacing, 50, 0));
		wallMatrix = rotate(wallMatrix, 90.f, vec3(1,0,0));
		wallMatrix = rotate(wallMatrix, 180.f, vec3(0,1,0));
		wallMatrix = translate(wallMatrix, vec3(0,0,200));
		wallMatrix = scale(wallMatrix, vec3(1,1,5));
		this->wall->Draw(projection, wallMatrix, tod, 2.5*(1-(float)((float)i/(float)numSubWalls))+5);
	}

	/*glDepthMask(GL_FALSE);
	another = translate(modelview, vec3(-5, 0, -5));
	this->base->colorA = vec4(0.5,0,0,0.75);
	this->base->Draw(projection, another, size, 0);

	another = translate(modelview, vec3(-995, 0, -5));
	this->base->colorA = vec4(0.5,0.5,0,0.75);
	this->base->Draw(projection, another, size, 0);

	another = translate(modelview, vec3(-995, 0, -995));
	this->base->colorA = vec4(0,0.5,0,0.75);
	this->base->Draw(projection, another, size, 0);

	another = translate(modelview, vec3(-5, 0, -995));
	this->base->colorA = vec4(0,0,0.5,0.75);
	this->base->Draw(projection, another, size, 0);
	glDepthMask(GL_TRUE);*/

	if (this->GLReturnedError("Desert::Draw - on exit"))
		return;
}
