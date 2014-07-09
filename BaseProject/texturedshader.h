/*
Name: Clayton Suplinski
Project: First-Person Shooter
*/

#pragma once
#include "shader2.h"

class TexturedShader : public Shader2
{
public:
	TexturedShader();
	virtual bool Initialize(char * vertex_shader_file, char * fragment_shader_file);
	virtual void CustomSetup();

private:
	typedef Shader2 super;
	GLuint texture_handle;
};
