/*
Name: Clayton Suplinski
Project: First-Person Shooter
*/

#pragma once
#include "object.h"
#include "shader.h"
#include "sphere.h"
#include "snow.h"
#include <vector>

using namespace std;
using namespace glm;

class Precip : public Object
{
public:
	Precip();
	virtual bool Initialize();
	virtual void Draw(const glm::mat4& projection, glm::mat4 modelview, const glm::ivec2 & size, const float radius);
	void TakeDown();
	void increasePrecip(int amount);
	void decreasePrecip(int amount);
	vec3 color;

	Sphere * rain2;
	Snow * snow2;

	static const int maxParts = 1000;
	static const int minParts = 0;

	//Retrieve from main
	int weatherType;
	float movingWRTSnow;
	float RotatedY;

	int numParts;
	vector<float> partX;
	vector<float> partY;
	vector<float> partOffset;

private:
	typedef Object super;
};