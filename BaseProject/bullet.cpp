/*
Name: Clayton Suplinski
Project: First-Person Shooter
*/

#include "bullet.h"

Bullet::Bullet() : Object(){
	isDrawing = false;doneDrawing = false;
}

Bullet::~Bullet(){this->TakeDown();}

bool Bullet::Initialize(vec3 color)
{
	if (this->GLReturnedError("Bullet::Initialize - on entry"))
		return false;

	this->bullet = new Sphere();

	velocityFactor = 0.02;
	distance = 100;

	this->bullet->color = color;
	this->bullet->Initialize(1, 1.0f, "phong.vert", "phong.frag");

	if (this->GLReturnedError("Bullet::Initialize - on exit"))
		return false;

	return true;
}

void Bullet::TakeDown()
{
	this->bullet = NULL;
	this->shader.TakeDown();
	super::TakeDown();	
}

float Bullet::dist(float x1, float y1, float z1, float x2, float y2, float z2){
	float x=x2-x1;float y=y2-y1;float z=z2-z1;
	return sqrt(x*x + y*y + z*z);
}

void Bullet::Draw(const mat4 & projection, mat4 modelview, const ivec2 & size, const float rotY)
{
	if (this->GLReturnedError("Bullet::Draw - on entry"))
		return;

	glEnable(GL_DEPTH_TEST);
	mat4 another, scaler;
	another = modelview;
	
	if(!doneDrawing){
		if(currPos.x == startPos.x){
			another = translate(another, vec3(4,0,0));
		}

		//Move the bullet one step closer to the endPos
		currPos.x += velocityFactor*(endPos.x-startPos.x);
		currPos.y += velocityFactor*(endPos.y-startPos.y);
		currPos.z += velocityFactor*(endPos.z-startPos.z);

		if(dist(currPos.x, currPos.y, currPos.z, endPos.x, endPos.y, endPos.z) <= 2){
				isDrawing = false;doneDrawing = true;
		}
		
		another = scale(another, vec3(3.0f, 0.02f, 0.02f));
		if(distFromUser <= 250){this->bullet->Draw(projection, another, size, 0);}
	}
	
	if (this->GLReturnedError("Bullet::Draw - on exit"))
		return;
}
