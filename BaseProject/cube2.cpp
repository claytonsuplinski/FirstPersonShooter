/*
Name: Clayton Suplinski
ID: 906 580 2630
CS 559 Project 3

Creates a textured cube with 6 different images
(used only as skybox)
*/

#include <iostream>
#include "cube2.h"

using namespace std;
using namespace glm;

//Create the cube object
Cube2::Cube2() : Object()
{
}

Cube2::~Cube2(){
	this->TakeDown();
}

//Initialize all the elements of the cube object
bool Cube2::Initialize(int skyboxID, int baseTexID, char* v, char* f)
{
	if (this->GLReturnedError("Cube2::Initialize - on entry"))
		return false;

	if (!super::Initialize())
		return false;

	this->left = new Square2();this->right = new Square2();
	this->up = new Square2();this->down = new Square2();
	this->front = new Square2();this->back = new Square2();

	char *leftBox, *rightBox, *topBox, *botBox, *frontBox, *backBox;

	leftBox="./skyboxMain/frontsh.jpg";rightBox="./skyboxMain/backsh.jpg";
	topBox="./skyboxMain/toptsh.jpg";botBox="./skyboxMain/botsh.jpg";
	frontBox="./skyboxMain/leftsh.jpg";backBox="./skyboxMain/rightsh.jpg";
		

	this->left->Initialize(1200.0f,1,leftBox,v,f);this->right->Initialize(1200.0f,1,rightBox,v,f);	
	this->up->Initialize(1200.0f,1,topBox,v,f);this->down->Initialize(1200.0f,1,botBox,v,f);	
	this->front->Initialize(1200.0f,1,frontBox,v,f);this->back->Initialize(1200.0f,1,backBox,v,f);	
	
	if (this->GLReturnedError("Cube2::Initialize - on exit"))
		return false;

	return true;
}

void Cube2::StepShader(){
	this->left->StepShader();this->right->StepShader();
	this->up->StepShader();this->down->StepShader();
	this->front->StepShader();this->back->StepShader();
}

//Delete the cube object
void Cube2::TakeDown()
{
	this->left = NULL;this->right = NULL;
	this->up = NULL;this->down = NULL;
	this->front = NULL;this->back = NULL;
	this->vertices.clear();
	this->shader.TakeDown();
	this->solid_color.TakeDown();
	super::TakeDown();
}

//Draw and position the elements of the cube
void Cube2::Draw(const mat4 & projection, mat4 modelview, const ivec2 & size, const float time)
{
	if (this->GLReturnedError("Cube2::Draw - on entry"))
		return;

	glEnable(GL_DEPTH_TEST);

	mat4 another, scaler;

	another = modelview;
	another = translate(another, vec3(600.0f, 0.0f, 0.0f));
	another = rotate(another, 90.0f, vec3(0,1,0));
	this->left->Draw(projection, another, size, 0);
	another = rotate(another, -90.0f, vec3(0,1,0));
	another = translate(another, vec3(-1200.0f, 0.0f, 0.0f));
	another = rotate(another, -90.0f, vec3(0,1,0));
	this->right->Draw(projection, another, size, 0);

	another = modelview;
	another = translate(another, vec3(0.0f,600.0f,0.0f));
	another = rotate(another, 90.0f, vec3(0,1,0));
	another = rotate(another, -90.0f, vec3(1,0,0));
	this->up->Draw(projection, another, size, 0);

	another = modelview;
	another = translate(another, vec3(0.0f,-600.0f,0.0f));
	another = rotate(another, 90.0f, vec3(0,1,0));
	another = rotate(another, 90.0f, vec3(1,0,0));
	this->down->Draw(projection, another, size, 0);

	another = modelview;
	another = translate(another, vec3(0.0f,0.0f,600.0f));	
	this->front->Draw(projection, another, size, 0);

	another = modelview;
	another = translate(another, vec3(0.0f,0.0f,-600.0f));
	another = rotate(another, 180.0f, vec3(0,1,0));
	this->back->Draw(projection, another, size, 0);

	if (this->GLReturnedError("Cube2::Draw - on exit"))
		return;
}
