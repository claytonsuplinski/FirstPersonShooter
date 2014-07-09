/*
Name: Clayton Suplinski
Project: First-Person Shooter
*/

#pragma once
#include "object.h"
#include "shader.h"
#include "sphere.h"

using namespace std;
using namespace glm;

class Bullet : public Object
{
public:
	Bullet();
	~Bullet();
	virtual bool Initialize(vec3 color);
	virtual void Draw(const mat4& projection, mat4 modelview, const ivec2 & size, const float time = 0);
	void TakeDown();
	void StepShader();
	Shader shader;
	float dist(float x1, float y1, float z1, float x2, float y2, float z2);

	Sphere * bullet;

	float velocityFactor;
	int distance;

	int teamNo;
	int userNo;

	//Get from team class
	float rotY;
	bool isDrawing;
	vec3 startPos;
	vec3 currPos;
	vec3 endPos;
	bool doneDrawing;

	float distFromUser;	

private:
	typedef Object super;
};