/*
Name: Clayton Suplinski
Project: First-Person Shooter
*/

#pragma once
#include "object.h"
#include "shader.h"
#include "cylinder.h"
#include "square4.h"

using namespace std;
using namespace glm;

class Jumbotron : public Object
{
public:
	Jumbotron();
	~Jumbotron();
	virtual bool Initialize();
	virtual void Draw(const glm::mat4& projection, glm::mat4 modelview, const glm::ivec2 & size, const float time = 0);
	void TakeDown();

	Cylinder * base;
	Square4 * screen;
	GLuint fboID;

private:
	typedef Object super;
};