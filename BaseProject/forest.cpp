/*
Name: Clayton Suplinski
ID: 906 580 2630
CS 559 Project 3

Creates the square arena
*/

#include <iostream>
#include "forest.h"

using namespace std;
using namespace glm;

//Create the Forest object
Forest::Forest() : Object(){initialized = false;}

Forest::~Forest(){}

//Initialize all the elements of the Forest
bool Forest::Initialize()
{

	if(!initialized){
	if (this->GLReturnedError("Forest::Initialize - on entry"))
		return false;

	if (!super::Initialize())
		return false;

	this->roof = new Square3();
	this->wall = new Square3();
	this->base = new Cylinder();

	this->base->color = vec3(1,0,0);
	this->base->Initialize(10, 50, 30, 30, "phong3.vert", "phong3.frag");

	tmpX=0;tmpZ=0;tmpR=0;tmpS=1;
	
	this->floor.order = 1;
	this->floor.Initialize("./models/forest.obj", "./models/forest.png", "basic_texture_shader.vert", "basic_texture_shader.frag");
	//this->roof->Initialize(1, 1000.0f, "./textures/wall3.jpg", "basic_texture_shader.vert", "roof_shader.frag");

	this->wall->Initialize(5, 50.0f, "./textures/waterfall.png", "sphereShader.vert", "sphereShader.frag");

	RectangularObstacle tRect;

	this->tBuilding.Initialize(vec3(0,0,0), vec3(5,30,5), vec3(0,0,0), 1);

	//Rivers
	tBuilding.buildingType = 100;
	tBuilding.rotation = 90;
	tBuilding.dimensions = vec3(0.9, 1, 0.8);
	tBuilding.pos = vec3(-290,0,315);
	buildings.push_back(tBuilding);
	tRect.dimensions = vec3(tBuilding.dimensions.z*44, 0, tBuilding.dimensions.x*204);
	tRect.pos = tBuilding.pos;		
	rectangularObstacles.push_back(tRect);

	tBuilding.rotation = -90;
	tBuilding.dimensions = vec3(1.6, 1, 0.85);
	tBuilding.pos = vec3(-370,0,-15);
	buildings.push_back(tBuilding);
	tRect.dimensions = vec3(tBuilding.dimensions.z*44, 0, tBuilding.dimensions.x*204);
	tRect.pos = tBuilding.pos;		
	rectangularObstacles.push_back(tRect);

	tBuilding.rotation = 90;
	tBuilding.dimensions = vec3(0.8, 1, 0.8);
	tBuilding.pos = vec3(-430,0,-355);
	buildings.push_back(tBuilding);
	tRect.dimensions = vec3(tBuilding.dimensions.z*44, 0, tBuilding.dimensions.x*204);
	tRect.pos = tBuilding.pos;		
	rectangularObstacles.push_back(tRect);

	tBuilding.rotation = -90;
	tBuilding.dimensions = vec3(1.9, 1, 0.875);
	tBuilding.pos = vec3(-210,0,-245);
	buildings.push_back(tBuilding);
	tRect.dimensions = vec3(tBuilding.dimensions.z*44, 0, tBuilding.dimensions.x*204);
	tRect.pos = tBuilding.pos;		
	rectangularObstacles.push_back(tRect);

	tBuilding.rotation = 90;
	tBuilding.dimensions = vec3(0.95, 1, 0.85);
	tBuilding.pos = vec3(-140,0,180);
	buildings.push_back(tBuilding);
	tRect.dimensions = vec3(tBuilding.dimensions.z*44, 0, tBuilding.dimensions.x*204);
	tRect.pos = tBuilding.pos;		
	rectangularObstacles.push_back(tRect);

	tBuilding.rotation = -90;
	tBuilding.dimensions = vec3(0.9, 1, 0.85);
	tBuilding.pos = vec3(40,0,225);
	buildings.push_back(tBuilding);
	tRect.dimensions = vec3(tBuilding.dimensions.z*44, 0, tBuilding.dimensions.x*204);
	tRect.pos = tBuilding.pos;		
	rectangularObstacles.push_back(tRect);

	tBuilding.rotation = 90;
	tBuilding.dimensions = vec3(0.95, 1, 0.85);
	tBuilding.pos = vec3(60,0,-240);
	buildings.push_back(tBuilding);
	tRect.dimensions = vec3(tBuilding.dimensions.z*44, 0, tBuilding.dimensions.x*204);
	tRect.pos = tBuilding.pos;		
	rectangularObstacles.push_back(tRect);

	tBuilding.rotation = -90;
	tBuilding.dimensions = vec3(0.84, 1, 0.85);
	tBuilding.pos = vec3(-30,0,-360);
	buildings.push_back(tBuilding);
	tRect.dimensions = vec3(tBuilding.dimensions.z*44, 0, tBuilding.dimensions.x*204);
	tRect.pos = tBuilding.pos;		
	rectangularObstacles.push_back(tRect);

	tBuilding.rotation = 90;
	tBuilding.dimensions = vec3(0.825, 1, 0.85);
	tBuilding.pos = vec3(180,0,350);
	buildings.push_back(tBuilding);
	tRect.dimensions = vec3(tBuilding.dimensions.z*44, 0, tBuilding.dimensions.x*204);
	tRect.pos = tBuilding.pos;		
	rectangularObstacles.push_back(tRect);

	tBuilding.rotation = -90;
	tBuilding.dimensions = vec3(1.02, 1, 0.85);
	tBuilding.pos = vec3(210,0,5);
	buildings.push_back(tBuilding);
	tRect.dimensions = vec3(tBuilding.dimensions.z*44, 0, tBuilding.dimensions.x*204);
	tRect.pos = tBuilding.pos;		
	rectangularObstacles.push_back(tRect);

	tBuilding.rotation = -90;
	tBuilding.dimensions = vec3(1.15, 1, 0.85);
	tBuilding.pos = vec3(300,0,260);
	buildings.push_back(tBuilding);
	tRect.dimensions = vec3(tBuilding.dimensions.z*44, 0, tBuilding.dimensions.x*204);
	tRect.pos = tBuilding.pos;		
	rectangularObstacles.push_back(tRect);

	tBuilding.rotation = 90;
	tBuilding.dimensions = vec3(1.25, 1, 0.85);
	tBuilding.pos = vec3(300,0,-322);
	buildings.push_back(tBuilding);
	tRect.dimensions = vec3(tBuilding.dimensions.z*44, 0, tBuilding.dimensions.x*204);
	tRect.pos = tBuilding.pos;		
	rectangularObstacles.push_back(tRect);

	tBuilding.rotation = -90;
	tBuilding.dimensions = vec3(1.12, 1, 0.85);
	tBuilding.pos = vec3(430,0,-35);
	buildings.push_back(tBuilding);
	tRect.dimensions = vec3(tBuilding.dimensions.z*44, 0, tBuilding.dimensions.x*204);
	tRect.pos = tBuilding.pos;		
	rectangularObstacles.push_back(tRect);

	//Rock Walls
	tBuilding.buildingType = 104;
	tBuilding.rotation = 90;
	tBuilding.pos = vec3(-500, 0, 0);
	buildings.push_back(tBuilding);
	tRect.dimensions = vec3(20, 0, 940);
	tRect.pos = tBuilding.pos;		
	rectangularObstacles.push_back(tRect);

	tBuilding.rotation = 180;
	tBuilding.pos = vec3(0, 0, 500);
	buildings.push_back(tBuilding);
	tRect.dimensions = vec3(940, 0, 20);
	tRect.pos = tBuilding.pos;		
	rectangularObstacles.push_back(tRect);

	tBuilding.rotation = 270;
	tBuilding.pos = vec3(500, 0, 0);
	buildings.push_back(tBuilding);
	tRect.dimensions = vec3(20, 0, 940);
	tRect.pos = tBuilding.pos;		
	rectangularObstacles.push_back(tRect);

	tBuilding.rotation = 0;
	tBuilding.pos = vec3(0, 0, -500);
	buildings.push_back(tBuilding);
	tRect.dimensions = vec3(940, 0, 20);
	tRect.pos = tBuilding.pos;		
	rectangularObstacles.push_back(tRect);

	//Statue
	tBuilding.buildingType = 101;
	tBuilding.rotation = -90;
	tBuilding.pos = vec3(0,0,0);
	buildings.push_back(tBuilding);

	tRect.dimensions = vec3(20, 10, 20);
	tRect.pos = vec3(0,0,0);		
	rectangularObstacles.push_back(tRect);

	//Tree Arch
	tBuilding.buildingType = 105;
	tBuilding.rotation = 0;
	tBuilding.pos = vec3(50,0,0);
	buildings.push_back(tBuilding);

	tBuilding.rotation = 90;
	tBuilding.pos = vec3(0,0,50);
	buildings.push_back(tBuilding);

	tBuilding.rotation = 180;
	tBuilding.pos = vec3(-50,0,0);
	buildings.push_back(tBuilding);

	tBuilding.rotation = 270;
	tBuilding.pos = vec3(0,0,-50);
	buildings.push_back(tBuilding);

	for(int i=0; i<1500; i++){ //trees
		tBuilding.buildingType = 103;
		tBuilding.rotation = 180*(float) rand() / (RAND_MAX)+180;
		tBuilding.pos = vec3(960*(float) rand() / (RAND_MAX)-480,0,960*(float) rand() / (RAND_MAX)-480);
		buildings.push_back(tBuilding);
	}

	for(int i=0; i<500; i++){ //ferns
		tBuilding.buildingType = 102;
		tBuilding.rotation = 180*(float) rand() / (RAND_MAX)+180;
		tBuilding.pos = vec3(980*(float) rand() / (RAND_MAX)-490,0,980*(float) rand() / (RAND_MAX)-490);
		buildings.push_back(tBuilding);
	}


	RoundObstacle initRound;

/*	tTree.Initialize();
	for(int i=0; i<NUM_TREES; i++){
		tTree.pos = vec3(1000*(float) rand() / (RAND_MAX)-500,0,1000*(float) rand() / (RAND_MAX)-500);		
		tTree.radius = 8*(float) rand() / (RAND_MAX)+1;
		tTree.height = 30*(float) rand() / (RAND_MAX)+50;
		trees.push_back(tTree);

		initRound.pos = tTree.pos;
		initRound.radius = tTree.radius;
		initRound.height = tTree.height;
		roundObstacles.push_back(initRound);
	}*/

	if (this->GLReturnedError("Forest::Initialize - on exit"))
		return false;

		initialized = true;
	}

	return true;
}

//Delete the Forest
void Forest::TakeDown()
{
	this->floor.TakeDown();
	this->vertices.clear();this->shader.TakeDown();
	this->solid_color.TakeDown();
	super::TakeDown();
}

float Forest::dist(float x1, float y1, float z1, float x2, float y2, float z2){
	float x=x2-x1;float y=y2-y1;float z=z2-z1;
	return sqrt(x*x + y*y + z*z);
}

//Draw and position the elements of the Forest
void Forest::Draw(const mat4 & projection, mat4 modelview, const ivec2 & size, const float time)
{
	if (this->GLReturnedError("Forest::Draw - on entry"))
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

	for(int i=0; i<buildings.size(); i++){
		buildingMatrix = modelview;
		buildingMatrix = translate(buildingMatrix, buildings.at(i).pos);
		if(dist(buildings.at(i).pos.x,0,buildings.at(i).pos.z, 
			-transX, 0, -transZ) < 300 || buildings.at(i).buildingType == 104){
		this->buildings.at(i).Draw(projection, buildingMatrix, size, 0);
		}
	}
	/*for(int i=0; i<NUM_TREES; i++){
		//Remember to change dist to trees->distFromUser
		if(dist(trees.at(i).pos.x,0,trees.at(i).pos.z, 
			-transX, 0, -transZ) < 250){
				this->trees.at(i).Draw(projection, modelview, size, time);
		}
	}*/

	//Elements of the arena.
	floorMatrix = modelview;
	this->floor.Draw(projection, modelview, size, time);

	modelview = translate(modelview, vec3(499.f,0.f,500.f));
	
	floorMatrix = translate(floorMatrix, vec3(0,250,0));
	//this->roof->Draw(projection, floorMatrix, size, time);

	int subWallSpacing = 50;
	int numSubWalls = 2;

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
	wallMatrix = modelview;
	wallMatrix = rotate(wallMatrix, 180.f, vec3(0,1,0));
	wallMatrixReset = wallMatrix;
	for(int i=19; i<21; i++){
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
	for(int i=19; i<21; i++){
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
	wallMatrix = translate(modelview, vec3(1, 0, -1000));
	wallMatrix = rotate(wallMatrix, 270.f, vec3(0,1,0));
	wallMatrixReset = wallMatrix;
	for(int i=19; i<21; i++){
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
	wallMatrix = translate(modelview, vec3(0, 0, -1000));
	wallMatrix = rotate(wallMatrix, 180.f, vec3(0,1,0));
	wallMatrixReset = wallMatrix;
	for(int i=19; i<21; i++){
		wallMatrix = translate(wallMatrixReset, vec3(i*subWallSpacing, 50, 0));
		wallMatrix = rotate(wallMatrix, 90.f, vec3(1,0,0));
		wallMatrix = rotate(wallMatrix, 180.f, vec3(0,1,0));
		wallMatrix = translate(wallMatrix, vec3(0,0,200));
		wallMatrix = scale(wallMatrix, vec3(1,1,5));
		this->wall->Draw(projection, wallMatrix, tod, 2.5*(1-(float)((float)i/(float)numSubWalls))+5);
	}


	if (this->GLReturnedError("Forest::Draw - on exit"))
		return;
}
