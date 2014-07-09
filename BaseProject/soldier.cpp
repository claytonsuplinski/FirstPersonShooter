/*
Name: Clayton Suplinski
ID: 906 580 2630
CS 559 Project 3

Creates a shark object out of basic shapes.
*/

#include <iostream>
#include "soldier.h"

using namespace std;
using namespace glm;

//Create a Shark object
Soldier::Soldier() : Object(){
	this->health = maxHP;
	this->dead = false;
	this->user = false;
	this->userTeam = false;
	this->ammo = maxAmmo;
	this->grenades = maxGrenades;
	this->kills = 0;
}

Soldier::~Soldier(){this->TakeDown();}

//Initialize all the Shark elements.
bool Soldier::Initialize()
{
	if (this->GLReturnedError("Soldier::Initialize - on entry"))
		return false;

	this->soldier = new Gengar();

	this->person.Initialize();

	fallDownTime = 0;fadeTime = 0;userDamageCounter = 0;

	if (this->GLReturnedError("Soldier::Initialize - on exit"))
		return false;

	return true;
}

//Delete the Shark elements.
void Soldier::TakeDown()
{
	this->soldier = NULL;this->person.TakeDown();
	this->vertices.clear();
	this->shader.TakeDown();
	super::TakeDown();	
}

//Draw and position the Shark elements.
void Soldier::Draw(const mat4 & projection, mat4 modelview, const ivec2 & size, const float rotY)
{
	if (this->GLReturnedError("Soldier::Draw - on entry"))
		return;

	glEnable(GL_DEPTH_TEST);
	mat4 another, scaler;
	another = modelview;

	if(!dead){
		if(distFromUser <= 300){
			this->person.Draw(projection, another, size, rotY);
		}
	}
	else if(dead && fadeTime < 0.6f){
		this->person.dead = true;
		if(distFromUser <= 300){			
			this->person.Draw(projection, another, size, rotY);
		}
	}
	
	if (this->GLReturnedError("Soldier::Draw - on exit"))
		return;
}

//Draw and position the Shark elements.
void Soldier::DrawTransparent(const mat4 & projection, mat4 modelview, const ivec2 & size, const float rotY)
{
	if (this->GLReturnedError("Soldier::DrawT - on entry"))
		return;

	glEnable(GL_DEPTH_TEST);
	mat4 another, scaler;
	another = modelview;

	if(!dead){
		if(distFromUser <= 300){
			this->person.DrawTransparent(projection, another, size, rotY);
		}
	}
	else if(dead && fadeTime < 0.6f){
		this->person.dead = true;
		if(distFromUser <= 300){			
			this->person.DrawTransparent(projection, another, size, rotY);
		}
	}
	
	if (this->GLReturnedError("Soldier::DrawT - on exit"))
		return;
}
