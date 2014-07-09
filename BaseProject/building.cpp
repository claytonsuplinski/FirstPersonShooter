/*
Name: Clayton Suplinski
Project: First-Person Shooter
*/

#include "building.h"

Building::Building() : Object(){
}

Building::~Building(){}

//Initialize all the different buildings (depending on the environment)
bool Building::Initialize(vec3 color, vec3 dim, vec3 pos, int environment)
{
	if (this->GLReturnedError("Building::Initialize - on entry"))
		return false;

	this->pos = pos;
	rotation = 0;
	buildingType = 0;
	scaler = 1;
	environmentNumber = environment;

	if(environment == 0){
	statueSoldier = new PersonFixed();
	statueSoldier->Initialize("basic_texture_shader.vert", "basic_texture_shader.frag");

	statue = new Gengar();
	statue->order=1;
	statue->Initialize("./models/statue.obj", "./models/statue.png", "basic_texture_shader.vert", "basic_texture_shader.frag");

	pool = new Gengar();
	pool->order=1;
	pool->Initialize("./models/pool.obj", "./models/pool.png", "basic_texture_shader.vert", "basic_texture_shader.frag");

	building1 = new Gengar();
	building1->order=1;
	building1->Initialize("./models/building1.obj", "./models/building1.png", "basic_texture_shader.vert", "basic_texture_shader.frag");

	building2 = new Gengar();
	building2->order=1;
	building2->Initialize("./models/building2.obj", "./models/building2.png", "basic_texture_shader.vert", "basic_texture_shader.frag");

	building3 = new Gengar();
	building3->order=1;
	building3->Initialize("./models/building3.obj", "./models/building3.png", "basic_texture_shader.vert", "basic_texture_shader.frag");

	building4 = new Gengar();
	building4->order=1;
	building4->Initialize("./models/building4.obj", "./models/building4.png", "basic_texture_shader.vert", "basic_texture_shader.frag");

	building5 = new Gengar();
	building5->order=1;
	building5->Initialize("./models/building5.obj", "./models/building5.png", "basic_texture_shader.vert", "basic_texture_shader.frag");

	arch = new Gengar();
	arch->order=1;
	arch->Initialize("./models/arch.obj", "./models/arch.png", "basic_texture_shader.vert", "basic_texture_shader.frag");
	}
	else if(environment == 1){

	river = new Gengar();
	river->order=1;
	river->Initialize("./models/river.obj", "./models/river.png", "basic_texture_shader.vert", "basic_texture_shader.frag");

	fern = new Gengar();
	fern->order=1;
	fern->Initialize("./models/fern.obj", "./models/fern.png", "basic_texture_shader.vert", "basic_texture_shader.frag");

	pineTree = new Gengar();
	pineTree->order=1;
	pineTree->Initialize("./models/pineTree.obj", "./models/pineTree.png", "basic_texture_shader.vert", "basic_texture_shader.frag");

	rockWall = new Gengar();
	rockWall->order=1;
	rockWall->Initialize("./models/rockWall.obj", "./models/rockWall.png", "basic_texture_shader.vert", "basic_texture_shader.frag");

	treeArch = new Gengar();
	treeArch->order=1;
	treeArch->Initialize("./models/treeArch.obj", "./models/treeArch.png", "basic_texture_shader.vert", "basic_texture_shader.frag");

	statueSoldier = new PersonFixed();
	statueSoldier->Initialize("basic_texture_shader.vert", "basic_texture_shader2.frag");

	statue = new Gengar();
	statue->order=1;
	statue->Initialize("./models/statue.obj", "./models/statue.png", "basic_texture_shader.vert", "basic_texture_shader.frag");

	}
	else if(environment == 2){

	statueSoldier = new PersonFixed();
	statueSoldier->Initialize("basic_texture_shader.vert", "basic_texture_shader2.frag");

	statue = new Gengar();
	statue->order=1;
	statue->Initialize("./models/statue.obj", "./models/statue.png", "basic_texture_shader.vert", "basic_texture_shader.frag");

	pyramid = new Gengar();
	pyramid->order=1;
	pyramid->Initialize("./models/meteosat.obj", "./models/meteosat10.png", "basic_texture_shader.vert", "basic_texture_shader.frag");

	}
	else if(environment == 3){

	statueSoldier = new PersonFixed();
	statueSoldier->Initialize("basic_texture_shader.vert", "basic_texture_shader2.frag");

	statue = new Gengar();
	statue->order=1;
	statue->Initialize("./models/statue.obj", "./models/statue.png", "basic_texture_shader.vert", "basic_texture_shader.frag");

	volcano = new Gengar();
	volcano->order=1;
	volcano->Initialize("./models/volcano.obj", "./models/statue.png", "basic_texture_shader.vert", "basic_texture_shader.frag");

	}
	else if(environment == 4){

	statueSoldier = new PersonFixed();
	statueSoldier->Initialize("basic_texture_shader.vert", "basic_texture_shader2.frag");

	statue = new Gengar();
	statue->order=1;
	statue->Initialize("./models/statue.obj", "./models/statue.png", "basic_texture_shader.vert", "basic_texture_shader.frag");

	cave = new Gengar();
	cave->order=1;
	cave->Initialize("./models/cave.obj", "./models/cave.png", "basic_texture_shader.vert", "basic_texture_shader.frag");

	}
	
	if (this->GLReturnedError("Building::Initialize - on exit"))
		return false;

	return true;
}

void Building::TakeDown()
{
	if(environmentNumber == 0){
	statueSoldier->TakeDown();
	statue->TakeDown();
	pool->TakeDown();
	building1->TakeDown();
	building2->TakeDown();
	building3->TakeDown();
	building4->TakeDown();
	building5->TakeDown();
	arch->TakeDown();
	}
	else if(environmentNumber == 1){
	river->TakeDown();
	fern->TakeDown();
	pineTree->TakeDown();
	rockWall->TakeDown();
	treeArch->TakeDown();
	statueSoldier->TakeDown();
	statue->TakeDown();
	}
	else if(environmentNumber == 2){
	statueSoldier->TakeDown();
	statue->TakeDown();
	pyramid->TakeDown();
	}
	else if(environmentNumber == 3){
	statueSoldier->TakeDown();
	statue->TakeDown();
	volcano->TakeDown();
	}
	else if(environmentNumber == 4){
	statueSoldier->TakeDown();
	statue->TakeDown();
	cave->TakeDown();
	}

	this->shader.TakeDown();
	super::TakeDown();	
}

void Building::Draw(const mat4 & projection, mat4 modelview, const ivec2 & size, const float rotY)
{

	if (this->GLReturnedError("Building ::Draw - on entry")){
		cout << "building " << buildingType << endl;
		return;	
	}

	glEnable(GL_DEPTH_TEST);
	mat4 another, statueBaseMat;
	another = modelview;

	if(distFromUser < 550){
		another = rotate(another, rotation, vec3(0,1,0));
		switch(buildingType){
		case -2:
			another = scale(another, vec3(1,0.2,1));
			pool->Draw(projection, another, size, 0);
			break;
		case -1:
			statueBaseMat = another;
			statueBaseMat = scale(statueBaseMat, vec3(1,0.5,1));
			statue->Draw(projection, statueBaseMat, size, 0);
			another = translate(another, vec3(0,14,0));
			another = scale(another, vec3(10,10,10));
			statueSoldier->Draw(projection, another, size, 0);
			break;
		case 0:
			arch->Draw(projection, another, size, 0);
			break;
		case 1:
			another = scale(another, vec3(scaler, scaler, scaler));
			building1->Draw(projection, another, size, 0);
			break;
		case 2:
			another = scale(another, vec3(scaler, scaler, scaler));
			building2->Draw(projection, another, size, 0);
			break;
		case 3:
			another = scale(another, vec3(scaler, scaler, scaler));
			building3->Draw(projection, another, size, 0);
			break;
		case 4:
			another = scale(another, vec3(scaler, scaler, scaler));
			building4->Draw(projection, another, size, 0);
			break;
		case 5:
			another = scale(another, vec3(scaler, scaler, scaler));
			building5->Draw(projection, another, size, 0);
			break;
		case 100:
			glDisable(GL_CULL_FACE);
			another = scale(another, dimensions);
			river->Draw(projection, another, size, 0);
			glEnable(GL_CULL_FACE);
			break;
		case 101:
			statueBaseMat = another;
			statueBaseMat = scale(statueBaseMat, vec3(1,0.5,1));
			statue->Draw(projection, statueBaseMat, size, 0);
			another = translate(another, vec3(0,14,0));
			another = scale(another, vec3(10,10,10));
			statueSoldier->Draw(projection, another, size, 5);
			break;
		case 102:
			glDisable(GL_CULL_FACE);
			another = translate(another, vec3(0,-1,0));
			another = scale(another, vec3(0.4, 0.4, 0.4));
			fern->Draw(projection, another, size, 0);
			glEnable(GL_CULL_FACE);
			break;
		case 103:
			pineTree->Draw(projection, another, size, 0);
			break;
		case 104:
			rockWall->Draw(projection, another, size, 0);
			break;
		case 105:
			glDisable(GL_CULL_FACE);
			//another = translate(another, vec3(0,4,0));
			another = scale(another, vec3(1,0.5,1));
			treeArch->Draw(projection, another, size, 0);
			glEnable(GL_CULL_FACE);
			break;
		case 200:
			statueBaseMat = another;
			statueBaseMat = scale(statueBaseMat, vec3(1,0.5,1));
			statue->Draw(projection, statueBaseMat, size, 0);
			another = translate(another, vec3(0,14,0));
			another = scale(another, vec3(10,10,10));
			statueSoldier->Draw(projection, another, size, 2.5);
			break;
		case 201:
			glDisable(GL_CULL_FACE);
			another = scale(another, dimensions);
			pyramid->Draw(projection, another, size, 0);
			glEnable(GL_CULL_FACE);
			break;
		case 300:
			statueBaseMat = another;
			statueBaseMat = scale(statueBaseMat, vec3(1,0.5,1));
			statue->Draw(projection, statueBaseMat, size, 0);
			another = translate(another, vec3(0,14,0));
			another = scale(another, vec3(10,10,10));
			statueSoldier->Draw(projection, another, size, 0);
			break;
		case 301:
			glDisable(GL_CULL_FACE);
			another = scale(another, vec3(1,0.5,1));
			volcano->Draw(projection, another, size, 0);
			glEnable(GL_CULL_FACE);
			break;
		case 400:
			statueBaseMat = another;
			statueBaseMat = scale(statueBaseMat, vec3(1,0.5,1));
			statue->Draw(projection, statueBaseMat, size, 0);
			another = translate(another, vec3(0,14,0));
			another = scale(another, vec3(10,10,10));
			statueSoldier->Draw(projection, another, size, 7.5);
			break;
		case 401:
			glDisable(GL_CULL_FACE);
			//another = scale(another, vec3(1,0.5,1));
			cave->Draw(projection, another, size, 0);
			glEnable(GL_CULL_FACE);
			break;
		default:
			statue->Draw(projection, another, size, 0);
			break;
		}
	}

	if (this->GLReturnedError("Building::Draw - on exit")){
		cout << "building " << buildingType << endl;
		return;
	}
}
