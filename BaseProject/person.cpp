/*
Name: Clayton Suplinski
ID: 906 580 2630
CS 559 Project 3

Creates the UFO arena
*/

#include <iostream>
#include "person.h"

using namespace std;
using namespace glm;

//Create the arena
Person::Person() : Object()
{
}

Person::~Person(){
	this->TakeDown();
}

//Initialize all the elements of the arena
bool Person::Initialize()
{
	if (this->GLReturnedError("Person::Initialize - on entry"))
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
	this->deathEffect = new Impostor();

	editX=0;editY=0;
	velocity = 0;
	MAX_VELOCITY = 0.35;
	
	this->head->order = 1;
	this->head->Initialize("./models/Soldier/soldierHead.obj", "./models/Soldier/soldierHead.png", 
		"basic_texture_shader.vert", "basic_texture_shader2.frag");

	this->torso->order = 1;
	this->torso->Initialize("./models/Soldier/soldierTorso.obj", "./models/Soldier/soldierTorso.png", 
		"basic_texture_shader.vert", "basic_texture_shader2.frag");

	this->upperArm->order = 1;
	this->upperArm->Initialize("./models/Soldier/soldierUpperArm.obj", "./models/Soldier/soldierUpperArm.png", 
		"basic_texture_shader.vert", "basic_texture_shader2.frag");

	this->lowerArm->order = 1;
	this->lowerArm->Initialize("./models/Soldier/soldierLowerArm.obj", "./models/Soldier/soldierLowerArm.png", 
		"basic_texture_shader.vert", "basic_texture_shader2.frag");

	this->upperLeg->order = 1;
	this->upperLeg->Initialize("./models/Soldier/soldierUpperLeg.obj", "./models/Soldier/soldierUpperLeg.png", 
		"basic_texture_shader.vert", "basic_texture_shader2.frag");

	this->lowerLeg->order = 1;
	this->lowerLeg->Initialize("./models/Soldier/soldierLowerLeg.obj", "./models/Soldier/soldierLowerLeg.png", 
		"basic_texture_shader.vert", "basic_texture_shader2.frag");

	this->gun->order = 1;
	this->gun->Initialize("./models/Soldier/soldierGun.obj", "./models/Soldier/soldierGun.png", 
		"basic_texture_shader.vert", "basic_texture_shader2.frag");

	this->shoe->order = 1;
	this->shoe->Initialize("./models/Soldier/soldierShoe.obj", "./models/Soldier/soldierShoe.png", 
		"basic_texture_shader.vert", "basic_texture_shader2.frag");

	this->deathEffect->Initialize("./textures/deathEffect.png");

	tmpZoom = 0.01;
	tmpX = 0;tmpY = 0;tmpZ = 0;

	fallDownTime = 0;fadeTime = 0;
	dead = false;

	if (this->GLReturnedError("Person::Initialize - on exit"))
		return false;

	return true;
}

//Delete the DiscStadium object
void Person::TakeDown()
{
	this->head = NULL;this->torso = NULL;this->upperArm = NULL;
	this->vertices.clear();
	this->shader.TakeDown();
	this->solid_color.TakeDown();
	super::TakeDown();
}

//Draw and position the elements of the DiscStadium
void Person::Draw(const mat4 & projection, mat4 modelview, const ivec2 & size, const float time)
{
	if (this->GLReturnedError("Person::Draw - on entry"))
		return;

	glEnable(GL_DEPTH_TEST);

	float ct = float(glutGet(GLUT_ELAPSED_TIME));

	modelview = translate(modelview, vec3(0, -1, 0));

	if(!transparentPass){
	
		if(!dead){
			DrawAlive(projection, modelview, size, time);
		}
		else if(dead && fadeTime < 0.6f){
			if(fallDownTime < MAX_FALLDOWNTIME){fallDownTime+=15;}
			else{fadeTime+=0.06;}

			modelview = scale(modelview, vec3(1.f - fadeTime/0.6, 1.f - fadeTime/0.6, 1.f - fadeTime/0.6));

			DrawDead(projection, modelview, size, time);
		}

	}
	
	if (this->GLReturnedError("Person::Draw - on exit"))
		return;
}

//Draw and position the elements of the DiscStadium
void Person::DrawTransparent(const mat4 & projection, mat4 modelview, const ivec2 & size, const float time)
{
	if (this->GLReturnedError("Person::DrawT - on entry"))
		return;

	float ct = float(glutGet(GLUT_ELAPSED_TIME));

	//modelview = translate(modelview, vec3(0, -1, 0));
	
	if(dead && fadeTime < 0.6f){
		if(fallDownTime >= MAX_FALLDOWNTIME){
			mat4 deathSpiral = modelview;
			//deathSpiral = rotate(deathSpiral, ct, vec3(0,0,1));
			deathSpiral = translate(deathSpiral, vec3(0, 0.7, 0));
			float fadeFactor = 10;
			if(fadeTime < 0.3f){
				deathSpiral = scale(deathSpiral, vec3(fadeTime/fadeFactor, fadeTime/fadeFactor, fadeTime/fadeFactor));
			}
			else{
				deathSpiral = scale(deathSpiral, vec3(0.6/fadeFactor - fadeTime/fadeFactor, 0.6/fadeFactor - fadeTime/fadeFactor, 
					0.6/fadeFactor - fadeTime/fadeFactor));
			}
			deathSpiral = translate(deathSpiral, vec3(0, -deathEffect->squareSize/2, 0));
			deathSpiral = translate(deathSpiral, vec3(0, deathEffect->squareSize/2, 0));
			deathSpiral = rotate(deathSpiral, ct, vec3(1,0,0));
			deathSpiral = translate(deathSpiral, vec3(0, -deathEffect->squareSize/2, 0));
			this->deathEffect->Draw(projection, deathSpiral, size, time);
		}		
	}

	if (this->GLReturnedError("Person::DrawT - on exit"))
		return;
}



void Person::DrawAlive(const mat4 & projection, mat4 modelview, const ivec2 & size, const float time)
{
	float ct = float(glutGet(GLUT_ELAPSED_TIME)) / 200.0f;

	mat4 another, limb, running, modelviewReset;

	float legRotation = velocity*50*sin(ct)-15;
	float legRotation2 = -velocity*50*sin(ct)-15;

	float walkingOffset = abs(velocity*sin(ct));
	modelview = translate(modelview, vec3(0.25*walkingOffset, 0.5*walkingOffset,0));

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
}


void Person::DrawDead(const mat4 & projection, mat4 modelview, const ivec2 & size, const float time)
{
	float ct = float(glutGet(GLUT_ELAPSED_TIME)) / 200.0f;

	mat4 another, limb, running, modelviewReset;

	modelviewReset = modelview;

	another = modelview;
	another = translate(another, vec3(0,2.05 + fallDownTime/MAX_FALLDOWNTIME,0));
	another = rotate(another, 90.f, vec3(0,1,0));
	another = scale(another, vec3(0.03, 0.03, 0.03));
	this->head->Draw(projection, another, size, time);

	another = modelview;
	another = translate(another, vec3(0.0,0.7 + 0.2*fallDownTime/MAX_FALLDOWNTIME,0.0));
	another = rotate(another, 90.f, vec3(0,1,0));
	another = scale(another, vec3(0.035, 0.035, 0.035));
	this->torso->Draw(projection, another, size, time);

	modelview = modelviewReset;

	//Rotate whole left arm
	modelview = translate(modelview, vec3(0.0, 1.62, 0.0));
	modelview = rotate(modelview, 63.f, vec3(0,0,1));
	modelview = translate(modelview, vec3(0.0, -1.62, 0.0));
	//Left upper arm
	another = modelview;
	another = translate(another, vec3(0.0, 1.3 + 0.5*fallDownTime/MAX_FALLDOWNTIME, -0.4 - 0.3*fallDownTime/MAX_FALLDOWNTIME));
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
	modelview = rotate(modelview, 63.f, vec3(0,0,1));
	modelview = translate(modelview, vec3(0.0, -1.62, 0.0));
	//Right upper arm
	another = modelview;
	another = translate(another, vec3(0.0, 1.3 + 0.5*fallDownTime/MAX_FALLDOWNTIME, 0.4 + 0.3*fallDownTime/MAX_FALLDOWNTIME));
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
	modelview = rotate(modelview, 2.f, vec3(0,0,1));
	modelview = translate(modelview, vec3(0.0, -0.765, 0.0));
	//Left upper leg
	another = modelview;
	another = translate(another, vec3(0.0, 0.6, -0.1 - 0.5*fallDownTime/MAX_FALLDOWNTIME));
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
	modelview = rotate(modelview, 2.f, vec3(0,0,1));
	modelview = translate(modelview, vec3(0.0, -0.765, 0.0));
	//Right upper leg
	another = modelview;
	another = translate(another, vec3(0.0, 0.6, 0.1 + 0.5*fallDownTime/MAX_FALLDOWNTIME));
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
	another = translate(another, vec3(0.6, 1.44 + 1.44*fallDownTime/MAX_FALLDOWNTIME, 0.0));
	another = rotate(another, -90.f, vec3(0,1,0));
	another = scale(another, vec3(0.008,0.008,0.008));
	this->gun->Draw(projection, another, size, time);
}
