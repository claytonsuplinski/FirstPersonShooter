/*
Name: Clayton Suplinski
Project: First-Person Shooter
*/

#include "canister.h"

Canister::Canister() : Object(){
	doneDrawing = false;
}

Canister::~Canister(){this->TakeDown();}

bool Canister::Initialize(int type)
{
	if (this->GLReturnedError("Canister::Initialize - on entry"))
		return false;

	this->canister = new Cylinder();

	this->canisterRadius = 0.25f;
	this->canisterHeight = 0.5f;

	this->lifetime = 0;

	this->type = type;

	switch(type){
	case 1: // Hp
	default:
		this->canister->colorA = vec4(0,0,1,1);
		break;
	case 2: // Ammo
		this->canister->colorA = vec4(1,0,0,1);
		break;
	case 3: // Grenades
		this->canister->colorA = vec4(0,1,0,1);
		break;
	}
	
	this->canister->Initialize(1, canisterHeight, canisterRadius, canisterRadius, "phong3.vert", "phong3.frag");

	if (this->GLReturnedError("Canister::Initialize - on exit"))
		return false;

	return true;
}

void Canister::TakeDown()
{
	this->canister = NULL;
	this->shader.TakeDown();
	super::TakeDown();	
}

void Canister::Draw(const mat4 & projection, mat4 modelview, const ivec2 & size, const float rotY)
{
	if (this->GLReturnedError("Canister::Draw - on entry"))
		return;

	glEnable(GL_DEPTH_TEST);
	mat4 another, scaler;
	another = modelview;

	switch(type){
	case 1: // Hp
	default:
		this->canister->colorA = vec4(0,0,1,1);
		break;
	case 2: // Ammo
		this->canister->colorA = vec4(1,0,0,1);
		break;
	case 3: // Grenades
		this->canister->colorA = vec4(0,1,0,1);
		break;
	}
	
	if(!doneDrawing){	
		if(lifetime < 1000){lifetime++;}
		else{doneDrawing = true;}
		
		this->canister->Draw(projection, another, size, 0);
	}
	
	if (this->GLReturnedError("Canister::Draw - on exit"))
		return;
}
