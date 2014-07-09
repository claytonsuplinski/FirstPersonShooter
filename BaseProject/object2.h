/*
Name: Clayton Suplinski
Project: First-Person Shooter
*/

#pragma once
#include <vector>
#include <gl/glew.h>
#include <gl/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "vertexattributes2.h"

class Object2
{
public:
	Object2();

	virtual void TakeDown();
	virtual bool Initialize();
	virtual void Draw(const glm::mat4 & projection, glm::mat4 modelview, const glm::ivec2 & size, const float time = 0) = 0;
	virtual bool PostGLInitialize(GLuint * vertex_array_handle, GLuint * vertex_coordinate_handle, GLsizeiptr sz, const GLvoid * ptr);
	virtual ~Object2();

protected:
	GLuint vertex_coordinate_handle;
	GLuint vertex_array_handle;

	bool GLReturnedError(char * s);
	std::vector<VertexAttributes> vertices;
	std::vector<GLuint> vertex_indices;

private:
	void InternalInitialize();
};
