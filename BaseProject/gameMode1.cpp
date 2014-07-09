/*
Name: Clayton Suplinski
ID: 906 580 2630
CS 559 Project 3

Creates the square arena
*/

#include <iostream>
#include "gameMode1.h"

using namespace std;
using namespace glm;

//Create the GameMode1 object
GameMode1::GameMode1() : Object()
{
}

GameMode1::~GameMode1(){
	this->TakeDown();
}

/////////////////////////////////////CAMERA CONTROLS//////////////////////////////////////////
//Moves the camera with user
mat4 GameMode1::render(mat4 Model){		
	Model = glm::rotate(Model, (GLfloat) RotatedX, glm::vec3(1,0,0));
	Model = glm::rotate(Model, (GLfloat) RotatedY, glm::vec3(0,1,0));
	Model = glm::translate(Model, glm::vec3(transX,0,0));    
	Model = glm::translate(Model, glm::vec3(0,0,transZ));    
	Model = glm::translate(Model, glm::vec3(0,-transY,0));	
	glLoadMatrixf(glm::value_ptr(Model));
    return Model;
}

//Doesn't move camera with user
mat4 GameMode1::endRender(mat4 Model){	
	Model = glm::translate(Model, glm::vec3(0,transY,0));	
	Model = glm::translate(Model, glm::vec3(0,0,-transZ));
	Model = glm::translate(Model, glm::vec3(-transX,0,0));
	Model = glm::rotate(Model, (GLfloat) -RotatedY, glm::vec3(0,1,0));
	Model = glm::rotate(Model, (GLfloat) -RotatedX, glm::vec3(1,0,0));			
	glLoadMatrixf(glm::value_ptr(Model));
    return Model;
}

//Initialize all the elements of the GameMode1
bool GameMode1::Initialize()
{
	if (this->GLReturnedError("GameMode1::Initialize - on entry"))
		return false;

	if (!super::Initialize())
		return false;

	tod = ivec2(0, 2);
	movingWRTSnow = 0;

	transX = 0;transY = 0;transZ = 0;
	RotatedX = 0;RotatedY = 0;
	stadiumSelect = 0;

	this->stadium = new SquareStadium();
	//if (!stadium->Initialize(0)){return false;}

	userTeam.tSoldier = tSoldier;
	greenTeam.tSoldier = tSoldier;
	blueTeam.tSoldier = tSoldier;
	redTeam.tSoldier = tSoldier;

	this->userTeam.userTeam = true;
	this->userTeam.Initialize(1);
	this->greenTeam.Initialize(2);
	this->blueTeam.Initialize(3);
	this->redTeam.Initialize(4);

	disc.Initialize(8, 1.0f, "phong3.vert", "phong3.frag");
	healthBar.Initialize(2, 1.0f, 1.f, 1.f, "phong3.vert", "phong3.frag");
	numberBackground.Initialize(1, 1, "./textures/mask.png", "basic_texture_shader.vert", "basic_texture_shader.frag");
	userDamaged.Initialize(1, 1, "./textures/userDamage.png", "basic_texture_shader.vert", "basic_texture_shader.frag");
	userHealed.Initialize(1, 1, "./textures/healingEffect.png", "basic_texture_shader.vert", "basic_texture_shader.frag");
	reticule.Initialize(1, 1, "./textures/reticule.png", "basic_texture_shader.vert", "basic_texture_shader.frag");

	backgroundSquare.Initialize(1, 1, "./icons/backgroundSquare.png", "basic_texture_shader.vert", "basic_texture_shader.frag");
	healthIcon.Initialize(1, 1, "./icons/healthIcon.png", "basic_texture_shader.vert", "basic_texture_shader.frag");
	killsIcon.Initialize(1, 1, "./icons/killsIcon.png", "basic_texture_shader.vert", "basic_texture_shader.frag");
	ammoIcon.Initialize(1, 1, "./icons/ammoIcon.png", "basic_texture_shader.vert", "basic_texture_shader.frag");
	grenadeIcon.Initialize(1, 1, "./icons/grenadeIcon.png", "basic_texture_shader.vert", "basic_texture_shader.frag");

	soldierToFollowIndex = 0;

	if (this->GLReturnedError("GameMode1::Initialize - on exit"))
		return false;

	return true;
}

//Delete the GameMode1
void GameMode1::TakeDown()
{
	disc.TakeDown();healthBar.TakeDown();numberBackground.TakeDown();userDamaged.TakeDown();userHealed.TakeDown();
	backgroundSquare.TakeDown();healthIcon.TakeDown();killsIcon.TakeDown();ammoIcon.TakeDown();grenadeIcon.TakeDown();
	reticule.TakeDown();
	super::TakeDown();
}

//Draw and position the elements of the GameMode1
void GameMode1::Draw(const mat4 & projection, mat4 modelview, const ivec2 & size, const float time)
{
	if (this->GLReturnedError("GameMode1::Draw - on entry"))
		return;

	glEnable(GL_DEPTH_TEST);


	if (this->GLReturnedError("GameMode1::Draw - on exit"))
		return;
}

void GameMode1::DrawTeams(const mat4 & projection, mat4 modelview, const ivec2 & size, const float time){
	//Draw cpu players (for both teams)
	mat4 scaler = rotate(modelview, 90.0f, vec3(0,1,0));
	userTeam.drawUser = false;
	userTeam.Draw(projection, scaler, size, 0);
	redTeam.drawBullet = false;
	redTeam.Draw(projection, scaler, size, 0);
	greenTeam.drawBullet = false;
	greenTeam.Draw(projection, scaler, size, 0);
	blueTeam.drawBullet = false;
	blueTeam.Draw(projection, scaler, size, 0);

	DrawStadium(projection, modelview, size, current_timeDisplay);
	modelview = translate(modelview, vec3(0,-1,0));

	//Draw bullets
	scaler = translate(modelview, vec3(0.0f, 0.5f, 0.0f));
	scaler = rotate(scaler, 90.0f, vec3(0,1,0));

	for(int i=0; i<userTeam.NUM_SOLDIERS; i++){
		userTeam.soldiers[i].person.deathEffect->userPos = vec3(transX, transY, transZ);
		greenTeam.soldiers[i].person.deathEffect->userPos = vec3(transX, transY, transZ);
		redTeam.soldiers[i].person.deathEffect->userPos = vec3(transX, transY, transZ);
		blueTeam.soldiers[i].person.deathEffect->userPos = vec3(transX, transY, transZ);
	}
		
	userTeam.drawUser = false;userTeam.drawBullet = true;
	userTeam.Draw(projection, modelview, size, 0);
	redTeam.drawBullet = true;
	redTeam.Draw(projection, modelview, size, 0);	
	greenTeam.drawBullet = true;
	greenTeam.Draw(projection, modelview, size, 0);	
	blueTeam.drawBullet = true;
	blueTeam.Draw(projection, modelview, size, 0);

	userTeam.ifHitByBullet(&redTeam, &greenTeam, &blueTeam);
	redTeam.ifHitByBullet(&userTeam, &greenTeam, &blueTeam);
	greenTeam.ifHitByBullet(&redTeam, &userTeam, &blueTeam);
	blueTeam.ifHitByBullet(&redTeam, &greenTeam, &userTeam);

	switch(stadiumSelect){
	case 1:ai.MoveComputers(&userTeam, &redTeam, &greenTeam, &blueTeam, &(stadium->buildings), &(stadium->rectangularObstacles));break;
	case 2:ai.MoveComputers(&userTeam, &redTeam, &greenTeam, &blueTeam, &(forest->buildings), &(forest->rectangularObstacles));break;
	case 3:ai.MoveComputers(&userTeam, &redTeam, &greenTeam, &blueTeam, &(stadium->buildings), &(stadium->rectangularObstacles));break;
	case 4:ai.MoveComputers(&userTeam, &redTeam, &greenTeam, &blueTeam, &(stadium->buildings), &(stadium->rectangularObstacles));break;
	case 5:ai.MoveComputers(&userTeam, &redTeam, &greenTeam, &blueTeam, &(stadium->buildings), &(stadium->rectangularObstacles));break;
	}
}

void GameMode1::DrawUser(const mat4 & projection, mat4 modelview, const ivec2 & size, const float time){
	mat4 scaler;
	userTeam.soldiers[0].pos.x=transZ;userTeam.soldiers[0].pos.y=transY;userTeam.soldiers[0].pos.z=-transX;
	userTeam.distFromUser(userTeam.soldiers[0].pos);redTeam.distFromUser(userTeam.soldiers[0].pos);
	blueTeam.distFromUser(userTeam.soldiers[0].pos);greenTeam.distFromUser(userTeam.soldiers[0].pos);
	userTeam.soldiers[0].hRot = (float)(RotatedY);
			
	//Draw the user
		
	scaler = rotate(modelview, (float)(RotatedX), vec3(1,0,0));
	scaler = rotate(scaler, 90.0f, vec3(0,1,0));
	userTeam.drawUser = true;userTeam.drawBullet = false;
	userTeam.Draw(projection, scaler, size, time);
}

void GameMode1::DrawPrecipitation(const mat4 & projection, mat4 modelview, const ivec2 & size, const float time){
	modelview = endRender(modelview);

	modelview = rotate(modelview, (GLfloat) RotatedX, vec3(1,0,0));
	modelview = rotate(modelview, (GLfloat) RotatedY, vec3(0,1,0));
		
	precip.RotatedY = (float)(RotatedY);
	precip.movingWRTSnow = movingWRTSnow;
	precip.weatherType = weatherType;

	precip.Draw(projection, modelview, tod, 0);	
			
	modelview = rotate(modelview, (GLfloat) -RotatedY, vec3(0,1,0));
	modelview = rotate(modelview, (GLfloat) -RotatedX, vec3(1,0,0));

	modelview = render(modelview);
}

//ADD_STADIUM//
void GameMode1::DrawStadium(const mat4 & projection, mat4 modelview, const ivec2 & size, const float time){
	modelview = translate(modelview, vec3(0.f,-1,0.f));
	switch(stadiumSelect){
	case 1:
		stadium->transX = transX;stadium->transY = transY;stadium->transZ = transZ;
		stadium->Draw(projection, modelview, size, time);
		break;
	case 2:
		forest->transX = transX;forest->transY = transY;forest->transZ = transZ;
		forest->Draw(projection, modelview, size, time);
		break;
	case 3:
		desert->transX = transX;desert->transY = transY;desert->transZ = transZ;
		desert->Draw(projection, modelview, size, time);
		break;
	case 4:
		volcano->transX = transX;volcano->transY = transY;volcano->transZ = transZ;
		volcano->Draw(projection, modelview, size, time);
		break;
	case 5:
		cave->transX = transX;cave->transY = transY;cave->transZ = transZ;
		cave->Draw(projection, modelview, size, time);
		break;
	default:
		break;
	}
}

void GameMode1::DrawOrthographic(const mat4 & projection, mat4 modelview, const ivec2 & size, bool firstPerson, const float time){

	modelview = endRender(modelview);

	//Set up orthographic projection for radar
	mat4 Projection2 = ortho( -10.0f, 10.0f, -10.0f, 00.0f,1.0f, 10.0f);
	mat4 View       = lookAt(
		vec3(0,0,5), // Camera is at (0,0,5), in World Space
		vec3(0,0,0), // and looks at the origin
		vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
	);  
			
	mat4 another = View;
	mat4 healthBarMatrix = View;

	mat4 nB = another;

	//nB = rotate(nB, tmpRot1, vec3(0,1,0));
	nB = translate(nB, vec3(-10,0.05,-0.6));
	nB = scale(nB, vec3(20.f,2.5,1));
	//usr.Draw(Projection2, nB, tod, 0);

	nB = rotate(nB, 90.f, vec3(0,0,1));
	nB = rotate(nB, 90.f, vec3(0,1,0));
	nB = rotate(nB, -90.f, vec3(0,0,1));
		
	numberBackground.Draw(Projection2, nB, tod, 0);


	nB = another;
	nB = translate(nB, vec3(-9.55,-8.95,-0.6));
	nB = scale(nB, vec3(0.5, 0.5, 1));
	nB = rotate(nB, 90.f, vec3(0,0,1));
	nB = rotate(nB, 90.f, vec3(0,1,0));
	nB = rotate(nB, -90.f, vec3(0,0,1));
	backgroundSquare.Draw(Projection2, nB, tod, 0);

	nB = another;
	nB = translate(nB, vec3(-9.55,-8.35,-0.6));
	nB = scale(nB, vec3(0.5, 0.5, 1));
	nB = rotate(nB, 90.f, vec3(0,0,1));
	nB = rotate(nB, 90.f, vec3(0,1,0));
	nB = rotate(nB, -90.f, vec3(0,0,1));
	killsIcon.Draw(Projection2, nB, tod, 0);

	nB = another;
	nB = translate(nB, vec3(-8.525,-8.95,-0.6));
	nB = scale(nB, vec3(0.5, 0.5, 1));
	nB = rotate(nB, 90.f, vec3(0,0,1));
	nB = rotate(nB, 90.f, vec3(0,1,0));
	nB = rotate(nB, -90.f, vec3(0,0,1));
	backgroundSquare.Draw(Projection2, nB, tod, 0);

	nB = another;
	nB = translate(nB, vec3(-8.525,-8.35,-0.6));
	nB = scale(nB, vec3(0.5, 0.5, 1));
	nB = rotate(nB, 90.f, vec3(0,0,1));
	nB = rotate(nB, 90.f, vec3(0,1,0));
	nB = rotate(nB, -90.f, vec3(0,0,1));
	ammoIcon.Draw(Projection2, nB, tod, 0);

	nB = another;
	nB = translate(nB, vec3(-7.5,-8.95,-0.6));
	nB = scale(nB, vec3(0.5, 0.5, 1));
	nB = rotate(nB, 90.f, vec3(0,0,1));
	nB = rotate(nB, 90.f, vec3(0,1,0));
	nB = rotate(nB, -90.f, vec3(0,0,1));
	backgroundSquare.Draw(Projection2, nB, tod, 0);

	nB = another;
	nB = translate(nB, vec3(-7.5,-8.35,-0.6));
	nB = scale(nB, vec3(0.5, 0.5, 1));
	nB = rotate(nB, 90.f, vec3(0,0,1));
	nB = rotate(nB, 90.f, vec3(0,1,0));
	nB = rotate(nB, -90.f, vec3(0,0,1));
	grenadeIcon.Draw(Projection2, nB, tod, 0);

	nB = another;
	nB = translate(nB, vec3(-9.85,-9.5,-0.6));
	nB = scale(nB, vec3(0.3, 0.3, 1));
	nB = rotate(nB, 90.f, vec3(0,0,1));
	nB = rotate(nB, 90.f, vec3(0,1,0));
	nB = rotate(nB, -90.f, vec3(0,0,1));
	healthIcon.Draw(Projection2, nB, tod, 0);

	nB = another;
	nB = translate(nB, vec3(-9.55,-9.56,-0.6));
	nB = scale(nB, vec3(5.1, 0.2, 1));
	nB = rotate(nB, 90.f, vec3(0,0,1));
	nB = rotate(nB, 90.f, vec3(0,1,0));
	nB = rotate(nB, -90.f, vec3(0,0,1));
	backgroundSquare.Draw(Projection2, nB, tod, 0);

	if(firstPerson){
		nB = another;

		nB = translate(nB, vec3(-10,0.05,-0.6));
		nB = scale(nB, vec3(20.f,10.f,1));

		nB = rotate(nB, 90.f, vec3(0,0,1));
		nB = rotate(nB, 90.f, vec3(0,1,0));
		nB = rotate(nB, -90.f, vec3(0,0,1));

		reticule.Draw(Projection2, nB, tod, 0);
	}


	if(userTeam.soldiers[0].userDamageFlag){
		nB = another;
		//nB = rotate(nB, tmpRot1, vec3(0,1,0));
		nB = translate(nB, vec3(-10,0.05,0.0));
		nB = scale(nB, vec3(20.f,20.f,1));
		//usr.Draw(Projection2, nB, tod, 0);

		nB = rotate(nB, 90.f, vec3(0,0,1));
		nB = rotate(nB, 90.f, vec3(0,1,0));
		nB = rotate(nB, -90.f, vec3(0,0,1));
		
		glDepthMask(GL_FALSE);
		userDamaged.Draw(Projection2, nB, tod, 0);
		glDepthMask(GL_TRUE);

		userTeam.soldiers[0].userDamageCounter++;
		if(userTeam.soldiers[0].userDamageCounter > 3){
			userTeam.soldiers[0].userDamageCounter = 0;
			userTeam.soldiers[0].userDamageFlag = false;
		}
	}

	if(userTeam.soldiers[0].userCanisterFlag){
		nB = another;
		nB = translate(nB, vec3(-10,0.05,0.0));
		nB = scale(nB, vec3(20.f,20.f,1));

		nB = rotate(nB, 90.f, vec3(0,0,1));
		nB = rotate(nB, 90.f, vec3(0,1,0));
		nB = rotate(nB, -90.f, vec3(0,0,1));
		
		glDepthMask(GL_FALSE);
		userHealed.Draw(Projection2, nB, tod, 0);
		glDepthMask(GL_TRUE);

		userTeam.soldiers[0].userCanisterCounter++;
		if(userTeam.soldiers[0].userCanisterCounter > 3){
			userTeam.soldiers[0].userCanisterCounter = 0;
			userTeam.soldiers[0].userCanisterFlag = false;
		}
	}

	another = translate(another, vec3(8.5,-8.5,0));
		
	another = rotate(another, 90.0f, vec3(0,1,0));
	another = rotate(another, 90.0f, vec3(0,0,1));

	healthBarMatrix = translate(healthBarMatrix, vec3(-9.5,-9.65,0));
		
	healthBarMatrix = rotate(healthBarMatrix, -90.0f, vec3(0,0,1));
	healthBarMatrix = scale(healthBarMatrix, vec3(0.05f, userTeam.soldiers[0].health/20.f, 0.05f));

	if(userTeam.soldiers[0].health < 50){
		healthBar.colorA = vec4(1.f, userTeam.soldiers[0].health/50.f, 0.f, 0.85);
	}
	else{
		healthBar.colorA = vec4(1.f - (userTeam.soldiers[0].health-50.f)/50.f, 1.f, 0.f, 0.85);
	}
	healthBar.Draw(Projection2, healthBarMatrix, tod, 0);

	mat4 radar = another;

	//Radar display
		
	int radarBlipTime = (int)(current_timeDisplay) * 1000;
	float radarBlip = (float)(0.0015 * (radarBlipTime%1000));
	radar = scale(radar, vec3(radarBlip, radarBlip, radarBlip));
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	disc.color = vec3(0,1,0);
	disc.colorA = vec4(0,1,0,0.35);
	disc.Draw(Projection2, radar, tod, 0);

	another = scale(another, vec3(1.5, 1.5, 1.5));
	disc.Draw(Projection2, another, tod, 0);		

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);    //Include a wireframe variable if necessary
	disc.color = vec3(0,0.25,0);
	disc.colorA = vec4(0,0.25,0,0.35);
	disc.Draw(Projection2, another, tod, 0);

	another = translate(View, vec3(8.5 - ((3/104.6)*transX),-8.6 + ((3/104.6)*transZ),0));
	//usr.Draw(Projection2, another, tod, 0);

	modelview = render(modelview);
}

bool GameMode1::checkGameOver(int &winningTeam, string &winningTeamName, vec4 &winningTeamFontColor){
	if(redTeam.numRemaining == 0 && greenTeam.numRemaining == 0 && blueTeam.numRemaining == 0){
		winningTeam=1;winningTeamName="Yellow";winningTeamFontColor=vec4(1,1,0,1);return true;
	}
	else if(redTeam.numRemaining == 0 && userTeam.numRemaining == 0 && blueTeam.numRemaining == 0){
		winningTeam=2;winningTeamName="Green";winningTeamFontColor=vec4(0,1,0,1);return true;
	}
	else if(redTeam.numRemaining == 0 && greenTeam.numRemaining == 0 && userTeam.numRemaining == 0){
		winningTeam=3;winningTeamName="Blue";winningTeamFontColor=vec4(0,0,1,1);return true;
	}
	else if(userTeam.numRemaining == 0 && greenTeam.numRemaining == 0 && blueTeam.numRemaining == 0){
		winningTeam=4;winningTeamName="Red";winningTeamFontColor=vec4(1,0,0,1);return true;
	}
	return false;
}

void GameMode1::AfterDeath(vector<Soldier *> &remainingSoldiers, float &transX2, float &transY2, float &transZ2){
	if(followCpuSoldier){
		transX2 = -remainingSoldiers.at(soldierToFollowIndex)->pos.z;
		transY2 = remainingSoldiers.at(soldierToFollowIndex)->pos.y;
		transZ2 = remainingSoldiers.at(soldierToFollowIndex)->pos.x;
		if(remainingSoldiers.at(soldierToFollowIndex)->dead){
			soldierToFollowIndex = 0;
			remainingSoldiers.clear();
			for(int i=1; i<userTeam.NUM_SOLDIERS; i++){
				if(!userTeam.soldiers[i].dead){
					remainingSoldiers.push_back(&userTeam.soldiers[i]);
				}
			}
			for(int i=0; i<userTeam.NUM_SOLDIERS; i++){
				if(!greenTeam.soldiers[i].dead){
					remainingSoldiers.push_back(&greenTeam.soldiers[i]);
				}
				if(!blueTeam.soldiers[i].dead){
					remainingSoldiers.push_back(&blueTeam.soldiers[i]);
				}
				if(!redTeam.soldiers[i].dead){
					remainingSoldiers.push_back(&redTeam.soldiers[i]);
				}
			}
		}
	}
}

