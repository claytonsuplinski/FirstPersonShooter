/*
Name: Clayton Suplinski
ID: 906 580 2630
CS 559 Project 3

Creates the square arena
*/

#include <iostream>
#include "squareStadium.h"

using namespace std;
using namespace glm;

//Create the SquareStadium object
SquareStadium::SquareStadium() : Object(){initialized = false;}

SquareStadium::~SquareStadium(){}

//Initialize all the elements of the SquareStadium
bool SquareStadium::Initialize(int weatherIndex)
{

	if(!initialized){
	if (this->GLReturnedError("SquareStadium::Initialize - on entry"))
		return false;

	if (!super::Initialize())
		return false;

	this->roof = new Square3();
	this->wall = new Square3();
	this->base = new Cylinder();

	RectangularObstacle tRect;

	this->tBuilding.Initialize(vec3(0,0,0), vec3(5,30,5), vec3(0,0,0), 0);

	//Statue
	tBuilding.buildingType = -1;
	tBuilding.rotation = -90;
	tBuilding.pos = vec3(0,0,0);
	buildings.push_back(tBuilding);

	//Pools
	tBuilding.buildingType = -2;
	tBuilding.rotation = -90;
	tBuilding.pos = vec3(0,0,220);
	buildings.push_back(tBuilding);
	tBuilding.pos = vec3(0,0,-230);
	buildings.push_back(tBuilding);

	//Arches
	tBuilding.buildingType = 0;
	
	tBuilding.rotation = -90;
	tBuilding.pos = vec3(65, 0, 15);
	buildings.push_back(tBuilding);

	
	tBuilding.pos = vec3(-65, 0, 15);
	buildings.push_back(tBuilding);

	
	tBuilding.rotation = 0;
	tBuilding.pos = vec3(15, 0, 65);
	buildings.push_back(tBuilding);

	
	tBuilding.pos = vec3(15, 0, -65);
	buildings.push_back(tBuilding);
	//End arches

	//Wall buildings

	//Green corner
	tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);
	tBuilding.scaler = 1;
	tBuilding.rotation = 0;
	
	tBuilding.pos = vec3(-465, 0, -495);
	buildings.push_back(tBuilding);

	tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);
	tBuilding.scaler = 2;
	tBuilding.rotation = 0;
	
	tBuilding.pos = vec3(-450, 0, -490);
	buildings.push_back(tBuilding);

	for(int i=-420; i<460; i+=40){ //Green-blue Wall
		tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);
		tBuilding.scaler = 4;
		tBuilding.rotation = 0;
		
		tBuilding.pos = vec3(i, 0, -480);
		buildings.push_back(tBuilding);
	}

	tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);
	tBuilding.scaler = 2;
	tBuilding.rotation = 0;
	
	tBuilding.pos = vec3(450, 0, -490);
	buildings.push_back(tBuilding);

	tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);
	tBuilding.scaler = 1;
	tBuilding.rotation = 0;
	
	tBuilding.pos = vec3(465, 0, -495);
	buildings.push_back(tBuilding);

	tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);
	tBuilding.scaler = 1;
	tBuilding.rotation = 90;
	
	tBuilding.pos = vec3(-495, 0, -465);
	buildings.push_back(tBuilding);

	tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);
	tBuilding.scaler = 2;
	tBuilding.rotation = 90;
	
	tBuilding.pos = vec3(-490, 0, -450);
	buildings.push_back(tBuilding);

	tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);
	tBuilding.scaler = 3;
	tBuilding.rotation = 90;
	
	tBuilding.pos = vec3(-485, 0, -425);
	buildings.push_back(tBuilding);

	tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);
	tBuilding.scaler = 1;
	tBuilding.rotation = 90;
	
	tBuilding.pos = vec3(-465, 0, -405);
	buildings.push_back(tBuilding);

	//Yellow Corner
	tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);
	tBuilding.scaler = 3;
	tBuilding.rotation = 180;
	
	tBuilding.pos = vec3(-425, 0, 485);
	buildings.push_back(tBuilding);

	tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);
	tBuilding.scaler = 2;
	tBuilding.rotation = 180;
	
	tBuilding.pos = vec3(-450, 0, 490);
	buildings.push_back(tBuilding);

	tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);
	tBuilding.scaler = 1;
	tBuilding.rotation = 90;
	
	tBuilding.pos = vec3(-495, 0, 465);
	buildings.push_back(tBuilding);

	tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);
	tBuilding.scaler = 2;
	tBuilding.rotation = 90;
	
	tBuilding.pos = vec3(-490, 0, 450);
	buildings.push_back(tBuilding);

	for(int i=420; i>-400; i-=40){ //Yellow-green Wall
		tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);
		tBuilding.scaler = 4;
		tBuilding.rotation = 90;
		
		tBuilding.pos = vec3(-480, 0, i);
		buildings.push_back(tBuilding);
	}

	tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);
	tBuilding.scaler = 1;
	tBuilding.rotation = 180;
	
	tBuilding.pos = vec3(-465, 0, 495);
	buildings.push_back(tBuilding);

	//Blue corner

	tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);
	tBuilding.scaler = 1;
	tBuilding.rotation = -90;
	
	tBuilding.pos = vec3(495, 0, -465);
	buildings.push_back(tBuilding);

	tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);
	tBuilding.scaler = 2;
	tBuilding.rotation = -90;
	
	tBuilding.pos = vec3(490, 0, -450);
	buildings.push_back(tBuilding);

	tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);
	tBuilding.scaler = 3;
	tBuilding.rotation = -90;
	
	tBuilding.pos = vec3(485, 0, -425);
	buildings.push_back(tBuilding);

	tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);
	tBuilding.scaler = 2;
	tBuilding.rotation = -90;
	
	tBuilding.pos = vec3(470, 0, 400);
	buildings.push_back(tBuilding);

	for(int i=-390; i<390; i+=40){ //Yellow-green Wall
		tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);
		tBuilding.scaler = 4;
		tBuilding.rotation = -90;
		
		tBuilding.pos = vec3(480, 0, i);
		buildings.push_back(tBuilding);
	}

	//Red corner

	tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);
	tBuilding.scaler = 1;
	tBuilding.rotation = -90;
	
	tBuilding.pos = vec3(495, 0, 465);
	buildings.push_back(tBuilding);

	tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);
	tBuilding.scaler = 2;
	tBuilding.rotation = -90;
	
	tBuilding.pos = vec3(490, 0, 450);
	buildings.push_back(tBuilding);

	tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);
	tBuilding.scaler = 3;
	tBuilding.rotation = -90;
	
	tBuilding.pos = vec3(485, 0, 425);
	buildings.push_back(tBuilding);

	tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);
	tBuilding.scaler = 1;
	tBuilding.rotation = 180;
	
	tBuilding.pos = vec3(465, 0, 495);
	buildings.push_back(tBuilding);

	tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);
	tBuilding.scaler = 2;
	tBuilding.rotation = 180;
	
	tBuilding.pos = vec3(450, 0, 490);
	buildings.push_back(tBuilding);

	for(int i=420; i>-400; i-=40){ //Yellow-green Wall
		tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);
		tBuilding.scaler = 4;
		tBuilding.rotation = 180;
		
		tBuilding.pos = vec3(i, 0, 480);
		buildings.push_back(tBuilding);
	}

	tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);
	tBuilding.scaler = 1;
	tBuilding.rotation = 180;
	
	tBuilding.pos = vec3(-405, 0, 465);
	buildings.push_back(tBuilding);
	//End wall buildings

	//Buildings facing up/down

	int skipCounter = 1;
	for(int i=400; i>-410; i-=40){ //Yellow-green Wall

		//Col 1//
		if(skipCounter != 5 && skipCounter != 6 && skipCounter != 11 && skipCounter != 12 && skipCounter != 16 && skipCounter != 17){
			tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);
			tBuilding.scaler = 4;
			tBuilding.rotation = 270;
			
			tBuilding.pos = vec3(-390, 0, i);
			buildings.push_back(tBuilding);

			tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);
			tBuilding.rotation = 90;
			tBuilding.pos = vec3(-310, 0, i);
			buildings.push_back(tBuilding);
			
			if(skipCounter == 10 || skipCounter == 15 || skipCounter == 21){
				tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);
				tBuilding.rotation = 180;
				tBuilding.pos = vec3(-350, 0, i);
				buildings.push_back(tBuilding);
			}

			if(skipCounter == 1){
				tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);
				tBuilding.rotation = 0;
				tBuilding.pos = vec3(-350, 0, i);
				buildings.push_back(tBuilding);
			}
		}
		else if(skipCounter == 5){
			tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);
			tBuilding.rotation = 180;
			tBuilding.pos = vec3(-350, 0, i+20);
			buildings.push_back(tBuilding);

			tBuilding.scaler = 2;
			tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);
			tBuilding.rotation = 180;
			tBuilding.pos = vec3(-320, 0, i+10);
			buildings.push_back(tBuilding);

			tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);
			tBuilding.pos = vec3(-300, 0, i+10);
			buildings.push_back(tBuilding);

			tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);
			tBuilding.pos = vec3(-380, 0, i+10);
			buildings.push_back(tBuilding);

			tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);
			tBuilding.pos = vec3(-400, 0, i+10);
			buildings.push_back(tBuilding);
			tBuilding.scaler = 4;
		}
		else if(skipCounter == 6){
			tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);
			tBuilding.rotation = 0;
			tBuilding.pos = vec3(-350, 0, i-20);
			buildings.push_back(tBuilding);

			tBuilding.scaler = 2;
			tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);
			tBuilding.rotation = 0;
			tBuilding.pos = vec3(-320, 0, i-10);
			buildings.push_back(tBuilding);

			tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);
			tBuilding.pos = vec3(-300, 0, i-10);
			buildings.push_back(tBuilding);

			tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);
			tBuilding.pos = vec3(-380, 0, i-10);
			buildings.push_back(tBuilding);

			tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);
			tBuilding.pos = vec3(-400, 0, i-10);
			buildings.push_back(tBuilding);
			tBuilding.scaler = 4;
		}
		else if(skipCounter == 12 || skipCounter == 17){
			tBuilding.scaler = 3;
			tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);
			tBuilding.rotation = 0;
			tBuilding.pos = vec3(-395, 0, i-5);
			buildings.push_back(tBuilding);

			tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);
			tBuilding.pos = vec3(-365, 0, i-5);
			buildings.push_back(tBuilding);

			tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);
			tBuilding.pos = vec3(-335, 0, i-5);
			buildings.push_back(tBuilding);

			tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);
			tBuilding.pos = vec3(-305, 0, i-5);
			buildings.push_back(tBuilding);
			tBuilding.scaler = 4;
		}
		//End Col 1//

		//Col 2//
		if(skipCounter != 5 && skipCounter != 6 && skipCounter != 11 && skipCounter != 12){
			tBuilding.rotation = 270;
			tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);
			tBuilding.pos = vec3(-230, 0, i);
			buildings.push_back(tBuilding);

			tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);
			tBuilding.rotation = 90;
			tBuilding.pos = vec3(-180, 0, i);
			buildings.push_back(tBuilding);

			if(skipCounter == 1){
				tBuilding.scaler = 1;
				tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);
				tBuilding.rotation = 0;
				tBuilding.pos = vec3(-205, 0, i+15);
				buildings.push_back(tBuilding);
				tBuilding.scaler = 4;
			}
			if(skipCounter == 10 || skipCounter == 21){
				tBuilding.scaler = 1;
				tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);
				tBuilding.rotation = 180;
				tBuilding.pos = vec3(-205, 0, i-15);
				buildings.push_back(tBuilding);
				tBuilding.scaler = 4;
			}
		}
		else if(skipCounter == 5){
			tBuilding.scaler = 2;
			tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);
			tBuilding.rotation = 180;
			tBuilding.pos = vec3(-240, 0, i+10);
			buildings.push_back(tBuilding);

			tBuilding.scaler = 3;
			tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);
			tBuilding.pos = vec3(-215, 0, i+15);
			buildings.push_back(tBuilding);

			tBuilding.scaler = 2;
			tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);
			tBuilding.pos = vec3(-190, 0, i+10);
			buildings.push_back(tBuilding);

			tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);
			tBuilding.pos = vec3(-170, 0, i+10);
			buildings.push_back(tBuilding);
			tBuilding.scaler = 4;
		}
		else if(skipCounter == 6){
			tBuilding.scaler = 2;
			tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);
			tBuilding.rotation = 0;
			tBuilding.pos = vec3(-240, 0, i-10);
			buildings.push_back(tBuilding);

			tBuilding.scaler = 3;
			tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);
			tBuilding.pos = vec3(-215, 0, i-15);
			buildings.push_back(tBuilding);

			tBuilding.scaler = 2;
			tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);
			tBuilding.pos = vec3(-190, 0, i-10);
			buildings.push_back(tBuilding);

			tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);
			tBuilding.pos = vec3(-170, 0, i-10);
			buildings.push_back(tBuilding);
			tBuilding.scaler = 4;
		}
		else if(skipCounter == 12){
			tBuilding.scaler = 3;
			tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);
			tBuilding.rotation = 0;
			tBuilding.pos = vec3(-235, 0, i-5);
			buildings.push_back(tBuilding);

			tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);
			tBuilding.pos = vec3(-205, 0, i-5);
			buildings.push_back(tBuilding);

			tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);
			tBuilding.pos = vec3(-175, 0, i-5);
			buildings.push_back(tBuilding);

			tBuilding.scaler = 4;
		}
		//End Col 2//

		//Col 3//
		if(skipCounter != 5 && skipCounter != 6 && skipCounter != 10 && skipCounter != 11 && skipCounter != 12 && 
			skipCounter != 16 && skipCounter != 17){
			tBuilding.rotation = 270;
			tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);
			tBuilding.pos = vec3(-90, 0, i);
			buildings.push_back(tBuilding);

			tBuilding.scaler = 2;
			tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);
			tBuilding.rotation = 90;
			tBuilding.pos = vec3(-60, 0, i-10);
			buildings.push_back(tBuilding);

			tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);
			tBuilding.rotation = 90;
			tBuilding.pos = vec3(-60, 0, i+10);
			buildings.push_back(tBuilding);
			tBuilding.scaler = 4;
		}
		else if(skipCounter == 5){
			tBuilding.scaler = 2;
			tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);
			tBuilding.rotation = 180;
			tBuilding.pos = vec3(-100, 0, i+10);
			buildings.push_back(tBuilding);

			tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);
			tBuilding.pos = vec3(-80, 0, i+10);
			buildings.push_back(tBuilding);

			tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);
			tBuilding.pos = vec3(-60, 0, i+10);
			buildings.push_back(tBuilding);
			tBuilding.scaler = 4;
		}
		else if(skipCounter == 6){
			tBuilding.scaler = 2;
			tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);
			tBuilding.rotation = 0;
			tBuilding.pos = vec3(-100, 0, i-10);
			buildings.push_back(tBuilding);

			tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);
			tBuilding.pos = vec3(-80, 0, i-10);
			buildings.push_back(tBuilding);

			tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);
			tBuilding.pos = vec3(-60, 0, i-10);
			buildings.push_back(tBuilding);
			tBuilding.scaler = 4;
		}
		else if(skipCounter == 10){
			tBuilding.scaler = 1;
			tBuilding.rotation = 180;
			tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);			
			tBuilding.pos = vec3(-95, 0, i+15);
			buildings.push_back(tBuilding);

			tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);
			tBuilding.pos = vec3(-85, 0, i+15);
			buildings.push_back(tBuilding);

			tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);
			tBuilding.pos = vec3(-65, 0, i+15);
			buildings.push_back(tBuilding);

			tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);			
			tBuilding.pos = vec3(-105, 0, i+15);
			buildings.push_back(tBuilding);

			tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);
			tBuilding.pos = vec3(-75, 0, i+15);
			buildings.push_back(tBuilding);

			tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);
			tBuilding.pos = vec3(-55, 0, i+15);
			buildings.push_back(tBuilding);
			tBuilding.scaler = 4;
		}
		else if(skipCounter == 12 || skipCounter == 17){
			tBuilding.scaler = 1;
			tBuilding.rotation = 0;
			tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);			
			tBuilding.pos = vec3(-95, 0, i-15);
			buildings.push_back(tBuilding);

			tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);
			tBuilding.pos = vec3(-85, 0, i-15);
			buildings.push_back(tBuilding);

			tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);
			tBuilding.pos = vec3(-65, 0, i-15);
			buildings.push_back(tBuilding);

			tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);			
			tBuilding.pos = vec3(-105, 0, i-15);
			buildings.push_back(tBuilding);

			tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);
			tBuilding.pos = vec3(-75, 0, i-15);
			buildings.push_back(tBuilding);

			tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);
			tBuilding.pos = vec3(-55, 0, i-15);
			buildings.push_back(tBuilding);
			tBuilding.scaler = 4;
		}
		else if(skipCounter == 16){
			tBuilding.scaler = 3;
			tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);
			tBuilding.rotation = 180;
			tBuilding.pos = vec3(-95, 0, i+5);
			buildings.push_back(tBuilding);

			tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);
			tBuilding.pos = vec3(-65, 0, i+5);
			buildings.push_back(tBuilding);
			tBuilding.scaler = 4;
		}
		//End Col 3//

		//Col 4//
		if(skipCounter != 5 && skipCounter != 6 && skipCounter != 10 && skipCounter != 11 && skipCounter != 12 && 
			skipCounter != 16 && skipCounter != 17){
			tBuilding.rotation = 270;
			tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);
			tBuilding.pos = vec3(70, 0, i);
			buildings.push_back(tBuilding);

			tBuilding.scaler = 2;
			tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);
			tBuilding.rotation = 90;
			tBuilding.pos = vec3(110, 0, i-10);
			buildings.push_back(tBuilding);

			tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);
			tBuilding.rotation = 90;
			tBuilding.pos = vec3(110, 0, i+10);
			buildings.push_back(tBuilding);
			tBuilding.scaler = 4;

			if(skipCounter == 1){
				tBuilding.scaler = 1;
				tBuilding.rotation = 0;
				tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);			
				tBuilding.pos = vec3(95, 0, i+15);
				buildings.push_back(tBuilding);
				tBuilding.scaler = 4;
			}
			if(skipCounter == 21){
				tBuilding.scaler = 1;
				tBuilding.rotation = 180;
				tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);			
				tBuilding.pos = vec3(95, 0, i-15);
				buildings.push_back(tBuilding);
				tBuilding.scaler = 4;
			}
		}
		else if(skipCounter == 5){
			tBuilding.scaler = 2;
			tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);
			tBuilding.rotation = 180;
			tBuilding.pos = vec3(60, 0, i+10);
			buildings.push_back(tBuilding);

			tBuilding.scaler = 3;
			tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);
			tBuilding.pos = vec3(85, 0, i+15);
			buildings.push_back(tBuilding);

			tBuilding.scaler = 2;
			tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);
			tBuilding.pos = vec3(110, 0, i+10);
			buildings.push_back(tBuilding);
			tBuilding.scaler = 4;
		}
		else if(skipCounter == 6){
			tBuilding.scaler = 2;
			tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);
			tBuilding.rotation = 0;
			tBuilding.pos = vec3(60, 0, i-10);
			buildings.push_back(tBuilding);

			tBuilding.scaler = 3;
			tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);
			tBuilding.pos = vec3(85, 0, i-15);
			buildings.push_back(tBuilding);

			tBuilding.scaler = 2;
			tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);
			tBuilding.pos = vec3(110, 0, i-10);
			buildings.push_back(tBuilding);
			tBuilding.scaler = 4;
		}
		else if(skipCounter == 10){
			tBuilding.scaler = 1;
			tBuilding.rotation = 180;
			tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);			
			tBuilding.pos = vec3(95, 0, i+15);
			buildings.push_back(tBuilding);

			tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);
			tBuilding.pos = vec3(85, 0, i+15);
			buildings.push_back(tBuilding);

			tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);
			tBuilding.pos = vec3(65, 0, i+15);
			buildings.push_back(tBuilding);

			tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);			
			tBuilding.pos = vec3(105, 0, i+15);
			buildings.push_back(tBuilding);

			tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);			
			tBuilding.pos = vec3(115, 0, i+15);
			buildings.push_back(tBuilding);

			tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);
			tBuilding.pos = vec3(75, 0, i+15);
			buildings.push_back(tBuilding);

			tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);
			tBuilding.pos = vec3(55, 0, i+15);
			buildings.push_back(tBuilding);
			tBuilding.scaler = 4;
		}
		else if(skipCounter == 12 || skipCounter == 17){
			tBuilding.scaler = 1;
			tBuilding.rotation = 0;
			tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);			
			tBuilding.pos = vec3(95, 0, i-15);
			buildings.push_back(tBuilding);

			tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);
			tBuilding.pos = vec3(85, 0, i-15);
			buildings.push_back(tBuilding);

			tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);
			tBuilding.pos = vec3(65, 0, i-15);
			buildings.push_back(tBuilding);

			tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);			
			tBuilding.pos = vec3(105, 0, i-15);
			buildings.push_back(tBuilding);

			tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);			
			tBuilding.pos = vec3(115, 0, i-15);
			buildings.push_back(tBuilding);

			tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);
			tBuilding.pos = vec3(75, 0, i-15);
			buildings.push_back(tBuilding);

			tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);
			tBuilding.pos = vec3(55, 0, i-15);
			buildings.push_back(tBuilding);
			tBuilding.scaler = 4;
		}
		else if(skipCounter == 16){
			tBuilding.scaler = 3;
			tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);
			tBuilding.rotation = 180;
			tBuilding.pos = vec3(65, 0, i+5);
			buildings.push_back(tBuilding);

			tBuilding.scaler = 1;
			tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);
			tBuilding.pos = vec3(85, 0, i-5);
			buildings.push_back(tBuilding);

			tBuilding.scaler = 3;
			tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);
			tBuilding.pos = vec3(105, 0, i+5);
			buildings.push_back(tBuilding);
			tBuilding.scaler = 4;
		}
		//End Col 4//

		//Col 5//
		if(skipCounter != 10 && skipCounter != 11 && skipCounter != 16 && skipCounter != 17){
			tBuilding.rotation = 270;
			tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);
			tBuilding.pos = vec3(190, 0, i);
			buildings.push_back(tBuilding);

			tBuilding.scaler = 2;
			tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);
			tBuilding.rotation = 90;
			tBuilding.pos = vec3(230, 0, i-10);
			buildings.push_back(tBuilding);

			tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);
			tBuilding.rotation = 90;
			tBuilding.pos = vec3(230, 0, i+10);
			buildings.push_back(tBuilding);
			tBuilding.scaler = 4;

			if(skipCounter == 1 || skipCounter == 12){
				tBuilding.scaler = 1;
				tBuilding.rotation = 0;
				tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);			
				tBuilding.pos = vec3(215, 0, i+15);
				buildings.push_back(tBuilding);
				tBuilding.scaler = 4;
			}
			if(skipCounter == 21){
				tBuilding.scaler = 1;
				tBuilding.rotation = 180;
				tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);			
				tBuilding.pos = vec3(215, 0, i-15);
				buildings.push_back(tBuilding);
				tBuilding.scaler = 4;
			}
		}
		else if(skipCounter == 17){
			tBuilding.scaler = 1;
			tBuilding.rotation = 0;
			tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);			
			tBuilding.pos = vec3(235, 0, i-15);
			buildings.push_back(tBuilding);

			tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);
			tBuilding.pos = vec3(225, 0, i-15);
			buildings.push_back(tBuilding);

			tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);
			tBuilding.pos = vec3(215, 0, i-15);
			buildings.push_back(tBuilding);

			tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);			
			tBuilding.pos = vec3(205, 0, i-15);
			buildings.push_back(tBuilding);

			tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);			
			tBuilding.pos = vec3(195, 0, i-15);
			buildings.push_back(tBuilding);

			tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);
			tBuilding.pos = vec3(185, 0, i-15);
			buildings.push_back(tBuilding);

			tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);
			tBuilding.pos = vec3(175, 0, i-15);
			buildings.push_back(tBuilding);
			tBuilding.scaler = 4;
		}
		else if(skipCounter == 10 || skipCounter == 16){
			tBuilding.scaler = 3;
			tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);
			tBuilding.rotation = 180;
			tBuilding.pos = vec3(185, 0, i+5);
			buildings.push_back(tBuilding);

			tBuilding.scaler = 1;
			tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);
			tBuilding.pos = vec3(205, 0, i-5);
			buildings.push_back(tBuilding);

			tBuilding.scaler = 3;
			tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);
			tBuilding.pos = vec3(225, 0, i+5);
			buildings.push_back(tBuilding);
			tBuilding.scaler = 4;
		}
		//End Col 5//

		//Col 6//
		if(skipCounter != 5 && skipCounter != 6 && skipCounter != 10 && skipCounter != 11 && skipCounter != 16 && skipCounter != 17){
			tBuilding.rotation = 270;
			tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);
			tBuilding.pos = vec3(300, 0, i);
			buildings.push_back(tBuilding);

			tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);
			tBuilding.rotation = 90;
			tBuilding.pos = vec3(390, 0, i);
			buildings.push_back(tBuilding);

			if(skipCounter == 1 || skipCounter == 12){
				tBuilding.scaler = 3;
				tBuilding.rotation = 0;
				tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);			
				tBuilding.pos = vec3(335, 0, i+5);
				buildings.push_back(tBuilding);

				tBuilding.scaler = 2;
				tBuilding.rotation = 0;
				tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);			
				tBuilding.pos = vec3(360, 0, i+10);
				buildings.push_back(tBuilding);
				tBuilding.scaler = 4;
			}
			if(skipCounter == 21){
				tBuilding.scaler = 3;
				tBuilding.rotation = 180;
				tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);			
				tBuilding.pos = vec3(335, 0, i-5);
				buildings.push_back(tBuilding);

				tBuilding.scaler = 2;
				tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);			
				tBuilding.pos = vec3(360, 0, i-10);
				buildings.push_back(tBuilding);
				tBuilding.scaler = 4;
			}
		}
		else if(skipCounter == 5){
			tBuilding.scaler = 2;
			tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);
			tBuilding.rotation = 180;
			tBuilding.pos = vec3(290, 0, i+10);
			buildings.push_back(tBuilding);

			tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);
			tBuilding.pos = vec3(310, 0, i+10);
			buildings.push_back(tBuilding);

			tBuilding.scaler = 3;
			tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);
			tBuilding.pos = vec3(335, 0, i+15);
			buildings.push_back(tBuilding);

			tBuilding.scaler = 2;
			tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);
			tBuilding.pos = vec3(360, 0, i+10);
			buildings.push_back(tBuilding);

			tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);
			tBuilding.pos = vec3(380, 0, i+10);
			buildings.push_back(tBuilding);

			tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);
			tBuilding.pos = vec3(400, 0, i+10);
			buildings.push_back(tBuilding);
			tBuilding.scaler = 4;
		}
		else if(skipCounter == 6){
			tBuilding.scaler = 2;
			tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);
			tBuilding.rotation = 0;
			tBuilding.pos = vec3(290, 0, i-10);
			buildings.push_back(tBuilding);

			tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);
			tBuilding.pos = vec3(310, 0, i-10);
			buildings.push_back(tBuilding);

			tBuilding.scaler = 3;
			tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);
			tBuilding.pos = vec3(335, 0, i-15);
			buildings.push_back(tBuilding);

			tBuilding.scaler = 2;
			tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);
			tBuilding.pos = vec3(360, 0, i-10);
			buildings.push_back(tBuilding);

			tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);
			tBuilding.pos = vec3(380, 0, i-10);
			buildings.push_back(tBuilding);

			tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);
			tBuilding.pos = vec3(400, 0, i-10);
			buildings.push_back(tBuilding);
			tBuilding.scaler = 4;
		}
		else if(skipCounter == 10 || skipCounter == 16){
			tBuilding.scaler = 3;
			tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);
			tBuilding.rotation = 180;
			tBuilding.pos = vec3(295, 0, i+5);
			buildings.push_back(tBuilding);

			tBuilding.scaler = 2;
			tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);
			tBuilding.pos = vec3(320, 0, i);
			buildings.push_back(tBuilding);

			tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);
			tBuilding.pos = vec3(340, 0, i);
			buildings.push_back(tBuilding);

			tBuilding.scaler = 3;
			tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);
			tBuilding.pos = vec3(365, 0, i+5);
			buildings.push_back(tBuilding);

			tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);
			tBuilding.pos = vec3(395, 0, i+5);
			buildings.push_back(tBuilding);
			tBuilding.scaler = 4;
		}
		else if(skipCounter == 17){
			tBuilding.scaler = 1;
			tBuilding.rotation = 0;
			tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);			
			tBuilding.pos = vec3(405, 0, i-15);
			buildings.push_back(tBuilding);

			tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);
			tBuilding.pos = vec3(395, 0, i-15);
			buildings.push_back(tBuilding);

			tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);
			tBuilding.pos = vec3(385, 0, i-15);
			buildings.push_back(tBuilding);

			tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);			
			tBuilding.pos = vec3(375, 0, i-15);
			buildings.push_back(tBuilding);

			tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);			
			tBuilding.pos = vec3(365, 0, i-15);
			buildings.push_back(tBuilding);

			tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);
			tBuilding.pos = vec3(355, 0, i-15);
			buildings.push_back(tBuilding);

			tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);
			tBuilding.pos = vec3(345, 0, i-15);
			buildings.push_back(tBuilding);

			tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);
			tBuilding.pos = vec3(335, 0, i-15);
			buildings.push_back(tBuilding);

			tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);			
			tBuilding.pos = vec3(325, 0, i-15);
			buildings.push_back(tBuilding);

			tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);			
			tBuilding.pos = vec3(315, 0, i-15);
			buildings.push_back(tBuilding);

			tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);
			tBuilding.pos = vec3(305, 0, i-15);
			buildings.push_back(tBuilding);

			tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);
			tBuilding.pos = vec3(295, 0, i-15);
			buildings.push_back(tBuilding);

			tBuilding.buildingType = (int) (5*(float) rand() / (RAND_MAX)+1);
			tBuilding.pos = vec3(285, 0, i-15);
			buildings.push_back(tBuilding);
			tBuilding.scaler = 4;
		}
		//End Col 6//

		skipCounter++;
	}

	//End buildings facing up/down

	//////Rectangular Obstacles//////

	//Yellow Corner
	int scaler = 3;
	tRect.dimensions = vec3(scaler*10, scaler*10, scaler*10);
	tRect.pos = vec3(-425, 0, 485);		
	rectangularObstacles.push_back(tRect);

	scaler = 2;
	tRect.dimensions = vec3(scaler*10, scaler*10, scaler*10);
	tRect.pos = vec3(-450, 0, 490);	
	rectangularObstacles.push_back(tRect);
	tRect.pos = vec3(-490, 0, 450);	
	rectangularObstacles.push_back(tRect);

	scaler = 1;
	tRect.dimensions = vec3(scaler*10, scaler*10, scaler*10);
	tRect.pos = vec3(-495, 0, 465);	
	rectangularObstacles.push_back(tRect);
	tRect.pos = vec3(-465, 0, 495);
	rectangularObstacles.push_back(tRect);
	
	//Yellow-green Wall
	tRect.dimensions = vec3(4*10, 10, 850);
	tRect.pos = vec3(-480, 0, 15);	
	rectangularObstacles.push_back(tRect);

	//Green corner
	scaler = 3;
	tRect.dimensions = vec3(scaler*10, scaler*10, scaler*10);
	tRect.pos = vec3(-485, 0, -425);		
	rectangularObstacles.push_back(tRect);

	scaler = 2;
	tRect.dimensions = vec3(scaler*10, scaler*10, scaler*10);
	tRect.pos = vec3(-450, 0, -490);	
	rectangularObstacles.push_back(tRect);
	tRect.pos = vec3(-490, 0, -450);	
	rectangularObstacles.push_back(tRect);
	tRect.pos = vec3(450, 0, -490);	
	rectangularObstacles.push_back(tRect);

	scaler = 1;
	tRect.dimensions = vec3(scaler*10, scaler*10, scaler*10);
	tRect.pos = vec3(-495, 0, -465);	
	rectangularObstacles.push_back(tRect);
	tRect.pos = vec3(-465, 0, -495);
	rectangularObstacles.push_back(tRect);
	tRect.pos = vec3(465, 0, -495);	
	rectangularObstacles.push_back(tRect);
	tRect.pos = vec3(465, 0, -495);	
	rectangularObstacles.push_back(tRect);

	//Green-blue Wall
	tRect.dimensions = vec3(880, 10, 40);
	tRect.pos = vec3(0, 0, -480);	
	rectangularObstacles.push_back(tRect);

	//Blue corner
	scaler = 3;
	tRect.dimensions = vec3(scaler*10, scaler*10, scaler*10);
	tRect.pos = vec3(485, 0, -425);		
	rectangularObstacles.push_back(tRect);

	scaler = 2;
	tRect.dimensions = vec3(scaler*10, scaler*10, scaler*10);
	tRect.pos = vec3(490, 0, -450);	
	rectangularObstacles.push_back(tRect);
	tRect.pos = vec3(470, 0, 400);	
	rectangularObstacles.push_back(tRect);

	scaler = 1;
	tRect.dimensions = vec3(scaler*10, scaler*10, scaler*10);
	tRect.pos = vec3(495, 0, -465);	
	rectangularObstacles.push_back(tRect);

	//Blue-red Wall
	tRect.dimensions = vec3(40, 10, 820);
	tRect.pos = vec3(480, 0, 0);	
	rectangularObstacles.push_back(tRect);

	//Red corner
	scaler = 3;
	tRect.dimensions = vec3(scaler*10, scaler*10, scaler*10);
	tRect.pos = vec3(485, 0, 425);		
	rectangularObstacles.push_back(tRect);

	scaler = 2;
	tRect.dimensions = vec3(scaler*10, scaler*10, scaler*10);
	tRect.pos = vec3(490, 0, 450);	
	rectangularObstacles.push_back(tRect);
	tRect.pos = vec3(450, 0, 490);	
	rectangularObstacles.push_back(tRect);

	scaler = 1;
	tRect.dimensions = vec3(scaler*10, scaler*10, scaler*10);
	tRect.pos = vec3(495, 0, 465);	
	rectangularObstacles.push_back(tRect);
	tRect.pos = vec3(465, 0, 495);	
	rectangularObstacles.push_back(tRect);
	tRect.pos = vec3(-405, 0, 465);	
	rectangularObstacles.push_back(tRect);

	//Red-yellow Wall
	tRect.dimensions = vec3(850, 10, 40);
	tRect.pos = vec3(15, 0, 480);	
	rectangularObstacles.push_back(tRect);

	//

	//Yellow corner
	tRect.dimensions = vec3(120, 10, 180);
	tRect.pos = vec3(-350, 0, 330);	
	rectangularObstacles.push_back(tRect);

	//Green corner
	tRect.dimensions = vec3(120, 10, 190);
	tRect.pos = vec3(-350, 0, -325);	
	rectangularObstacles.push_back(tRect);

	//Blue corner
	tRect.dimensions = vec3(130, 10, 170);
	tRect.pos = vec3(345, 0, -335);	
	rectangularObstacles.push_back(tRect);

	//Red corner
	tRect.dimensions = vec3(130, 10, 180);
	tRect.pos = vec3(345, 0, 330);	
	rectangularObstacles.push_back(tRect);

	//Col 1
	tRect.dimensions = vec3(120, 10, 180);
	tRect.pos = vec3(-350, 0, 110);	
	rectangularObstacles.push_back(tRect);

	tRect.dimensions = vec3(120, 10, 150);
	tRect.pos = vec3(-350, 0, -105);	
	rectangularObstacles.push_back(tRect);

	//Col 2
	tRect.dimensions = vec3(90, 10, 180);
	tRect.pos = vec3(-205, 0, 330);	
	rectangularObstacles.push_back(tRect);

	tRect.dimensions = vec3(90, 10, 180);
	tRect.pos = vec3(-205, 0, 110);	
	rectangularObstacles.push_back(tRect);

	tRect.dimensions = vec3(90, 10, 390);
	tRect.pos = vec3(-205, 0, -225);	
	rectangularObstacles.push_back(tRect);

	//Col 3
	tRect.dimensions = vec3(60, 10, 180);
	tRect.pos = vec3(-80, 0, 330);	
	rectangularObstacles.push_back(tRect);

	tRect.dimensions = vec3(60, 10, 150);
	tRect.pos = vec3(-80, 0, 125);	
	rectangularObstacles.push_back(tRect);

	tRect.dimensions = vec3(60, 10, 160);
	tRect.pos = vec3(-80, 0, -130);	
	rectangularObstacles.push_back(tRect);

	tRect.dimensions = vec3(60, 10, 170);
	tRect.pos = vec3(-80, 0, -335);	
	rectangularObstacles.push_back(tRect);

	//Col 4
	tRect.dimensions = vec3(70, 10, 180);
	tRect.pos = vec3(85, 0, 330);	
	rectangularObstacles.push_back(tRect);

	tRect.dimensions = vec3(70, 10, 150);
	tRect.pos = vec3(85, 0, 125);	
	rectangularObstacles.push_back(tRect);

	tRect.dimensions = vec3(70, 10, 160);
	tRect.pos = vec3(85, 0, -130);	
	rectangularObstacles.push_back(tRect);

	tRect.dimensions = vec3(70, 10, 170);
	tRect.pos = vec3(85, 0, -335);	
	rectangularObstacles.push_back(tRect);

	//Col 5
	tRect.dimensions = vec3(70, 10, 390);
	tRect.pos = vec3(205, 0, 225);	
	rectangularObstacles.push_back(tRect);

	tRect.dimensions = vec3(70, 10, 190);
	tRect.pos = vec3(205, 0, -115);	
	rectangularObstacles.push_back(tRect);

	tRect.dimensions = vec3(70, 10, 170);
	tRect.pos = vec3(205, 0, -335);	
	rectangularObstacles.push_back(tRect);

	//Col 6
	tRect.dimensions = vec3(130, 10, 170);
	tRect.pos = vec3(345, 0, 115);	
	rectangularObstacles.push_back(tRect);

	tRect.dimensions = vec3(130, 10, 190);
	tRect.pos = vec3(345, 0, -115);	
	rectangularObstacles.push_back(tRect);

	///Courtyard
	//Arches
	tRect.dimensions = vec3(10, 10, 10);
	tRect.pos = vec3(65, 0, 15);	
	rectangularObstacles.push_back(tRect);
	tRect.pos = vec3(65, 0, -15);	
	rectangularObstacles.push_back(tRect);
	tRect.pos = vec3(-65, 0, 15);	
	rectangularObstacles.push_back(tRect);
	tRect.pos = vec3(-65, 0, -15);	
	rectangularObstacles.push_back(tRect);
	tRect.pos = vec3(15, 0, 65);	
	rectangularObstacles.push_back(tRect);
	tRect.pos = vec3(15, 0, -65);	
	rectangularObstacles.push_back(tRect);
	tRect.pos = vec3(-15, 0, 65);	
	rectangularObstacles.push_back(tRect);
	tRect.pos = vec3(-15, 0, -65);	
	rectangularObstacles.push_back(tRect);
	//Statue
	tRect.dimensions = vec3(20, 10, 20);
	tRect.pos = vec3(0, 0, 0);	
	rectangularObstacles.push_back(tRect);
	//Pools
	tRect.dimensions = vec3(20, 1, 80);
	tRect.pos = vec3(0, 0, 220);	
	rectangularObstacles.push_back(tRect);
	tRect.dimensions = vec3(20, 1, 80);
	tRect.pos = vec3(0, 0, -230);	
	rectangularObstacles.push_back(tRect);

	this->base->color = vec3(1,0,0);
	this->base->Initialize(10, 50, 30, 30, "phong3.vert", "phong3.frag");

	tmpX=0;tmpZ=0;tmpR=0;tmpS=1;
	this->roadStraight.Initialize(1, 1.f, "./textures/roadStraight.png", "basic_texture_shader.vert", "basic_texture_shader.frag");
	
	//this->floor.Initialize(100, 1000.0f, "./textures/floorPattern.jpg", "basic_texture_shader.vert", "basic_texture_shader.frag");
	this->floor.order = 1;
	this->floor.Initialize("./models/city.obj", "./models/city.png", "basic_texture_shader.vert", "basic_texture_shader.frag");
	//this->roof->Initialize(1, 1000.0f, "./textures/wall3.jpg", "basic_texture_shader.vert", "roof_shader.frag");

	this->wall->Initialize(1, 50.0f, "./textures/wireWall.png", "basic_texture_shader.vert", "basic_texture_shader2.frag");

	if (this->GLReturnedError("SquareStadium::Initialize - on exit"))
		return false;

	initialized = true;
	}

	return true;
}

//Delete the SquareStadium
void SquareStadium::TakeDown()
{
	this->tBuilding.TakeDown();this->roadStraight.TakeDown();this->floor.TakeDown();
	this->vertices.clear();this->shader.TakeDown();
	this->solid_color.TakeDown();
	super::TakeDown();
}

void SquareStadium::saveBuildingVertices(){
	ofstream outputFile;
outputFile.open("roadStraightData.txt");

for(int i=0; i<roadStraightXZRS.size(); i++){
	outputFile << "roadStraightXZRS.push_back(vec4(" << roadStraightXZRS.at(i).x << ", " << roadStraightXZRS.at(i).y
		<< ", " << roadStraightXZRS.at(i).z << ", " << roadStraightXZRS.at(i).w << "));" << endl;
}

outputFile.close();
}

//Draw and position the elements of the SquareStadium
void SquareStadium::Draw(const mat4 & projection, mat4 modelview, const ivec2 & size, const float time)
{
	if (this->GLReturnedError("SquareStadium::Draw - on entry"))
		return;

	glEnable(GL_DEPTH_TEST);



	mat4 another, floorMatrix, wallMatrix, wallMatrixReset;

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

	for(int i=0; i<buildings.size(); i++){
		buildingMatrix = modelview;
		buildingMatrix = translate(buildingMatrix, buildings.at(i).pos);		
		this->buildings.at(i).Draw(projection, buildingMatrix, size, 0);
	}

	//Elements of the arena.
	floorMatrix = modelview;
	this->floor.Draw(projection, modelview, size, time);

	modelview = translate(modelview, vec3(499.f,0.f,500.f));

	

	floorMatrix = translate(floorMatrix, vec3(0,250,0));
	//this->roof->Draw(projection, floorMatrix, size, time);

	int subWallSpacing = 50;
	int numSubWalls = 2;

	//0=red; 2.5=yellow; 5=green; 7.5=blue;
	wallMatrix = modelview;
	wallMatrix = rotate(wallMatrix, 180.f, vec3(0,1,0));
	wallMatrixReset = wallMatrix;
	for(int i=0; i<numSubWalls; i++){ //Red
		wallMatrix = translate(wallMatrixReset, vec3(i*subWallSpacing, 50, 0));
		wallMatrix = rotate(wallMatrix, 90.f, vec3(1,0,0));
		wallMatrix = rotate(wallMatrix, 180.f, vec3(0,1,0));
		wallMatrix = rotate(wallMatrix, 180.f, vec3(0,0,1));
		this->wall->Draw(projection, wallMatrix, size, 0);
		wallMatrix = translate(wallMatrix, vec3(0,0,50));
		this->wall->Draw(projection, wallMatrix, size, 0);
		wallMatrix = translate(wallMatrix, vec3(0,0,50));
		this->wall->Draw(projection, wallMatrix, size, 0);
	}

	for(int i=19; i<19+numSubWalls; i++){ //Yellow
		wallMatrix = translate(wallMatrixReset, vec3(i*subWallSpacing, 50, 0));
		wallMatrix = rotate(wallMatrix, 90.f, vec3(1,0,0));
		wallMatrix = rotate(wallMatrix, 180.f, vec3(0,1,0));
		wallMatrix = rotate(wallMatrix, 180.f, vec3(0,0,1));
		this->wall->Draw(projection, wallMatrix, size, 2.5);
		wallMatrix = translate(wallMatrix, vec3(0,0,50));
		this->wall->Draw(projection, wallMatrix, size, 2.5);
		wallMatrix = translate(wallMatrix, vec3(0,0,50));
		this->wall->Draw(projection, wallMatrix, size, 2.5);
	}
	
	wallMatrix = translate(modelview, vec3(1, 0, -1000));
	wallMatrix = rotate(wallMatrix, 270.f, vec3(0,1,0));
	wallMatrixReset = wallMatrix;
	for(int i=0; i<numSubWalls; i++){ //Green
		wallMatrix = translate(wallMatrixReset, vec3(i*subWallSpacing, 50, 0));
		wallMatrix = rotate(wallMatrix, 90.f, vec3(1,0,0));
		wallMatrix = translate(wallMatrix, vec3(0,1000,0));
		wallMatrix = rotate(wallMatrix, 180.f, vec3(0,1,0));
		this->wall->Draw(projection, wallMatrix, size, 5);
		wallMatrix = translate(wallMatrix, vec3(0,0,50));
		this->wall->Draw(projection, wallMatrix, size, 5);
		wallMatrix = translate(wallMatrix, vec3(0,0,50));
		this->wall->Draw(projection, wallMatrix, size, 5);
	}
	for(int i=19; i<19+numSubWalls; i++){ //Yellow
		wallMatrix = translate(wallMatrixReset, vec3(i*subWallSpacing, 50, 0));
		wallMatrix = rotate(wallMatrix, 90.f, vec3(1,0,0));
		wallMatrix = translate(wallMatrix, vec3(0,1000,0));
		wallMatrix = rotate(wallMatrix, 180.f, vec3(0,1,0));
		this->wall->Draw(projection, wallMatrix, size, 2.5);
		wallMatrix = translate(wallMatrix, vec3(0,0,50));
		this->wall->Draw(projection, wallMatrix, size, 2.5);
		wallMatrix = translate(wallMatrix, vec3(0,0,50));
		this->wall->Draw(projection, wallMatrix, size, 2.5);		
	}

	wallMatrix = translate(modelview, vec3(1, 0, -1000));
	wallMatrix = rotate(wallMatrix, 270.f, vec3(0,1,0));
	wallMatrixReset = wallMatrix;
	for(int i=0; i<numSubWalls; i++){ //Blue
		wallMatrix = translate(wallMatrixReset, vec3(i*subWallSpacing, 50, 0));
		wallMatrix = rotate(wallMatrix, 90.f, vec3(1,0,0));
		wallMatrix = rotate(wallMatrix, 180.f, vec3(0,1,0));
		wallMatrix = rotate(wallMatrix, 180.f, vec3(0,0,1));
		this->wall->Draw(projection, wallMatrix, size, 7.5);
		wallMatrix = translate(wallMatrix, vec3(0,0,50));
		this->wall->Draw(projection, wallMatrix, size, 7.5);
		wallMatrix = translate(wallMatrix, vec3(0,0,50));
		this->wall->Draw(projection, wallMatrix, size, 7.5);
	}
	for(int i=19; i<19+numSubWalls; i++){ //Red
		wallMatrix = translate(wallMatrixReset, vec3(i*subWallSpacing, 50, 0));
		wallMatrix = rotate(wallMatrix, 90.f, vec3(1,0,0));
		wallMatrix = rotate(wallMatrix, 180.f, vec3(0,1,0));
		wallMatrix = rotate(wallMatrix, 180.f, vec3(0,0,1));
		this->wall->Draw(projection, wallMatrix, size, 0);
		wallMatrix = translate(wallMatrix, vec3(0,0,50));
		this->wall->Draw(projection, wallMatrix, size, 0);
		wallMatrix = translate(wallMatrix, vec3(0,0,50));
		this->wall->Draw(projection, wallMatrix, size, 0);
	}

	wallMatrix = translate(modelview, vec3(0, 0, -1000));
	wallMatrix = rotate(wallMatrix, 180.f, vec3(0,1,0));
	wallMatrixReset = wallMatrix;
	for(int i=0; i<numSubWalls; i++){ //Blue
		wallMatrix = translate(wallMatrixReset, vec3(i*subWallSpacing, 50, 0));
		wallMatrix = rotate(wallMatrix, 90.f, vec3(1,0,0));
		wallMatrix = rotate(wallMatrix, 180.f, vec3(0,1,0));
		this->wall->Draw(projection, wallMatrix, size, 7.5);
		wallMatrix = translate(wallMatrix, vec3(0,0,50));
		this->wall->Draw(projection, wallMatrix, size, 7.5);
		wallMatrix = translate(wallMatrix, vec3(0,0,50));
		this->wall->Draw(projection, wallMatrix, size, 7.5);
	}
	for(int i=19; i<19+numSubWalls; i++){ //Green
		wallMatrix = translate(wallMatrixReset, vec3(i*subWallSpacing, 50, 0));
		wallMatrix = rotate(wallMatrix, 90.f, vec3(1,0,0));
		wallMatrix = rotate(wallMatrix, 180.f, vec3(0,1,0));
		this->wall->Draw(projection, wallMatrix, size, 5);
		wallMatrix = translate(wallMatrix, vec3(0,0,50));
		this->wall->Draw(projection, wallMatrix, size, 5);
		wallMatrix = translate(wallMatrix, vec3(0,0,50));
		this->wall->Draw(projection, wallMatrix, size, 5);
	}

	//glDepthMask(GL_FALSE);

	/*another = translate(modelview, vec3(-5, 0, -5));
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
	this->base->Draw(projection, another, size, 0);*/

   //glDepthMask(GL_TRUE);

	if (this->GLReturnedError("SquareStadium::Draw - on exit"))
		return;
}
