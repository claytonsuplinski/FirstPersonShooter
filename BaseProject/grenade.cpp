/*
Name: Clayton Suplinski
ID: 906 580 2630
CS 559 Project 3

Creates a shark object out of basic shapes.
*/

#include <iostream>
#include "grenade.h"

using namespace std;
using namespace glm;

//Create a Shark object
Grenade::Grenade() : Object(){
	doneDrawing = false;
}

Grenade::~Grenade(){this->TakeDown();}

//Initialize all the Shark elements.
bool Grenade::Initialize(vec3 color)
{
	if (this->GLReturnedError("Grenade::Initialize - on entry"))
		return false;

	this->grenade = new Sphere();this->explosion = new Sphere2();

	velocityFactor = 0.05;
	distance = 70;

	explode = false;
	fallingTime = 0;explodeRadius = 1;

	grenadeRadius = 0.5f;

	this->grenade->color = color;
	this->grenade->Initialize(4, grenadeRadius, "phong3.vert", "phong3.frag");

	this->explosion->Initialize(4, grenadeRadius, "./textures/explosion.png", "basic_texture_shader.vert", "basic_texture_shader.frag");

	if (this->GLReturnedError("Grenade::Initialize - on exit"))
		return false;

	return true;
}

//Delete the Shark elements.
void Grenade::TakeDown()
{
	this->grenade = NULL;
	this->vertices.clear();
	this->shader.TakeDown();
	super::TakeDown();	
}

float Grenade::dist(float x1, float y1, float z1, float x2, float y2, float z2){
	float x=x2-x1;float y=y2-y1;float z=z2-z1;
	return sqrt(x*x + y*y + z*z);
}

//Draw and position the Shark elements.
void Grenade::Draw(const mat4 & projection, mat4 modelview, const ivec2 & size, const float rotY)
{
	if (this->GLReturnedError("Grenade::Draw - on entry"))
		return;

	glEnable(GL_DEPTH_TEST);
	mat4 another, scaler;
	another = modelview;

	float t = glutGet(GLUT_ELAPSED_TIME);
	
	if(!doneDrawing){
		if(!explode){
			if(fallingTime < 1.22){fallingTime += 0.1f;}
			else{fallingTime = 1.2247f;}
			//Move the Grenade one step closer to the endPos	
			currPos.x += velocityFactor*(endPos.x-startPos.x);
			currPos.y = 0.f - fallingTime*fallingTime;
			//currPos.y += velocityFactor*(endPos.y-startPos.y); Need to adjust for falling to ground (exponential rate)
			currPos.z += velocityFactor*(endPos.z-startPos.z);			

			if(dist(currPos.x, 0, currPos.z, startPos.x, 0, startPos.z) >= 
				dist(endPos.x, 0, endPos.z, startPos.x, 0, startPos.z)){explode = true;}
	
			this->grenade->colorA = vec4(0,0.5,0, 1);
			this->grenade->Draw(projection, another, size, 0);
		}
		else{
			mat4 innerExplosion = another;
			innerExplosion = rotate(innerExplosion, -2*t, vec3(0,1,0));
			innerExplosion = rotate(innerExplosion, t, vec3(1,0,0));
			innerExplosion = scale(innerExplosion, vec3(explodeRadius/2, explodeRadius/2, explodeRadius/2));
			this->explosion->Draw(projection, innerExplosion, size, 0);

			another = rotate(another, t, vec3(0,1,0));
			another = rotate(another, 2*t, vec3(1,0,0));
			another = scale(another, vec3(explodeRadius, explodeRadius, explodeRadius));
			this->explosion->Draw(projection, another, size, 0);
			
			if(explodeRadius < maxExplodeRadius){explodeRadius += 2.f;}
			else{doneDrawing = true;}
		}
	}
	
	if (this->GLReturnedError("Grenade::Draw - on exit"))
		return;
}
