/*
Name: Clayton Suplinski
Project: First-Person Shooter
*/

#pragma once

#include "object.h"
#include <vector>

using namespace std;
using namespace glm;

class Menu
{
public:
	Menu();
	~Menu();
	virtual bool Initialize();
	virtual void Update(int input);
	void reset();

	bool menuOn;
	int menuLevel;

	/////////////

	bool select1;

	bool select11;
	bool select12;
	bool select13;

	/////////////

	bool select2;

	bool select21;
	bool select22;
	bool select23;

	/////////////

	bool select3, select4, select5;

	vector<string> titles;
	vector<string> lines;

	vec3 FIRST_PERSON_EYE, FIRST_PERSON_CENTER, THIRD_PERSON_EYE, THIRD_PERSON_CENTER;

	struct settings{
		int stadiumSelect;
		vec3 lookAtEye;
		vec3 lookAtCenter;
	} s;

private:
	
};