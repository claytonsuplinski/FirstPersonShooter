/*
Name: Clayton Suplinski
ID: 906 580 2630
CS 559 Project 3

Creates a general textured object
-Taken from demo code
*/

/*	Perry Kivolowitz - University of Wisconsin - Madison 
	Computer Sciences Department

	A sample hello world like program demonstrating modern
	OpenGL techniques. 

	Object() is a sample base class upon which drawable objects might
	be derived. It assumes that all drawable objects have some geometry
	to buffer.

	Created:	2/25/13
*/

#include <iostream>
#include <assert.h>
#include "object2.h"

using namespace std;

/*	Notice the destructor in this case asserts that all resources
	that don't go away by themselves have ALREADY been released. This
	is because the destructor might be called after a GL context has
	been destroyed, so I force the user of this class to call the
	TakeDown() purposefully.
*/

Object2::Object2()
{
	this->InternalInitialize();
}

Object2::~Object2()
{
	assert(this->vertex_array_handle == GLuint(-1));
	assert(this->vertex_coordinate_handle == GLuint(-1));
}

//Initialize the buffer and vertex array for the object
bool Object2::PostGLInitialize(GLuint * vertex_array_handle, GLuint * vertex_coordinate_handle, GLsizeiptr sz, const GLvoid * ptr)
{
	glGenVertexArrays(1, vertex_array_handle);
	glBindVertexArray(*vertex_array_handle);
	glGenBuffers(1, vertex_coordinate_handle);
	glBindBuffer(GL_ARRAY_BUFFER, *vertex_coordinate_handle);
	glBufferData(GL_ARRAY_BUFFER, sz, ptr, GL_STATIC_DRAW);
	return !this->GLReturnedError("Object::PostGLInitialize - on exit");
}

void Object2::TakeDown()
{
	if (this->vertex_array_handle != GLuint(-1))
		glDeleteVertexArrays(1, &this->vertex_array_handle);

	if (this->vertex_coordinate_handle != GLuint(-1))
		glDeleteBuffers(1, &this->vertex_coordinate_handle);

	this->InternalInitialize();
}

bool Object2::Initialize()
{
	this->InternalInitialize();
	return true;
}

void Object2::InternalInitialize()
{
	this->vertex_array_handle = this->vertex_coordinate_handle = GLuint(-1);
}

bool Object2::GLReturnedError(char * s)
{
	bool return_error = false;
#ifdef _DEBUG
	GLenum glerror;

	while ((glerror = glGetError()) != GL_NO_ERROR)
	{
		return_error = true;
		cerr << s << ": " << gluErrorString(glerror) << endl;
	}
#endif
	return return_error;
}

