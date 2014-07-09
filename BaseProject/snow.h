/*
Name: Clayton Suplinski
Project: First-Person Shooter
*/

#pragma once
#include "object.h"
#include "shader.h"

using namespace std;
using namespace glm;

class Snow : public Object
{
public:
	Snow();
	virtual bool Initialize(int slices, float radius, char* v, char* f);
	virtual void Draw(const mat4& projection, mat4 modelview, const ivec2 & size, const float time = 0);
	void TakeDown();
	vec3 color;

	int shader_index;
	Shader shader;
	Shader flat_shader;
	Shader gouraud_shader;
	Shader phong_shader;
	vector<Shader *> shaders;
	inline void StepShader() {this->shader_index = ++this->shader_index % this->shaders.size();};
private:
	vector<VertexAttributesPCNT> vertices;
	typedef Object super;
};