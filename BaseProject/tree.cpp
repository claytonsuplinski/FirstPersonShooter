/*
Name: Clayton Suplinski
ID: 906 580 2630
CS 559 Project 3

Creates a shark object out of basic shapes.
*/

#include <iostream>
#include "tree.h"

using namespace std;
using namespace glm;

//Create a Shark object
Tree::Tree() : Object(){
}

Tree::~Tree(){this->TakeDown();}

//Initialize all the Shark elements.
bool Tree::Initialize()
{
	if (this->GLReturnedError("Tree::Initialize - on entry"))
		return false;

	this->pos = pos;
	int randBranch = (int)(rand());

	this->treeTrunk = new Cylinder2();
	this->treeLeaves = new Sphere2();

	this->treeTrunk->Initialize(1, 1, 0.5, 0.5, "./textures/treeBark.png", "basic_texture_shader.vert", "basic_texture_shader.frag");
	this->treeLeaves->Initialize(2, 0.5, "./textures/leaves.png", "basic_texture_shader.vert", "basic_texture_shader.frag");

	if (this->GLReturnedError("Tree::Initialize - on exit"))
		return false;

	return true;
}

//Delete the Shark elements.
void Tree::TakeDown()
{
	this->shader.TakeDown();
	super::TakeDown();	
}

//Draw and position the Shark elements.
void Tree::Draw(const mat4 & projection, mat4 modelview, const ivec2 & size, const float rotY)
{
	if (this->GLReturnedError("Tree::Draw - on entry"))
		return;

	glEnable(GL_DEPTH_TEST);

	mat4 treeMat;
	treeMat = translate(modelview, pos);
	treeMat = scale(treeMat, vec3(radius,height, radius));
	this->treeTrunk->Draw(projection, treeMat, size, 0);
	treeMat = translate(modelview, vec3(pos.x,height, pos.z));
	treeMat = scale(treeMat, vec3(height,height/2, height));
	this->treeLeaves->Draw(projection, treeMat, size, rotY);
	treeMat = translate(modelview, vec3(pos.x,height/(randBranch%2? 2 : 3), pos.z));
	treeMat = scale(treeMat, vec3(height/2,height/2, height/2));
	this->treeLeaves->Draw(projection, treeMat, size, rotY);

	if (this->GLReturnedError("Tree::Draw - on exit"))
		return;
}
