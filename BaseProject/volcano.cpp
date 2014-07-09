/*
Name: Clayton Suplinski
ID: 906 580 2630
CS 559 Project 3

Creates the square arena
*/

#include <iostream>
#include "volcano.h"

using namespace std;
using namespace glm;

//Create the Volcano object
Volcano::Volcano() : Object(){initialized = false;}

Volcano::~Volcano(){}

//Initialize all the elements of the Volcano
bool Volcano::Initialize()
{

	if(!initialized){
	if (this->GLReturnedError("Volcano::Initialize - on entry"))
		return false;

	if (!super::Initialize())
		return false;

	this->wall = new Square3();

	tmpX=0;tmpZ=0;tmpR=0;tmpS=1;
	
	this->floor.Initialize(100, 1000.0f, "./textures/explosion.png", "basic_texture_shader.vert", "basic_texture_shader.frag");
	//this->roof->Initialize(1, 1000.0f, "./textures/wall3.jpg", "basic_texture_shader.vert", "roof_shader.frag");

	this->wall->Initialize(5, 50.0f, "./textures/waterfallSand.png", "sphereShader.vert", "sphereShader.frag");

	RectangularObstacle tRect;

	this->tBuilding.Initialize(vec3(0,0,0), vec3(5,30,5), vec3(0,0,0), 3);

	//Statue
	tBuilding.buildingType = 300;
	tBuilding.rotation = -90;
	tBuilding.pos = vec3(0,0,0);
	buildings.push_back(tBuilding);

	//Volcano
	tBuilding.buildingType = 301;
	tBuilding.rotation = 0;
	tBuilding.pos = vec3(0,-230,0);
	buildings.push_back(tBuilding);

	if (this->GLReturnedError("Volcano::Initialize - on exit"))
		return false;

		initialized = true;
	}

	return true;
}

//Delete the Volcano
void Volcano::TakeDown()
{
	this->floor.TakeDown();
	this->shader.TakeDown();
	this->solid_color.TakeDown();
	super::TakeDown();
}

float Volcano::dist(float x1, float y1, float z1, float x2, float y2, float z2){
	float x=x2-x1;float y=y2-y1;float z=z2-z1;
	return sqrt(x*x + y*y + z*z);
}

//Draw and position the elements of the Volcano
void Volcano::Draw(const mat4 & projection, mat4 modelview, const ivec2 & size, const float time)
{
	if (this->GLReturnedError("Volcano::Draw - on entry"))
		return;

	glEnable(GL_DEPTH_TEST);

	mat4 another, floorMatrix, wallMatrix, wallMatrixReset;

	int ct = glutGet(GLUT_ELAPSED_TIME)%1000;

	mat4 buildingMatrix;
	/*buildingMatrix = modelview;
	buildingMatrix = translate(buildingMatrix, vec3(tmpX, 0, tmpZ));
	buildingMatrix = rotate(buildingMatrix, tmpR, vec3(0,1,0));
	buildingMatrix = scale(buildingMatrix, vec3(tmpS, tmpS, tmpS));
	this->roadStraight.Draw(projection, buildingMatrix, size, 0);

	for(int i=0; i<roadStraightXZRS.size(); i++){
		buildingMatrix = modelview;
		buildingMatrix = translate(buildingMatrix, vec3(roadStraightXZRS.at(i).x, 0, roadStraightXZRS.at(i).y));
		buildingMatrix = rotate(buildingMatrix, roadStraightXZRS.at(i).z, vec3(0,1,0));
		buildingMatrix = scale(buildingMatrix, vec3(roadStraightXZRS.at(i).w, roadStraightXZRS.at(i).w, roadStraightXZRS.at(i).w));
		this->roadStraight.Draw(projection, buildingMatrix, size, 0);
	}*/

	mat4 treeMat;
	/*for(int i=0; i<NUM_TREES; i++){
		if(dist(treePositions.at(i).x,0,treePositions.at(i).z, 
			-transX, 0, -transZ) < 250){
			treeMat = translate(modelview, treePositions.at(i));
			treeMat = scale(treeMat, vec3(1,treeHeight.at(i), 1));
			this->treeTrunk->Draw(projection, treeMat, size, time);
			treeMat = translate(modelview, vec3(treePositions.at(i).x,treeHeight.at(i), treePositions.at(i).z));
			treeMat = scale(treeMat, vec3(treeHeight.at(i),treeHeight.at(i)/2, treeHeight.at(i)));
			this->treeLeaves->Draw(projection, treeMat, size, time);
			treeMat = translate(modelview, vec3(treePositions.at(i).x,treeHeight.at(i)/(i%2? 2 : 3), treePositions.at(i).z));
			treeMat = scale(treeMat, vec3(treeHeight.at(i)/2,treeHeight.at(i)/2, treeHeight.at(i)/2));
			this->treeLeaves->Draw(projection, treeMat, size, time);
		}
	}*/

	/*
	for(int i=0; i<NUM_TREES; i++){
		//Remember to change dist to trees->distFromUser
		if(dist(trees.at(i).pos.x,0,trees.at(i).pos.z, 
			-transX, 0, -transZ) < 250){
				this->trees.at(i).Draw(projection, modelview, size, time);
		}
	}
	*/

	for(int i=0; i<buildings.size(); i++){
		buildingMatrix = modelview;
		buildingMatrix = translate(buildingMatrix, buildings.at(i).pos);
		if(dist(buildings.at(i).pos.x,0,buildings.at(i).pos.z, 
			-transX, 0, -transZ) < 300 || buildings.at(i).buildingType == 301){
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

	if (this->GLReturnedError("Volcano::Draw - on exit"))
		return;
}
