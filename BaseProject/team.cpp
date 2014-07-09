/*
Name: Clayton Suplinski
ID: 906 580 2630
CS 559 Project 3

Creates and organizes the team.
*/

#include <iostream>
#include "team.h"

using namespace std;
using namespace glm;

//Create the team
Team::Team() : Object(){
	userTeam = false;userTeam = false;drawBullet = false;
	teamNo = 0;
}

Team::~Team(){this->TakeDown();}

void Team::reset(){
	numRemaining = NUM_SOLDIERS;

	activeBullets.clear();
	activeGrenades.clear();
	activeCanisters.clear();

	tSoldier.person.velocity = 0;

	if(this->userTeam){tSoldier.user = true;tSoldier.name = "User";
	tSoldier.userCanisterCounter=0;tSoldier.userCanisterFlag=false;
	tSoldier.userDamageCounter=0;tSoldier.userDamageFlag=false;
	}
	else {tSoldier.name = teamColor + " 1";}

		soldiers[0] = tSoldier;
		
		soldiers[0].planOfAttack = 1;

		switch(teamNo){
		case 1: 
			soldiers[0].pos = vec3(-495.f, 0.f, -495.f); 
			soldiers[0].hRot = 315.f; 
			break;
		case 2:
			soldiers[0].pos = vec3(495.f, 0.f, -495.f);
			soldiers[0].hRot = 225.f;
			break;
		case 3:
			soldiers[0].pos = vec3(495.f, 0.f, 495.f); 
			soldiers[0].hRot = 135.f;
			break;
		case 4:
			soldiers[0].pos = vec3(-495.f, 0.f, 495.f);
			soldiers[0].hRot = 45.f;
			break;
		default:
			break;
		}

	tSoldier.user = false;tSoldier.person.user=false;
	for(int i=1; i<NUM_SOLDIERS; i++){
		stringstream soldierName (stringstream::in | stringstream::out);
		soldierName << i+1;
		tSoldier.name = teamColor + " " + soldierName.str();

		this->soldiers[i].userTeam = this->userTeam;
		this->soldiers[i] = tSoldier;

		float randAI = (float) rand() / (RAND_MAX);
		if(randAI < 0.25){soldiers[i].planOfAttack = 1;}
		else if(randAI < 0.5){soldiers[i].planOfAttack = 2;}
		else if(randAI < 0.75){soldiers[i].planOfAttack = 3;}
		else{soldiers[i].planOfAttack = 4;}


		float start_center = 495;
		float start_offset = 20;

		switch(teamNo){
		case 1: 
			soldiers[i].pos = vec3(-start_center + start_offset*((float) rand() / (RAND_MAX)), 0.f, -start_center + start_offset*((float) rand() / (RAND_MAX))); 
			break;
		case 2:
			soldiers[i].pos = vec3(start_center - start_offset*((float) rand() / (RAND_MAX)), 0.f, -start_center + start_offset*((float) rand() / (RAND_MAX))); 
			break;
		case 3:
			soldiers[i].pos = vec3(start_center - start_offset*((float) rand() / (RAND_MAX)), 0.f, start_center - start_offset*((float) rand() / (RAND_MAX))); 
			break;
		case 4:
			soldiers[i].pos = vec3(-start_center + start_offset*((float) rand() / (RAND_MAX)), 0.f, start_center - start_offset*((float) rand() / (RAND_MAX)));
			break;
		default:
			break;
		}
		soldiers[i].hRot = 360*((float) rand() / (RAND_MAX));
	}
}

//Initialize the team.
bool Team::Initialize(int teamNo)
{
	if (this->GLReturnedError("Team::Initialize - on entry"))
		return false;

	this->teamNo = teamNo;
	numRemaining = NUM_SOLDIERS;

	this->soldiers[0].userTeam = this->userTeam;

	switch(teamNo){
	case 1: //Team Yellow
		tBullet.Initialize(vec3(1.0f, 0.5f, 0.0f));teamColor = "Yellow";
		break;
	case 2: //Green
		tBullet.Initialize(vec3(0.f, 0.75f, 0.5f));teamColor = "Green";
		break;
	case 3: //Blue
		tBullet.Initialize(vec3(0.25f, 0.0f, 1.f));teamColor = "Blue";
		break;
	case 4: //Red
		tBullet.Initialize(vec3(0.75f, 0.f, 0.25f));teamColor = "Red";
		break;
	default:
		break;
	}

	tGrenade.Initialize(vec3(1,1,1));
	tCanister.Initialize(1);

	tSoldier.person.user = false;
	this->soldiers[0] = tSoldier;

	if(userTeam){this->soldiers[0].user = true;this->soldiers[0].person.user = true;this->soldiers[0].name = "User";}
	else {this->soldiers[0].name = teamColor + " 1";}
		
		soldiers[0].planOfAttack = 1;

		float start_center = 495;
		float start_offset = 20;

		switch(teamNo){
		case 1: 
			soldiers[0].pos = vec3(-start_center, 0.f, -start_center); 
			soldiers[0].hRot = 315.f; 
			break;
		case 2:
			soldiers[0].pos = vec3(start_center, 0.f, -start_center);
			soldiers[0].hRot = 225.f;
			break;
		case 3:
			soldiers[0].pos = vec3(start_center, 0.f, start_center); 
			soldiers[0].hRot = 135.f;
			break;
		case 4:
			soldiers[0].pos = vec3(-start_center, 0.f, start_center);
			soldiers[0].hRot = 45.f;
			break;
		default:
			break;
		}
			
	for(int i=1; i<NUM_SOLDIERS; i++){
		this->soldiers[i] = tSoldier;
		stringstream soldierName (stringstream::in | stringstream::out);
		soldierName << i+1;
		this->soldiers[i].name = teamColor + " " + soldierName.str();

		this->soldiers[i].userTeam = this->userTeam;		

		float randAI = (float) rand() / (RAND_MAX);
		if(randAI < 0.25){soldiers[i].planOfAttack = 1;}
		else if(randAI < 0.5){soldiers[i].planOfAttack = 2;}
		else if(randAI < 0.75){soldiers[i].planOfAttack = 3;}
		else{soldiers[i].planOfAttack = 4;}

		switch(teamNo){
		case 1: 
			soldiers[i].pos = vec3(-start_center + start_offset*((float) rand() / (RAND_MAX)), 0.f, -start_center + start_offset*((float) rand() / (RAND_MAX))); 
			break;
		case 2:
			soldiers[i].pos = vec3(start_center - start_offset*((float) rand() / (RAND_MAX)), 0.f, -start_center + start_offset*((float) rand() / (RAND_MAX))); 
			break;
		case 3:
			soldiers[i].pos = vec3(start_center - start_offset*((float) rand() / (RAND_MAX)), 0.f, start_center - start_offset*((float) rand() / (RAND_MAX))); 
			break;
		case 4:
			soldiers[i].pos = vec3(-start_center + start_offset*((float) rand() / (RAND_MAX)), 0.f, start_center - start_offset*((float) rand() / (RAND_MAX)));
			break;
		default:
			break;
		}
		soldiers[i].hRot = 360*((float) rand() / (RAND_MAX));
	}

	if (this->GLReturnedError("Team::Initialize - on exit"))
		return false;

	return true;
}

//Draw and position elements.
void Team::Draw(const mat4 & projection, mat4 modelview, const ivec2 & size, const float rotY)
{
	if (this->GLReturnedError("Team::Draw - on entry"))
		return;

	int t = glutGet(GLUT_ELAPSED_TIME);

	if(!drawBullet){ //Don't draw bullets, draw the soldiers
		
		glEnable(GL_DEPTH_TEST);
		mat4 another, refresh;
		another = modelview;refresh = modelview;

	/////////////////Draw the soldiers
	
		if(userTeam && drawUser){
			soldiers[0].Draw(projection, another, size, (float)(teamNo*2.5));
			another = refresh;
		}
		else if(userTeam && !drawUser){
			for(int i=1; i<NUM_SOLDIERS; i++){
				another = translate(another, vec3(soldiers[i].pos.x, soldiers[i].pos.y, soldiers[i].pos.z));
				another = rotate(another, soldiers[i].hRot, vec3(0,1,0));
				soldiers[i].Draw(projection, another, size, (float)(teamNo*2.5));
				another = refresh;
			}
		}
		else{
			for(int i=0; i<NUM_SOLDIERS; i++){
				another = translate(another, vec3(soldiers[i].pos.x, soldiers[i].pos.y, soldiers[i].pos.z));
				another = rotate(another, soldiers[i].hRot, vec3(0,1,0));
				soldiers[i].Draw(projection, another, size, (float)(teamNo*2.5));
				another = refresh;
			}
		}
	}
	else{  //Erasing extra items

		hpBounds();
		for(unsigned int i=0; i<activeBullets.size(); i++){
			if((activeBullets.at(i)).doneDrawing){
				activeBullets.erase(activeBullets.begin()+i);
			}
		}

		for(unsigned int i=0; i<activeGrenades.size(); i++){
			if((activeGrenades.at(i)).doneDrawing){
				activeGrenades.erase(activeGrenades.begin()+i);
			}
		}

		for(unsigned int i=0; i<activeCanisters.size(); i++){
			if((activeCanisters.at(i)).doneDrawing){
				activeCanisters.erase(activeCanisters.begin()+i);
			}
		}

		//modelview = translate(modelview, vec3(0.0f, 0.5f, 0.0f));

		modelview = translate(modelview, vec3(0.0f, 1.5f, 0.0f));
		modelview = rotate(modelview, 90.0f, vec3(0,1,0));

		mat4 bulletMatrix;
		////////////////////////Draw the active bullets
		for(unsigned int i=0; i<activeBullets.size(); i++){
			bulletMatrix = translate(modelview, (activeBullets.at(i)).currPos);
			bulletMatrix = rotate(bulletMatrix, (activeBullets.at(i)).rotY, vec3(0,1,0));
			activeBullets.at(i).Draw(projection, bulletMatrix, size, 0);
		}

		////////////////////////Draw the active grenades
		for(unsigned int i=0; i<activeGrenades.size(); i++){
			bulletMatrix = translate(modelview, (activeGrenades.at(i)).currPos);
			activeGrenades.at(i).Draw(projection, bulletMatrix, size, 0);
		}

		////////////////////////Draw the active canisters
		for(unsigned int i=0; i<activeCanisters.size(); i++){
			bulletMatrix = translate(modelview, vec3(activeCanisters.at(i).pos.x, -1.5f, activeCanisters.at(i).pos.z));
			activeCanisters.at(i).Draw(projection, bulletMatrix, size, 0);
		}
	}
	

	if (this->GLReturnedError("Team::Draw - on exit"))
		return;
}

void Team::ifHitByBullet(Team * otherTeam, Team * otherTeam2, Team * otherTeam3){

	bool hit = false;
	for(int i=0; i<NUM_SOLDIERS; i++){
		for(unsigned int j=0; j<activeBullets.size(); j++){
			hit = false;
			if(activeBullets.at(j).currPos.x > 500.f || activeBullets.at(j).currPos.x < -500.f
				|| activeBullets.at(j).currPos.z > 500.f || activeBullets.at(j).currPos.z < -500.f
				|| ranIntoBuilding(vec3(activeBullets.at(j).currPos.z, 3, -activeBullets.at(j).currPos.x), 0.5)){
					(activeBullets.at(j)).doneDrawing = true;
			}
			else{
				if(!otherTeam->soldiers[i].dead){
						if(dist(otherTeam->soldiers[i].pos.x, otherTeam->soldiers[i].pos.y, otherTeam->soldiers[i].pos.z, 
							(activeBullets.at(j)).currPos.x, (activeBullets.at(j)).currPos.y, (activeBullets.at(j)).currPos.z) < 1){

								if(otherTeam->userTeam && i == 0){otherTeam->soldiers[i].userDamageFlag = true;}
								otherTeam->soldiers[i].health -= bulletDamage;
								if(otherTeam->soldiers[i].health <= 0){otherTeam->soldiers[i].health = 0;otherTeam->soldiers[i].dead = true;
								tCanister.pos = otherTeam->soldiers[i].pos;
								float randCanister = (float) rand() / (RAND_MAX);
								if(randCanister < 0.33){tCanister.type = 1;}
								else if(randCanister < 0.66){tCanister.type = 2;}
								else{tCanister.type = 3;}								
								activeCanisters.push_back(tCanister);
								otherTeam->numRemaining--;
								soldiers[activeBullets.at(j).userNo].kills++;}
								
								//Delete the bullet because it hit someone
								(activeBullets.at(j)).doneDrawing = true;hit = true;
						}
				}

				//Check for second team
				if(!hit && !otherTeam2->soldiers[i].dead){
						if(dist(otherTeam2->soldiers[i].pos.x, otherTeam2->soldiers[i].pos.y, otherTeam2->soldiers[i].pos.z, 
							(activeBullets.at(j)).currPos.x, (activeBullets.at(j)).currPos.y, (activeBullets.at(j)).currPos.z) < 1){

								if(otherTeam2->userTeam && i == 0){otherTeam2->soldiers[i].userDamageFlag = true;}
								otherTeam2->soldiers[i].health -= bulletDamage;
								if(otherTeam2->soldiers[i].health <= 0){otherTeam2->soldiers[i].health = 0;otherTeam2->soldiers[i].dead = true;
								tCanister.pos = otherTeam2->soldiers[i].pos;
								float randCanister = (float) rand() / (RAND_MAX);
								if(randCanister < 0.33){tCanister.type = 1;}
								else if(randCanister < 0.66){tCanister.type = 2;}
								else{tCanister.type = 3;}								
								activeCanisters.push_back(tCanister);
								otherTeam2->numRemaining--;
								soldiers[activeBullets.at(j).userNo].kills++;}
								
								//Delete the bullet because it hit someone
								(activeBullets.at(j)).doneDrawing = true;
						
								hit = true;
						}
				}

				//Check for third team
				if(!hit && !otherTeam3->soldiers[i].dead){
					if(dist(otherTeam3->soldiers[i].pos.x, otherTeam3->soldiers[i].pos.y, otherTeam3->soldiers[i].pos.z, 
						(activeBullets.at(j)).currPos.x, (activeBullets.at(j)).currPos.y, (activeBullets.at(j)).currPos.z) < 1){

							if(otherTeam3->userTeam && i == 0){otherTeam3->soldiers[i].userDamageFlag = true;}
							otherTeam3->soldiers[i].health -= bulletDamage;
							if(otherTeam3->soldiers[i].health <= 0){otherTeam3->soldiers[i].health = 0;otherTeam3->soldiers[i].dead = true;
							tCanister.pos = otherTeam3->soldiers[i].pos;
							float randCanister = (float) rand() / (RAND_MAX);
							if(randCanister < 0.33){tCanister.type = 1;}
							else if(randCanister < 0.66){tCanister.type = 2;}
							else{tCanister.type = 3;}								
							activeCanisters.push_back(tCanister);
							otherTeam3->numRemaining--;
							soldiers[activeBullets.at(j).userNo].kills++;}
								
							//Delete the bullet because it hit someone
							(activeBullets.at(j)).doneDrawing = true;
						
							hit = true;
					}
				}
			}
		}
		for(unsigned int j=0; j<activeGrenades.size(); j++){
			hit = false;
			if((activeGrenades.at(j).currPos.x > 500.f || activeGrenades.at(j).currPos.x < -500.f
				|| activeGrenades.at(j).currPos.z > 500.f || activeGrenades.at(j).currPos.z < -500.f
				|| ranIntoBuilding(vec3(activeGrenades.at(j).currPos.z, 0, -activeGrenades.at(j).currPos.x), 0.6)) 
				&& !activeGrenades.at(j).explode){
					activeGrenades.at(j).explode = true;
			}
			else{
				if(activeGrenades.at(j).explode){
					if(!otherTeam->soldiers[i].dead){
							if(dist(otherTeam->soldiers[i].pos.x, otherTeam->soldiers[i].pos.y, otherTeam->soldiers[i].pos.z, 
								(activeGrenades.at(j)).currPos.x, (activeGrenades.at(j)).currPos.y, (activeGrenades.at(j)).currPos.z) < 
								activeGrenades.at(j).explodeRadius*activeGrenades.at(j).grenadeRadius){

					
									if(otherTeam->userTeam && i == 0){otherTeam->soldiers[i].userDamageFlag = true;}
									otherTeam->soldiers[i].health -= grenadeDamage;
									if(otherTeam->soldiers[i].health <= 0){otherTeam->soldiers[i].health = 0;otherTeam->soldiers[i].dead = true;
									tCanister.pos = otherTeam->soldiers[i].pos;
									float randCanister = (float) rand() / (RAND_MAX);
									if(randCanister < 0.33){tCanister.type = 1;}
									else if(randCanister < 0.66){tCanister.type = 2;}
									else{tCanister.type = 3;}								
									activeCanisters.push_back(tCanister);
									otherTeam->numRemaining--;
									soldiers[activeGrenades.at(j).userIndex].kills++;
									}
						
									hit = true;
							}
					}

					//Check for second team
					if(!hit && !otherTeam2->soldiers[i].dead){
							if(dist(otherTeam2->soldiers[i].pos.x, otherTeam2->soldiers[i].pos.y, otherTeam2->soldiers[i].pos.z, 
								(activeGrenades.at(j)).currPos.x, (activeGrenades.at(j)).currPos.y, (activeGrenades.at(j)).currPos.z) < 
								activeGrenades.at(j).explodeRadius*activeGrenades.at(j).grenadeRadius){

									if(otherTeam2->userTeam && i == 0){otherTeam2->soldiers[i].userDamageFlag = true;}
									otherTeam2->soldiers[i].health -= grenadeDamage;
									if(otherTeam2->soldiers[i].health <= 0){otherTeam2->soldiers[i].health = 0;otherTeam2->soldiers[i].dead = true;
									tCanister.pos = otherTeam2->soldiers[i].pos;
									float randCanister = (float) rand() / (RAND_MAX);
									if(randCanister < 0.33){tCanister.type = 1;}
									else if(randCanister < 0.66){tCanister.type = 2;}
									else{tCanister.type = 3;}								
									activeCanisters.push_back(tCanister);
									otherTeam2->numRemaining--;
									soldiers[activeGrenades.at(j).userIndex].kills++;}
						
									hit = true;
							}
					}

					//Check for third team
					if(!hit && !otherTeam3->soldiers[i].dead){
						if(dist(otherTeam3->soldiers[i].pos.x, otherTeam3->soldiers[i].pos.y, otherTeam3->soldiers[i].pos.z, 
							(activeGrenades.at(j)).currPos.x, (activeGrenades.at(j)).currPos.y, (activeGrenades.at(j)).currPos.z) < 
							activeGrenades.at(j).explodeRadius*activeGrenades.at(j).grenadeRadius){

								if(otherTeam3->userTeam && i == 0){otherTeam3->soldiers[i].userDamageFlag = true;}
								otherTeam3->soldiers[i].health -= grenadeDamage;
								if(otherTeam3->soldiers[i].health <= 0){otherTeam3->soldiers[i].health = 0;otherTeam3->soldiers[i].dead = true;
								tCanister.pos = otherTeam3->soldiers[i].pos;
								float randCanister = (float) rand() / (RAND_MAX);
								if(randCanister < 0.33){tCanister.type = 1;}
								else if(randCanister < 0.66){tCanister.type = 2;}
								else{tCanister.type = 3;}								
								activeCanisters.push_back(tCanister);
								otherTeam3->numRemaining--;
								soldiers[activeGrenades.at(j).userIndex].kills++;}
						
								hit = true;
						}
					}
				}
				else{ //If grenade directly hits someone
					if(!otherTeam->soldiers[i].dead){
							if(dist(otherTeam->soldiers[i].pos.x, otherTeam->soldiers[i].pos.y, otherTeam->soldiers[i].pos.z, 
								(activeGrenades.at(j)).currPos.x, (activeGrenades.at(j)).currPos.y, (activeGrenades.at(j)).currPos.z) < 2){

									if(otherTeam->userTeam && i == 0){otherTeam->soldiers[i].userDamageFlag = true;}
									otherTeam->soldiers[i].health -= grenadeDamage;
									if(otherTeam->soldiers[i].health <= 0){otherTeam->soldiers[i].health = 0;otherTeam->soldiers[i].dead = true;
									tCanister.pos = otherTeam->soldiers[i].pos;
									float randCanister = (float) rand() / (RAND_MAX);
									if(randCanister < 0.33){tCanister.type = 1;}
									else if(randCanister < 0.66){tCanister.type = 2;}
									else{tCanister.type = 3;}								
									activeCanisters.push_back(tCanister);
									otherTeam->numRemaining--;}
								
									//Delete the bullet because it hit someone
									(activeGrenades.at(j)).explode = true;
						
									hit = true;
							}
					}

					//Check for second team
					if(!hit && !otherTeam2->soldiers[i].dead){
							if(dist(otherTeam2->soldiers[i].pos.x, otherTeam2->soldiers[i].pos.y, otherTeam2->soldiers[i].pos.z, 
								(activeGrenades.at(j)).currPos.x, (activeGrenades.at(j)).currPos.y, (activeGrenades.at(j)).currPos.z) < 2){

									if(otherTeam2->userTeam && i == 0){otherTeam2->soldiers[i].userDamageFlag = true;}
									otherTeam2->soldiers[i].health -= grenadeDamage;
									if(otherTeam2->soldiers[i].health <= 0){otherTeam2->soldiers[i].health = 0;otherTeam2->soldiers[i].dead = true;
									tCanister.pos = otherTeam2->soldiers[i].pos;
									float randCanister = (float) rand() / (RAND_MAX);
									if(randCanister < 0.33){tCanister.type = 1;}
									else if(randCanister < 0.66){tCanister.type = 2;}
									else{tCanister.type = 3;}								
									activeCanisters.push_back(tCanister);
									otherTeam2->numRemaining--;}
								
									(activeGrenades.at(j)).explode = true;
						
									hit = true;
							}
					}

					//Check for third team
					if(!hit && !otherTeam3->soldiers[i].dead){
						if(dist(otherTeam3->soldiers[i].pos.x, otherTeam3->soldiers[i].pos.y, otherTeam3->soldiers[i].pos.z, 
							(activeGrenades.at(j)).currPos.x, (activeGrenades.at(j)).currPos.y, (activeGrenades.at(j)).currPos.z) < 2){

								if(otherTeam3->userTeam && i == 0){otherTeam3->soldiers[i].userDamageFlag = true;}
								otherTeam3->soldiers[i].health -= grenadeDamage;
								if(otherTeam3->soldiers[i].health <= 0){otherTeam3->soldiers[i].health = 0;otherTeam3->soldiers[i].dead = true;
								tCanister.pos = otherTeam3->soldiers[i].pos;
								float randCanister = (float) rand() / (RAND_MAX);
								if(randCanister < 0.33){tCanister.type = 1;}
								else if(randCanister < 0.66){tCanister.type = 2;}
								else{tCanister.type = 3;}								
								activeCanisters.push_back(tCanister);
								otherTeam3->numRemaining--;}
								
								//Delete the bullet because it hit someone
								(activeGrenades.at(j)).explode = true;
						
								hit = true;
						}
					}
				}
			}
		}
		for(unsigned int j=0; j<activeCanisters.size(); j++){
				hit = false;
					if(!soldiers[i].dead){
						if(dist(soldiers[i].pos.x, 0, soldiers[i].pos.z, 
								(activeCanisters.at(j)).pos.x, 0, (activeCanisters.at(j)).pos.z) < 2+tCanister.canisterRadius){

									switch((activeCanisters.at(j)).type){
									case 1:
									default:
										soldiers[i].health += healthCanister;
										if(soldiers[i].health > soldiers[i].maxHP){soldiers[i].health = soldiers[i].maxHP;}
										break;
									case 2:
										soldiers[i].ammo += ammoCanister;
										if(soldiers[i].ammo > soldiers[i].maxAmmo){soldiers[i].ammo = soldiers[i].maxAmmo;}
										break;
									case 3:
										soldiers[i].grenades += grenadeCanister;
										if(soldiers[i].grenades > soldiers[i].maxGrenades){soldiers[i].grenades = soldiers[i].maxGrenades;}
										break;
									}

									if(userTeam && i == 0){soldiers[i].userCanisterFlag = true;
									soldiers[i].userCanisterType = activeCanisters.at(j).type;
									}
										
									//Delete the bullet because it hit someone
									(activeCanisters.at(j)).doneDrawing = true;hit = true;
							}
					}
					if(!hit && !otherTeam->soldiers[i].dead){
							if(dist(otherTeam->soldiers[i].pos.x, 0, otherTeam->soldiers[i].pos.z, 
								(activeCanisters.at(j)).pos.x, 0, (activeCanisters.at(j)).pos.z) < 2+tCanister.canisterRadius){

									switch((activeCanisters.at(j)).type){
									case 1:
									default:
										otherTeam->soldiers[i].health += healthCanister;
										if(otherTeam->soldiers[i].health > soldiers[i].maxHP){otherTeam->soldiers[i].health = soldiers[i].maxHP;}
										break;
									case 2:
										otherTeam->soldiers[i].ammo += ammoCanister;
										if(otherTeam->soldiers[i].ammo > soldiers[i].maxAmmo){otherTeam->soldiers[i].ammo = soldiers[i].maxAmmo;}
										break;
									case 3:
										otherTeam->soldiers[i].grenades += grenadeCanister;
										if(otherTeam->soldiers[i].grenades > soldiers[i].maxGrenades){otherTeam->soldiers[i].grenades = soldiers[i].maxGrenades;}
										break;
									}

									if(otherTeam->userTeam && i == 0){otherTeam->soldiers[i].userCanisterFlag = true;
									otherTeam->soldiers[i].userCanisterType = activeCanisters.at(j).type;
									}
										
									//Delete the bullet because it hit someone
									(activeCanisters.at(j)).doneDrawing = true;hit = true;
							}
					}

					//Check for second team
					if(!hit && !otherTeam2->soldiers[i].dead){
							if(dist(otherTeam2->soldiers[i].pos.x, 0, otherTeam2->soldiers[i].pos.z, 
								(activeCanisters.at(j)).pos.x, 0, (activeCanisters.at(j)).pos.z) < 2+tCanister.canisterRadius){

									switch((activeCanisters.at(j)).type){
									case 1:
									default:
										otherTeam2->soldiers[i].health += healthCanister;
										if(otherTeam2->soldiers[i].health > soldiers[i].maxHP){otherTeam2->soldiers[i].health = soldiers[i].maxHP;}
										break;
									case 2:
										otherTeam2->soldiers[i].ammo += ammoCanister;
										if(otherTeam2->soldiers[i].ammo > soldiers[i].maxAmmo){otherTeam2->soldiers[i].ammo = soldiers[i].maxAmmo;}
										break;
									case 3:
										otherTeam2->soldiers[i].grenades += grenadeCanister;
										if(otherTeam2->soldiers[i].grenades > soldiers[i].maxGrenades){otherTeam2->soldiers[i].grenades = soldiers[i].maxGrenades;}
										break;
									}

									if(otherTeam2->userTeam && i == 0){otherTeam2->soldiers[i].userCanisterFlag = true;
									otherTeam2->soldiers[i].userCanisterType = activeCanisters.at(j).type;
									}
										
									//Delete the bullet because it hit someone
									(activeCanisters.at(j)).doneDrawing = true;hit = true;
							}
					}

					//Check for third team
					if(!hit && !otherTeam3->soldiers[i].dead){
						if(dist(otherTeam3->soldiers[i].pos.x, 0, otherTeam3->soldiers[i].pos.z, 
							(activeCanisters.at(j)).pos.x, 0, (activeCanisters.at(j)).pos.z) < 2+tCanister.canisterRadius){

								switch((activeCanisters.at(j)).type){
								case 1:
								default:
									otherTeam3->soldiers[i].health += healthCanister;
									if(otherTeam3->soldiers[i].health > soldiers[i].maxHP){otherTeam3->soldiers[i].health = soldiers[i].maxHP;}
									break;
								case 2:
									otherTeam3->soldiers[i].ammo += ammoCanister;
									if(otherTeam3->soldiers[i].ammo > soldiers[i].maxAmmo){otherTeam3->soldiers[i].ammo = soldiers[i].maxAmmo;}
									break;
								case 3:
									otherTeam3->soldiers[i].grenades += grenadeCanister;
									if(otherTeam3->soldiers[i].grenades > soldiers[i].maxGrenades){otherTeam3->soldiers[i].grenades = soldiers[i].maxGrenades;}
									break;
								}


								if(otherTeam3->userTeam && i == 0){otherTeam3->soldiers[i].userCanisterFlag = true;
									otherTeam3->soldiers[i].userCanisterType = activeCanisters.at(j).type;
									}
										
								//Delete the bullet because it hit someone
								(activeCanisters.at(j)).doneDrawing = true;hit = true;
						}
					}
			}
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////BASIC FUNCTIONS///////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


bool Team::buildingInWay(vec3 user, vec3 targetSoldier, RectangularObstacle closestBuilding){
	float dimX = closestBuilding.dimensions.x/2+0.5;
	float dimZ = closestBuilding.dimensions.z/2+0.5;
	if(linesIntersect(vec2(user.z, -user.x), vec2(targetSoldier.z, -targetSoldier.x),
		vec2(closestBuilding.pos.x+dimX, closestBuilding.pos.z+dimZ), 
		vec2(closestBuilding.pos.x-dimX, closestBuilding.pos.z-dimZ))
		||
		linesIntersect(vec2(user.z, -user.x), vec2(targetSoldier.z, -targetSoldier.x),
		vec2(closestBuilding.pos.x-dimX, closestBuilding.pos.z+dimZ), 
		vec2(closestBuilding.pos.x+dimX, closestBuilding.pos.z-dimZ))){
			return true;
	}
	return false;
}

bool Team::buildingInFront(Soldier user, RectangularObstacle closestBuilding){
	if(linesIntersect(vec2(user.pos.z, -user.pos.x), vec2(user.pos.z+100*sin(-user.hRot*0.0174), -(user.pos.x+100*cos(-user.hRot*0.0174))),
		vec2(closestBuilding.pos.x+closestBuilding.dimensions.x/2, closestBuilding.pos.z+closestBuilding.dimensions.z/2), 
		vec2(closestBuilding.pos.x-closestBuilding.dimensions.x/2, closestBuilding.pos.z-closestBuilding.dimensions.z/2))
		||
		linesIntersect(vec2(user.pos.z, -user.pos.x), vec2(user.pos.z+100*sin(-user.hRot*0.0174), -(user.pos.x+100*cos(-user.hRot*0.0174))),
		vec2(closestBuilding.pos.x-closestBuilding.dimensions.x/2, closestBuilding.pos.z+closestBuilding.dimensions.z/2), 
		vec2(closestBuilding.pos.x+closestBuilding.dimensions.x/2, closestBuilding.pos.z-closestBuilding.dimensions.z/2))){
			return true;
	}
	return false;
}

bool Team::ranIntoBuilding(vec3 pos, double buffer){
	for(int i=0; i<buildings.size(); i++){
		if(pos.x > buildings.at(i).pos.x - buildings.at(i).dimensions.x/2 - buffer
			&& pos.x < buildings.at(i).pos.x + buildings.at(i).dimensions.x/2 + buffer
			&& pos.z > buildings.at(i).pos.z - buildings.at(i).dimensions.z/2 - buffer
			&& pos.z < buildings.at(i).pos.z + buildings.at(i).dimensions.z/2 + buffer
			&& pos.y <= buildings.at(i).dimensions.y){
			return true;
		}
	}
	return false;
}

float Team::distFromBuilding(vec3 pos, RectangularObstacle building, double buffer){
	float a,b,c,d,minDist;
	a = abs(pos.z - building.pos.x + building.dimensions.x/2 + buffer);
	b = abs(pos.z - building.pos.x - building.dimensions.x/2 - buffer);
	c = abs(-pos.x - building.pos.z + building.dimensions.z/2 + buffer);
	d = abs(-pos.x - building.pos.z - building.dimensions.z/2 - buffer);
	minDist = a;
	if(b < minDist){minDist = b;}
	if(c < minDist){minDist = c;}
	if(d < minDist){minDist = d;}

	return minDist;
}

bool Team::treeInWay(vec3 user, vec3 targetSoldier, Tree closestTree){
	float dimR = closestTree.radius+0.5;
	if(linesIntersect(vec2(user.z, -user.x), vec2(targetSoldier.z, -targetSoldier.x),
		vec2(closestTree.pos.x+dimR, closestTree.pos.z+dimR), 
		vec2(closestTree.pos.x-dimR, closestTree.pos.z-dimR))
		||
		linesIntersect(vec2(user.z, -user.x), vec2(targetSoldier.z, -targetSoldier.x),
		vec2(closestTree.pos.x-dimR, closestTree.pos.z+dimR), 
		vec2(closestTree.pos.x+dimR, closestTree.pos.z-dimR))){
			return true;
	}
	return false;
}

bool Team::treeInFront(Soldier user, Tree closestTree){
	float fwdX = user.pos.z+100*sin(-user.hRot*0.0174);
	float fwdZ = -(user.pos.x+100*cos(-user.hRot*0.0174));
	if(linesIntersect(vec2(user.pos.z, -user.pos.x), vec2(fwdX, fwdZ),
		vec2(closestTree.pos.x+closestTree.radius, closestTree.pos.z+closestTree.radius), 
		vec2(closestTree.pos.x-closestTree.radius, closestTree.pos.z-closestTree.radius))
		||
		linesIntersect(vec2(user.pos.z, -user.pos.x), vec2(fwdX, fwdZ),
		vec2(closestTree.pos.x-closestTree.radius, closestTree.pos.z+closestTree.radius), 
		vec2(closestTree.pos.x+closestTree.radius, closestTree.pos.z-closestTree.radius))){
			return true;
	}
	return false;
}

bool Team::ranIntoTree(vec3 pos, double buffer){
	for(int i=0; i<trees.size(); i++){
		if(dist(trees.at(i).pos.x, trees.at(i).pos.y, trees.at(i).pos.z,
			pos.x, pos.y, pos.z) < trees.at(i).radius + buffer){
			return true;
		}
	}
	return false;
}

float Team::distFromTree(vec3 pos, Tree tree, double buffer){
	return dist(pos.x, pos.y, pos.z, 
		tree.pos.x, tree.pos.y, tree.pos.z)-buffer;
}

bool CCW(vec2 C, vec2 W1, vec2 W2){
	vec2 ab = W1-C;
	vec2 ac = W2-C;
	double y = (ab.x * ac.y) - (ab.y * ac.x);

    // dot product
    double x = (ab.x * ab.y) + (ac.x * ac.y);

	return atan2(y, x) > 0;
}

bool Team::linesIntersect(vec2 a1, vec2 a2, vec2 b1, vec2 b2){
	return (CCW(a1, b1, b2) != CCW(a2, b1, b2)) && (CCW(b1, a1, a2) != CCW(b2, a1, a2));
}

void Team::distFromUser(vec3 userPos){
	for(int i=0; i<NUM_SOLDIERS; i++){
		soldiers[i].distFromUser = dist(soldiers[i].pos.x, soldiers[i].pos.y, soldiers[i].pos.z,
			userPos.x, userPos.y, userPos.z);
	}
	for(int i=0; i<activeBullets.size(); i++){
		activeBullets.at(i).distFromUser = dist(activeBullets.at(i).currPos.x, activeBullets.at(i).currPos.y, activeBullets.at(i).currPos.z,
			userPos.x, userPos.y, userPos.z);
	}
}


float Team::dist(float x1, float y1, float z1, float x2, float y2, float z2){
	float x=x2-x1;float y=y2-y1;float z=z2-z1;
	return sqrt(x*x + y*y + z*z);
}

//Delete everything.
void Team::TakeDown()
{
	this->vertices.clear();
	this->shader.TakeDown();
	super::TakeDown();	
}

void Team::hpBounds(){
	for(int i=0; i<NUM_SOLDIERS; i++){
		if(soldiers[i].health > 100){soldiers[i].health = 100;}
		else if(soldiers[i].health < 0){soldiers[i].health = 0;soldiers[i].dead = true;}
	}
}

void Team::firedBullet(int index){
	int bulletDistance = tBullet.distance;
	if(this->soldiers[index].ammo > 0){
		if(userTeam && index == 0){
			tBullet.rotY = -this->soldiers[index].hRot;
		}
		else{
			tBullet.rotY = this->soldiers[index].hRot;
		}
		tBullet.startPos = vec3(1.5*cos(tBullet.rotY*3.14/180)+this->soldiers[index].pos.x, this->soldiers[index].pos.y,
			1.5*sin(-tBullet.rotY*3.14/180)+this->soldiers[index].pos.z);
		tBullet.currPos = vec3(1.5*cos(tBullet.rotY*3.14/180)+this->soldiers[index].pos.x, this->soldiers[index].pos.y,
			1.5*sin(-tBullet.rotY*3.14/180)+this->soldiers[index].pos.z);

		tBullet.endPos = vec3(bulletDistance*cos(tBullet.rotY*3.14/180)+tBullet.startPos.x, this->soldiers[index].pos.y,
			bulletDistance*sin(-tBullet.rotY*3.14/180)+tBullet.startPos.z);

		tBullet.teamNo = teamNo;tBullet.userNo = index;

		activeBullets.push_back(tBullet);

		this->soldiers[index].ammo--;

	}
}

void Team::threwGrenade(int index){
	int grenadeDistance = tGrenade.distance;
	if(this->soldiers[index].grenades > 0){
		
		tGrenade.startPos = vec3(this->soldiers[index].pos.x, 0.f, this->soldiers[index].pos.z);
		tGrenade.currPos = vec3(this->soldiers[index].pos.x, 0.f, this->soldiers[index].pos.z);

		tGrenade.endPos = vec3(
			grenadeDistance*cos((userTeam && index==0 ? -soldiers[index].hRot : soldiers[index].hRot)*3.14/180)+tGrenade.startPos.x,
			0.f,
			grenadeDistance*sin(-(userTeam && index==0 ? -soldiers[index].hRot : soldiers[index].hRot)*3.14/180)+tGrenade.startPos.z
			);

		tGrenade.userIndex = index;

		activeGrenades.push_back(tGrenade);

		this->soldiers[index].grenades--;

	}
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////GRAVEYARD/////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////