/*
Name: Clayton Suplinski
Project: First-Person Shooter
*/

#pragma once
#include "object.h"
#include "square3.h"

using namespace std;
using namespace glm;

class Impostor : public Object
{
public:
	Impostor();
	~Impostor();
	virtual bool Initialize(char * filename);
	virtual void Draw(const glm::mat4& projection, glm::mat4 modelview, const glm::ivec2 & size, const float time = 0);
	void TakeDown();

	Square3 * square;
	float squareSize;

	vec3 impostorPos;
	vec3 userPos;

private:
	typedef Object super;
};