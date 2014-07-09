/*
Name: Clayton Suplinski
Project: First-Person Shooter
*/

#include "menu.h"

Menu::Menu(){
}

Menu::~Menu(){}

bool Menu::Initialize(){
	menuOn = true;

	menuLevel = 0;

	titles.clear();
	titles.push_back("Main Menu");
	
	//ADD_STADIUM//
	lines.clear();
	lines.push_back("(1) City");
	lines.push_back("(2) Forest");
	lines.push_back("(3) Desert");
	lines.push_back("(4) Volcano");
	lines.push_back("(5) Cave");
	/*lines.push_back("(3) Capture the Flag");
	lines.push_back("(4) Survival");
	lines.push_back("(5) Settings");*/

	FIRST_PERSON_EYE = vec3(0.0f, 0.5, -2);
	FIRST_PERSON_CENTER = vec3(0.0f, 0.5f, -3.0f);
	THIRD_PERSON_EYE = vec3(0.0f, 2, 10);
	THIRD_PERSON_CENTER = vec3(0.0f, 1.0f, -10.0f);


	return true;
}

void Menu::reset(){
	s.stadiumSelect = 0;

	//ADD_STADIUM//
	titles.clear();
	titles.push_back("Main Menu");
	lines.clear();
	lines.push_back("(1) City");
	lines.push_back("(2) Forest");
	lines.push_back("(3) Desert");
	lines.push_back("(4) Volcano");
	lines.push_back("(5) Cave");

	//ADD_STADIUM//
	menuOn = true;
	menuLevel = 0;
	select1 = false;
	select11 = false;
	select12 = false;
	select13 = false;
	select2 = false;
	select21 = false;
	select22 = false;
	select23 = false;
	select3 = false;
	select4 = false;
	select5 = false;
}

void Menu::Update(int input)
{
	//ADD_STADIUM//
	switch(input){
	case 1:
		if(!select1 && menuLevel == 0){ //1
			s.stadiumSelect = 1;

			titles.clear();
			titles.push_back("Perspective");
			lines.clear();
			lines.push_back("(1) 1st Person");
			lines.push_back("(2) 3rd Person");

			select1=true;			
			menuLevel=1;
		}
		else if(select1 && !select11 && menuLevel == 1){ //1 1
			s.lookAtEye = FIRST_PERSON_EYE;
			s.lookAtCenter = FIRST_PERSON_CENTER;
			select11=true;
			menuLevel=2;
			menuOn = false;
		}
		else if(select2 && !select21 && menuLevel == 1){ //2 1
			s.lookAtEye = FIRST_PERSON_EYE;
			s.lookAtCenter = FIRST_PERSON_CENTER;
			select21=true;
			menuLevel=2;
			menuOn = false;
		}
		else if((select3 || select4 || select5) && menuLevel == 1){ //3 1
			s.lookAtEye = FIRST_PERSON_EYE;
			s.lookAtCenter = FIRST_PERSON_CENTER;
			//select21=true;
			menuLevel=2;
			menuOn = false;
		}
		break;
	case 2:
		if(select1 && !select12 && menuLevel == 1){ //1 2
			s.lookAtEye = THIRD_PERSON_EYE;
			s.lookAtCenter = THIRD_PERSON_CENTER;		
			menuOn = false;

			select12=true;
			menuLevel=2;
		}
		else if(!select2 && menuLevel == 0){ //2
			s.stadiumSelect = 2;

			titles.clear();
			titles.push_back("Perspective");
			lines.clear();
			lines.push_back("(1) 1st Person");
			lines.push_back("(2) 3rd Person");

			select2=true;
			menuLevel=1;
		}
		else if(select2 && !select22 && menuLevel == 1){ //2 2
			s.lookAtEye = THIRD_PERSON_EYE;
			s.lookAtCenter = THIRD_PERSON_CENTER;		
			menuOn = false;

			select22=true;
			menuLevel=2;
		}
		else if((select3 || select4 || select5) && menuLevel == 1){ //3 2
			s.lookAtEye = THIRD_PERSON_EYE;
			s.lookAtCenter = THIRD_PERSON_CENTER;		
			menuOn = false;
		}
		break;
	case 3:
		if(!select3 && menuLevel == 0){
			s.stadiumSelect = 3;

			titles.clear();
			titles.push_back("Perspective");
			lines.clear();
			lines.push_back("(1) 1st Person");
			lines.push_back("(2) 3rd Person");

			select3 = true;
			menuLevel = 1;
		}
		break;
	case 4:
		if(!select4 && menuLevel == 0){
			s.stadiumSelect = 4;

			titles.clear();
			titles.push_back("Perspective");
			lines.clear();
			lines.push_back("(1) 1st Person");
			lines.push_back("(2) 3rd Person");

			select4 = true;
			menuLevel = 1;
		}
		break;
	case 5:
		if(!select5 && menuLevel == 0){
			s.stadiumSelect = 5;

			titles.clear();
			titles.push_back("Perspective");
			lines.clear();
			lines.push_back("(1) 1st Person");
			lines.push_back("(2) 3rd Person");

			select5 = true;
			menuLevel = 1;
		}
		break;

	}

}
