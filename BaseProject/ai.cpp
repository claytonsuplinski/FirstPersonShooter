/*
Name: Clayton Suplinski
Project: First-Person Shooter
*/

#include "ai.h"

AI::AI(){
}

AI::~AI(){}

//Controls how/where the computers move and when they shoot
void AI::MoveComputers(Team * yellow, Team * blue, Team * green, Team * red, vector<Building> * buildings, 
	vector<RectangularObstacle> * rectangularObstacles){

	float current_timeDisplay = float(glutGet(GLUT_ELAPSED_TIME)) / 1000.0f;
	
	Team * currTeam;
	Team * otherTeam;
	Team * otherTeam2;
	Team * otherTeam3;
				
	currTeam = yellow;
	//Get building distances from user
	for(unsigned int k=0; k<buildings->size(); k++){
		float tmpDistUser = currTeam->dist(buildings->at(k).pos.x, buildings->at(k).pos.y, buildings->at(k).pos.z,
			currTeam->soldiers[0].pos.z, currTeam->soldiers[0].pos.y, -currTeam->soldiers[0].pos.x);
		buildings->at(k).distFromUser = tmpDistUser;
	}

	//Go through every team
	for(int p=0; p<4; p++){

		switch(p){
		case 0:
			currTeam = yellow;
			otherTeam = blue;
			otherTeam2 = green;
			otherTeam3 = red;
			break;
		case 1:
			currTeam = red;
			otherTeam = blue;
			otherTeam2 = green;
			otherTeam3 = yellow;
			break;
		case 2:
			currTeam = blue;
			otherTeam = yellow;
			otherTeam2 = green;
			otherTeam3 = red;
			break;
		case 3:
			currTeam = green;
			otherTeam = blue;
			otherTeam2 = yellow;
			otherTeam3 = red;
			break;
		}

		float cpuSpeed;

		float angleConst = 3.14f/180.f;
		float minDist = 9999999;float min1 = 9999999;float min2 = 9999999;float min3 = 9999999;
		Team * closestTeam; 
		int closestIndex = -1;int closest1 = -1;int closest2 = -1;int closest3 = -1;
		RectangularObstacle closestBuilding, closestBuilding2, closestBuilding3, closestBuilding4;
		float closestBuildingDist = 9999999;float closestBuilding2Dist = 9999999;
		float closestBuilding3Dist = 9999999;float closestBuilding4Dist = 9999999;

		bool avoidWall = false;bool buildingInWay = false;bool buildingInWay2 = false;bool buildingInFront = false;
		float rotRatio = 1;

		float dist1, dist2, dist3;
		for(int i=(currTeam->userTeam ? 1 : 0); i<currTeam->NUM_SOLDIERS; i++){ //For each soldier on this team
			if(!currTeam->soldiers[i].dead){
				avoidWall = false;
				
				//Get 4 closest buildings
				for(unsigned int k=0; k<rectangularObstacles->size(); k++){
					float tmpDist = currTeam->dist(rectangularObstacles->at(k).pos.x, rectangularObstacles->at(k).pos.y, rectangularObstacles->at(k).pos.z,
						currTeam->soldiers[i].pos.z, currTeam->soldiers[i].pos.y, -currTeam->soldiers[i].pos.x);

					if(tmpDist < closestBuildingDist){
						closestBuilding4Dist = closestBuilding3Dist;
						closestBuilding4 = closestBuilding3;
						closestBuilding3Dist = closestBuilding2Dist;
						closestBuilding3 = closestBuilding2;
						closestBuilding2Dist = closestBuildingDist;
						closestBuilding2 = closestBuilding;
						closestBuildingDist = tmpDist;
						closestBuilding = rectangularObstacles->at(k);
					}
					else if(tmpDist < closestBuilding2Dist){
						closestBuilding4Dist = closestBuilding3Dist;
						closestBuilding4 = closestBuilding3;
						closestBuilding3Dist = closestBuilding2Dist;
						closestBuilding3 = closestBuilding2;
						closestBuilding2Dist = tmpDist;
						closestBuilding2 = rectangularObstacles->at(k);
					}
					else if(tmpDist < closestBuilding3Dist){
						closestBuilding4Dist = closestBuilding3Dist;
						closestBuilding4 = closestBuilding3;
						closestBuilding3Dist = tmpDist;
						closestBuilding3 = rectangularObstacles->at(k);
					}
					else if(tmpDist < closestBuilding4Dist){
						closestBuilding4Dist = tmpDist;
						closestBuilding4 = rectangularObstacles->at(k);
					}
				}

				for(int j=0; j<currTeam->NUM_SOLDIERS; j++){ //Check distances for each soldier on the other teams
					if(!otherTeam->soldiers[j].dead){
						dist1 = currTeam->dist(otherTeam->soldiers[j].pos.x, otherTeam->soldiers[j].pos.y, otherTeam->soldiers[j].pos.z, 
							currTeam->soldiers[i].pos.x, currTeam->soldiers[i].pos.y, currTeam->soldiers[i].pos.z);
						if(dist1 < minDist){minDist = dist1;closestTeam = otherTeam;closestIndex = j;min1 = dist1;closest1 = j;}
						else if(dist1 < min1){min1 = dist1;closest1 = j;}
					}
					if(!otherTeam2->soldiers[j].dead){
						dist2 = currTeam->dist(otherTeam2->soldiers[j].pos.x, otherTeam2->soldiers[j].pos.y, otherTeam2->soldiers[j].pos.z, 
							currTeam->soldiers[i].pos.x, currTeam->soldiers[i].pos.y, currTeam->soldiers[i].pos.z);
						if(dist2 < minDist){minDist = dist2;closestTeam = otherTeam2;closestIndex = j;min2 = dist2;closest2 = j;}
						else if(dist2 < min2){min2 = dist2;closest2 = j;}
					}
					if(!otherTeam3->soldiers[j].dead){
						dist3 = currTeam->dist(otherTeam3->soldiers[j].pos.x, otherTeam3->soldiers[j].pos.y, otherTeam3->soldiers[j].pos.z, 
							currTeam->soldiers[i].pos.x, currTeam->soldiers[i].pos.y, currTeam->soldiers[i].pos.z);
						if(dist3 < minDist){minDist = dist3;closestTeam = otherTeam3;closestIndex = j;min3 = dist3;closest3 = j;}
						else if(dist3 < min3){min3 = dist3;closest3 = j;}
					}
				}//end j for

				//Move the soldiers on this team towards the closest targeted enemy
				if(minDist < 9999999 && minDist > 0 && closestIndex > -1){
					float rotation = 2;//(float) rand() / (RAND_MAX)+1;
					Soldier targetSoldier;
					switch(currTeam->soldiers[i].planOfAttack){
					case 1:
					default:
						targetSoldier = closestTeam->soldiers[closestIndex];
						break;
					case 2:
						if(min1 < 9999999 && minDist > 75){targetSoldier = otherTeam->soldiers[closest1];}
						else{targetSoldier = closestTeam->soldiers[closestIndex];}
						break;
					case 3:
						if(min2 < 9999999 && minDist > 75){targetSoldier = otherTeam2->soldiers[closest2];}
						else{targetSoldier = closestTeam->soldiers[closestIndex];}
						break;
					case 4:
						if(min3 < 9999999 && minDist > 75){targetSoldier = otherTeam3->soldiers[closest3];}
						else{targetSoldier = closestTeam->soldiers[closestIndex];}
						break;
					}

					float minEnemyDist = 9999999;
					float minBuildingDist = 9999999;
					float rotB = 0;
					float maxBuildingDistL = 0;float maxBuildingDistR = 0;
					float rotBL = 0; float rotBR = 0; //Best angle for nearest building
					float maxBuildingDist2L = 0;float maxBuildingDist2R = 0;
					float rotB2L = 0; float rotB2R = 0; //Best angle for nearest building
					float rotE = 0; //Best angle for nearest enemy

					int cb = 1;
					buildingInWay = currTeam->buildingInWay(currTeam->soldiers[i].pos, targetSoldier.pos, closestBuilding);
					if(!buildingInWay){
						buildingInWay = currTeam->buildingInWay(currTeam->soldiers[i].pos, targetSoldier.pos, closestBuilding2);
						if(buildingInWay){
							closestBuilding = closestBuilding2;
							cb = 2;
						}
						else{
							buildingInWay = currTeam->buildingInWay(currTeam->soldiers[i].pos, targetSoldier.pos, closestBuilding3);
							if(buildingInWay){
								closestBuilding = closestBuilding3;
								cb = 3;
							}
							else{
								buildingInWay = currTeam->buildingInWay(currTeam->soldiers[i].pos, targetSoldier.pos, closestBuilding4);
								if(buildingInWay){
									closestBuilding = closestBuilding4;
									cb = 4;
								}
							}
						}
					}

					for(int m = -30; m<31; m+=2){
						float tmpDist = currTeam->dist(currTeam->soldiers[i].pos.x+0.5f*cos(-(currTeam->soldiers[i].hRot+m)*angleConst), 
							currTeam->soldiers[i].pos.y, currTeam->soldiers[i].pos.z+0.5f*sin(-(currTeam->soldiers[i].hRot+m)*angleConst),
						targetSoldier.pos.x, targetSoldier.pos.y, targetSoldier.pos.z);
						if(tmpDist < minEnemyDist){
							minEnemyDist = tmpDist;
							rotE = (float)(m);
						}
					}

					if(buildingInWay){
						for(int m = 0; m<91; m+=5){
								vec3 tmpPos = vec3(currTeam->soldiers[i].pos.x+200*cos(-(currTeam->soldiers[i].hRot+m)*angleConst), 
									0, currTeam->soldiers[i].pos.z+200*sin(-(currTeam->soldiers[i].hRot+m)*angleConst));
								if(!currTeam->buildingInWay(currTeam->soldiers[i].pos, tmpPos, closestBuilding)){
									rotB = (float)(m);
									m += 95;
								}
								else{
									tmpPos = vec3(currTeam->soldiers[i].pos.x+200*cos(-(currTeam->soldiers[i].hRot-m)*angleConst), 
									0, currTeam->soldiers[i].pos.z+200*sin(-(currTeam->soldiers[i].hRot-m)*angleConst));
									if(!currTeam->buildingInWay(currTeam->soldiers[i].pos, tmpPos, closestBuilding)){
										rotB = (float)(-m);
										m+=95;
									}
								}
						}
					}


					if(buildingInWay){
						float cbDist = currTeam->distFromBuilding(currTeam->soldiers[i].pos, closestBuilding, 0.5);
						float rotBRatio = 1 - cbDist/10;
						if(rotBRatio < 0){rotBRatio = 0;}
						else if(rotBRatio > 1){rotBRatio = 1;}
						rotation = rotB;
					}
					else{
						rotation = rotE;
					}			
				
					if(currTeam->soldiers[i].person.velocity < 0){
						currTeam->soldiers[i].person.velocity=0;
					}
					else if(currTeam->soldiers[i].person.velocity > currTeam->soldiers[i].person.MAX_VELOCITY){
						currTeam->soldiers[i].person.velocity = currTeam->soldiers[i].person.MAX_VELOCITY;
					}

					//cpuSpeed = soldiers[i].person->velocity;
					cpuSpeed = 0.5;
					currTeam->soldiers[i].person.velocity = cpuSpeed;
					currTeam->soldiers[i].hRot += rotation;
					currTeam->soldiers[i].hRot = fmod(currTeam->soldiers[i].hRot, 360.f);
					currTeam->soldiers[i].pos.x += (float)(cpuSpeed*cos(-currTeam->soldiers[i].hRot*angleConst));

					//If the cpu ran into something, don't let them run through it
					if(abs(currTeam->soldiers[i].pos.x) > 500.0f || currTeam->ranIntoBuilding(vec3(currTeam->soldiers[i].pos.z, 0, -currTeam->soldiers[i].pos.x), 0.5)){
						float centerDistL = currTeam->dist(currTeam->soldiers[i].pos.x+0.5f*cos(-(currTeam->soldiers[i].hRot-90)*angleConst), 
							currTeam->soldiers[i].pos.y, currTeam->soldiers[i].pos.z+0.5f*sin(-(currTeam->soldiers[i].hRot-90)*angleConst),
							0,0,0);
						float centerDistR = currTeam->dist(currTeam->soldiers[i].pos.x+0.5f*cos(-(currTeam->soldiers[i].hRot+90)*angleConst), 
							currTeam->soldiers[i].pos.y, currTeam->soldiers[i].pos.z+0.5f*sin(-(currTeam->soldiers[i].hRot+90)*angleConst),
							0,0,0);
						currTeam->soldiers[i].pos.x -= (float)(cpuSpeed*cos(-currTeam->soldiers[i].hRot*angleConst));
						currTeam->soldiers[i].hRot += (centerDistR > centerDistL ? -90 : 90);
					}

					currTeam->soldiers[i].pos.z += (float)(cpuSpeed*sin(-currTeam->soldiers[i].hRot*angleConst));
					if(abs(currTeam->soldiers[i].pos.z) > 500.0f || currTeam->ranIntoBuilding(vec3(currTeam->soldiers[i].pos.z, 0, -currTeam->soldiers[i].pos.x), 0.5)){  
						float centerDistL = currTeam->dist(currTeam->soldiers[i].pos.x+0.5f*cos(-(currTeam->soldiers[i].hRot-90)*angleConst), 
							currTeam->soldiers[i].pos.y, currTeam->soldiers[i].pos.z+0.5f*sin(-(currTeam->soldiers[i].hRot-90)*angleConst),
							0,0,0);
						float centerDistR = currTeam->dist(currTeam->soldiers[i].pos.x+0.5f*cos(-(currTeam->soldiers[i].hRot+90)*angleConst), 
							currTeam->soldiers[i].pos.y, currTeam->soldiers[i].pos.z+0.5f*sin(-(currTeam->soldiers[i].hRot+90)*angleConst),
							0,0,0);
						currTeam->soldiers[i].pos.z -= (float)(cpuSpeed*sin(-currTeam->soldiers[i].hRot*angleConst));
						currTeam->soldiers[i].hRot += (centerDistR > centerDistL ? -90 : 90);
					}		
					
					//Determine whether to shoot or not
					if((float) rand() / (RAND_MAX) < 0.15*(1-minDist/250) && !buildingInWay && !buildingInWay2){
						if(current_timeDisplay - currTeam->soldiers[i].lastShot > 0.25){
							currTeam->firedBullet(i);
							currTeam->soldiers[i].lastShot = current_timeDisplay;
						}
					}
					//Determine whether to throw a grenade or not
					if((float) rand() / (RAND_MAX) < 0.1*(1-minDist/70)){
						if(current_timeDisplay - currTeam->soldiers[i].lastGrenade > 0.5){
							currTeam->threwGrenade(i);
							currTeam->soldiers[i].lastGrenade = current_timeDisplay;
						}
					}
				
				}
				minDist = 9999999;closestIndex = -1;
			}//end if
		}//end for




	}


} //end function