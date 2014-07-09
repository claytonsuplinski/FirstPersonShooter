/*
Name: Clayton Suplinski
Project: First-Person Shooter
*/

#include "vertexattributes2.h"

using namespace glm;

VertexAttributes::VertexAttributes()
{
	this->position = vec3(0.0f);
	this->color = vec3(0.0f);
	this->normal = vec3(0.0f);
	this->texture_coordinate = vec2(0.0f);
}

VertexAttributes::VertexAttributes(const vec3 & p, const vec3 & c, const vec3 & n, const vec2 & t)
{
	this->position = p;
	this->color = c;
	this->normal = n;
	this->texture_coordinate = t;
}

VertexAttributes::VertexAttributes(const VertexAttributes & other)
{
	this->position = other.position;
	this->color = other.color;
	this->normal = other.normal;
	this->texture_coordinate = other.texture_coordinate;
}
