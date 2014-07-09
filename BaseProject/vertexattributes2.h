/*
Name: Clayton Suplinski
Project: First-Person Shooter
*/

#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class VertexAttributes
{
public:
	VertexAttributes();
	VertexAttributes(const glm::vec3 & p, const glm::vec3 & c, const glm::vec3 & n, const glm::vec2 & t);
	VertexAttributes(const VertexAttributes & other);
	glm::vec3 position;
	glm::vec3 color;
	glm::vec3 normal;
	glm::vec2 texture_coordinate;
};
