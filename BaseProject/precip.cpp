/*
Name: Clayton Suplinski
Project: First-Person Shooter
*/

#include "precip.h"
 
Precip::Precip() : Object()
{
	weatherType = 0;
}


bool Precip::Initialize()
{
	if (this->GLReturnedError("Precip::Initialize - on entry"))
		return false;

	if (!super::Initialize())
		return false;

	this->rain2 = new Sphere();
	this->snow2 = new Snow();

	this->rain2->color = vec3(0.4f, 0.4f, 1.0f);
	this->snow2->color = vec3(1.0f, 1.0f, 1.0f);
	
	this->rain2->Initialize(2, 0.02f, "phong.vert", "phong.frag");
	this->snow2->Initialize(3, 0.02f, "phong.vert", "phong2.frag");	

	numParts = 300;
	
	for(int i=0; i<numParts; i++){
		partX.push_back((static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/12)) - 6));
		partY.push_back((static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/12)) - 6));
		partOffset.push_back((float)(rand() % 360 + 1));
	}
	

	if (this->GLReturnedError("Precip::Initialize - on exit"))
		return false;

	return true;
}

void Precip::TakeDown()
{
	this->snow2 = NULL;this->rain2 = NULL;
	super::TakeDown();
}

void Precip::increasePrecip(int amount){
	if(numParts < maxParts){
		for(int i=0; i<amount; i++){
			if(numParts<maxParts){
				partX.push_back((static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/12)) - 6));
				partY.push_back((static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/12)) - 6));
				partOffset.push_back((float)(rand() % 360 + 1));
			}
		}
	}
	numParts = partX.size();
}

void Precip::decreasePrecip(int amount){
	if(numParts > minParts){
		for(int i=0; i<amount; i++){
			if(numParts>minParts){
				partX.pop_back();
				partY.pop_back();
				partOffset.pop_back();
			}
		}
	}
	numParts = partX.size();
}

void Precip::Draw(const mat4 & projection, mat4 modelview, const ivec2 & size, const float radius)
{
	if (this->GLReturnedError("Precip::Draw - on entry"))
		return;

	glEnable(GL_DEPTH_TEST);

	float current_timeDisplay = float(glutGet(GLUT_ELAPSED_TIME)) / 1000.0f;

	if(weatherType > 1){
		mat4 another;
		for(int i=0; i<numParts; i++){
			another = rotate(modelview, 70.0f, vec3(1,0,0));
			float z = 3.f*tan(((weatherType == 2 ? 2.f : 0.75f) *current_timeDisplay)+partOffset[i]);
			another = translate(another, vec3(partX[i],partY[i],z));
			another = rotate(another, 270.0f, vec3(1,0,0));
			another = rotate(another, 90.0f, vec3(0,1,0));
			if(z > 5){
				partX[i] = (static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/12)) - 6);
				partY[i] = (static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/12)) - 6);
			}
			if(weatherType == 2){
				mat4 rainScale = another;rainScale = scale(rainScale, vec3(0.35, 2, 0.35));
				this->rain2->Draw(projection, rainScale, size, 0);
			}
			else{this->snow2->Draw(projection, another, size, current_timeDisplay+i);}
		}
	}

	if (this->GLReturnedError("Precip::Draw - on exit"))
		return;
}
