/*
Name: Clayton Suplinski
ID: 906 580 2630
CS 559 Project 3

Creates the UFO arena
*/

#include <iostream>
#include "personFixed.h"

using namespace std;
using namespace glm;

//Create the arena
PersonFixed::PersonFixed() : Object()
{
}

PersonFixed::~PersonFixed(){
	this->TakeDown();
}

//Initialize all the elements of the arena
bool PersonFixed::Initialize(char* v, char* f)
{
	if (this->GLReturnedError("PersonFixed::Initialize - on entry"))
		return false;

	if (!super::Initialize())
		return false;

	this->head = new Gengar();
	this->torso = new Gengar();
	this->upperArm = new Gengar();
	this->lowerArm = new Gengar();
	this->upperLeg = new Gengar();
	this->lowerLeg = new Gengar();
	this->gun = new Gengar();
	this->shoe = new Gengar();
	
	this->head->order = 1;
	this->head->Initialize("./models/Soldier/soldierHead.obj", "./models/Soldier/soldierHead.png", v,f);

	this->torso->order = 1;
	this->torso->Initialize("./models/Soldier/soldierTorso.obj", "./models/Soldier/soldierTorso.png", 
		 v,f);

	this->upperArm->order = 1;
	this->upperArm->Initialize("./models/Soldier/soldierUpperArm.obj", "./models/Soldier/soldierUpperArm.png", 
		 v,f);

	this->lowerArm->order = 1;
	this->lowerArm->Initialize("./models/Soldier/soldierLowerArm.obj", "./models/Soldier/soldierLowerArm.png", 
		 v,f);

	this->upperLeg->order = 1;
	this->upperLeg->Initialize("./models/Soldier/soldierUpperLeg.obj", "./models/Soldier/soldierUpperLeg.png", 
		 v,f);

	this->lowerLeg->order = 1;
	this->lowerLeg->Initialize("./models/Soldier/soldierLowerLeg.obj", "./models/Soldier/soldierLowerLeg.png", 
		 v,f);

	this->gun->order = 1;
	this->gun->Initialize("./models/Soldier/soldierGun.obj", "./models/Soldier/soldierGun.png", 
		 v,f);

	this->shoe->order = 1;
	this->shoe->Initialize("./models/Soldier/soldierShoe.obj", "./models/Soldier/soldierShoe.png", 
		 v,f);

	if (this->GLReturnedError("PersonFixed::Initialize - on exit"))
		return false;

	return true;
}

//Delete the DiscStadium object
void PersonFixed::TakeDown()
{
	this->head = NULL;this->torso = NULL;this->upperArm = NULL;
	this->shader.TakeDown();
	this->solid_color.TakeDown();
	super::TakeDown();
}

//Draw and position the elements of the DiscStadium
void PersonFixed::Draw(const mat4 & projection, mat4 modelview, const ivec2 & size, const float time)
{
	if (this->GLReturnedError("PersonFixed::Draw - on entry"))
		return;

	glEnable(GL_DEPTH_TEST);

	modelview = translate(modelview, vec3(0, -1, 0));

	mat4 another, limb, running, modelviewReset;

	float legRotation = 50*sin(0.f)-15;
	float legRotation2 = -50*sin(0.f)-15;

	float walkingOffset = abs(sin(0.f));
	modelview = translate(modelview, vec3(0.25*walkingOffset, 0.1*walkingOffset,0));

	modelviewReset = modelview;

	another = modelview;
	another = translate(another, vec3(0,2.05,0));
	another = rotate(another, 90.f, vec3(0,1,0));
	another = scale(another, vec3(0.03, 0.03, 0.03));
	this->head->Draw(projection, another, size, time);

	another = modelview;
	another = translate(another, vec3(0.0,0.7,0.0));
	another = rotate(another, 90.f, vec3(0,1,0));
	another = scale(another, vec3(0.035, 0.035, 0.035));
	this->torso->Draw(projection, another, size, time);

	modelview = modelviewReset;

	//Rotate whole left arm
	modelview = translate(modelview, vec3(0.0, 1.62, 0.0));
	modelview = rotate(modelview, 63.f + legRotation2/10, vec3(0,0,1));
	modelview = translate(modelview, vec3(0.0, -1.62, 0.0));
	//Left upper arm
	another = modelview;
	another = translate(another, vec3(0.0, 1.3, -0.4));
	another = rotate(another, 90.f, vec3(0,1,0));
	another = scale(another, vec3(0.035, 0.035, 0.035));
	this->upperArm->Draw(projection, another, size, time);
	//Rotate lower left arm
	modelview = translate(modelview, vec3(0, 1.305, -0.405));
	modelview = rotate(modelview, 310.5f, vec3(1,0,0));
	modelview = rotate(modelview, 8.25f, vec3(0,0,1));
	modelview = translate(modelview, vec3(0, -1.305, 0.405));
	//Left lower arm
	another = modelview;
	another = translate(another, vec3(0.0, 1.1, -0.4));
	another = rotate(another, -90.f, vec3(0,1,0));
	another = scale(another, vec3(0.035, 0.035, 0.035));
	this->lowerArm->Draw(projection, another, size, time);

	modelview = modelviewReset;

	//Rotate whole right arm
	modelview = translate(modelview, vec3(0.0, 1.62, 0.0));
	modelview = rotate(modelview, 63.f + legRotation/10, vec3(0,0,1));
	modelview = translate(modelview, vec3(0.0, -1.62, 0.0));
	//Right upper arm
	another = modelview;
	another = translate(another, vec3(0.0, 1.3, 0.4));
	another = rotate(another, 90.f, vec3(0,1,0));
	another = scale(another, vec3(0.035, 0.035, 0.035));
	this->upperArm->Draw(projection, another, size, time);
	//Rotate lower right arm
	modelview = translate(modelview, vec3(0, 1.305, 0.405));
	modelview = rotate(modelview, 49.5f, vec3(1,0,0));
	modelview = rotate(modelview, 17.4f, vec3(0,0,1));
	modelview = translate(modelview, vec3(0, -1.305, -0.405));
	//Right lower arm
	another = modelview;
	another = translate(another, vec3(0.0, 1.1, 0.4));
	another = rotate(another, -90.f, vec3(0,1,0));
	another = scale(another, vec3(0.035, 0.035, 0.035));
	this->lowerArm->Draw(projection, another, size, time);

	modelview = modelviewReset;

	//Rotate whole left leg
	modelview = translate(modelview, vec3(0.0, 0.765, 0.0));
	modelview = rotate(modelview, 2.f+legRotation, vec3(0,0,1));
	modelview = translate(modelview, vec3(0.0, -0.765, 0.0));
	//Left upper leg
	another = modelview;
	another = translate(another, vec3(0.0, 0.6, -0.1));
	another = rotate(another, 90.f, vec3(0,1,0));
	another = scale(another, vec3(0.03, 0.03, 0.03));
	this->upperLeg->Draw(projection, another, size, time);
	//Rotate lower left leg
	modelview = translate(modelview, vec3(0, 0.315, -0.09));
	//modelview = rotate(modelview, -4.f, vec3(0,0,1));
	modelview = rotate(modelview, -4.f, vec3(0,0,1));
	modelview = translate(modelview, vec3(0, -0.315, 0.09));
	//Left lower leg
	another = modelview;
	another = translate(another, vec3(0, 0.2, -0.1));
	another = rotate(another, 90.f, vec3(0,1,0));
	another = scale(another, vec3(0.02, 0.02, 0.02));
	this->lowerLeg->Draw(projection, another, size, time);
	//Left foot
	another = modelview;
	another = translate(another, vec3(0.19, 0, -0.1));
	another = rotate(another, 90.f, vec3(0,1,0));
	another = scale(another, vec3(0.01, 0.01, 0.01));
	this->shoe->Draw(projection, another, size, time);

	modelview = modelviewReset;

	//Rotate whole right leg
	modelview = translate(modelview, vec3(0.0, 0.765, 0.0));
	modelview = rotate(modelview, 2.f + legRotation2, vec3(0,0,1));
	modelview = translate(modelview, vec3(0.0, -0.765, 0.0));
	//Right upper leg
	another = modelview;
	another = translate(another, vec3(0.0, 0.6, 0.1));
	another = rotate(another, 90.f, vec3(0,1,0));
	another = scale(another, vec3(0.03, 0.03, 0.03));
	this->upperLeg->Draw(projection, another, size, time);
	//Rotate lower right leg
	modelview = translate(modelview, vec3(0, 0.315, 0.09));
	modelview = rotate(modelview, -4.f, vec3(0,0,1));
	modelview = translate(modelview, vec3(0, -0.315, -0.09));
	//Right lower leg
	another = modelview;
	another = translate(another, vec3(0, 0.2, 0.1));
	another = rotate(another, 90.f, vec3(0,1,0));
	another = scale(another, vec3(0.02, 0.02, 0.02));
	this->lowerLeg->Draw(projection, another, size, time);
	//Right foot
	another = modelview;
	another = translate(another, vec3(0.19, 0, 0.1));
	another = rotate(another, 90.f, vec3(0,1,0));
	another = scale(another, vec3(0.01, 0.01, 0.01));
	this->shoe->Draw(projection, another, size, time);

	modelview = modelviewReset;

	another = modelview;
	another = translate(another, vec3(0.6, 1.44, 0.0));
	another = rotate(another, -90.f, vec3(0,1,0));
	another = scale(another, vec3(0.008,0.008,0.008));
	this->gun->Draw(projection, another, size, time);
	
	if (this->GLReturnedError("PersonFixed::Draw - on exit"))
		return;
}
