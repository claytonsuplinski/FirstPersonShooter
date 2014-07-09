/*
Name: Clayton Suplinski
Project: First-Person Shooter

A simple obj loader

Note: all slashes must be removed from the faces lines
*/

#pragma once
#include "object2.h"
#include "shader2.h"
#include "texturedshader.h"
#include "TextureManager.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;
using namespace glm;

class Gengar : public Object2
{
public:
	Gengar();
	virtual bool Initialize(const char * objName, const char * jpgName, char* v, char* f);
	virtual void Draw(const mat4& projection, mat4 modelview, const ivec2 & size, const float time = 0);
	void TakeDown();
	char * filename;
	unsigned int texID;
	int order;

	vector<vec4> gengar_vertices;
	vector<vec3> gengar_normals;
	vector<vec2> gengar_textures;
	vector<GLushort> gengar_faces;

private:
	typedef Object2 super;

	TexturedShader basic_texture_shader;
};