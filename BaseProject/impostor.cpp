/*
Name: Clayton Suplinski
Project: First-Person Shooter
*/

#include "impostor.h"

Impostor::Impostor() : Object(){}

Impostor::~Impostor()
{
	this->TakeDown();
}

bool Impostor::Initialize(char * filename)
{
	if (this->GLReturnedError("Impostor::Initialize - on entry"))
		return false;

	this->square = new Square3();

	squareSize = 100.f;

	impostorPos = vec3(0,0,0);

	this->square->Initialize(1,squareSize, filename, "basic_texture_shader.vert", "basic_texture_shader.frag");

	if (this->GLReturnedError("Impostor::Initialize - on exit"))
		return false;

	return true;
}

void Impostor::TakeDown(){
	super::TakeDown();	
}

void Impostor::Draw(const mat4 & projection, mat4 modelview, const ivec2 & size, const float time)
{
	if (this->GLReturnedError("Impostor::Draw - on entry"))
		return;

	glEnable(GL_DEPTH_TEST);

	float ct = float(glutGet(GLUT_ELAPSED_TIME)) / 200.0f;

	vec2 C = vec2(impostorPos.x, impostorPos.z);
	vec2 W1 = vec2(-100,0);
	vec2 W2 = vec2(userPos.x, userPos.z);

	float angle = atan2(W1.y, W1.x) - atan2(W2.y, W2.x);
	angle *= 180.f/3.14f;

	modelview = rotate(modelview, angle, vec3(0,1,0));

	modelview = translate(modelview, vec3(squareSize/2, squareSize, 0));
	modelview = rotate(modelview, -90.f, vec3(1,0,0));	

	glDepthMask(GL_FALSE);
	
	this->square->Draw(projection, modelview, size, 0);	

	glDepthMask(GL_TRUE);
	
	if (this->GLReturnedError("Impostor::Draw - on exit"))
		return;
}
