/*
Name: Clayton Suplinski
Project: First-Person Shooter
*/

#include "shader.h"
#include <assert.h>

#define BAD_GL_VALUE GLuint(-1)

Shader::Shader()
{
	this->vertex_shader_id = BAD_GL_VALUE;
	this->fragment_shader_id = BAD_GL_VALUE;
	this->program_id = BAD_GL_VALUE;
	this->modelview_matrix_handle = BAD_GL_VALUE;
	this->projection_matrix_handle = BAD_GL_VALUE;
	this->normal_matrix_handle = BAD_GL_VALUE;
	this->red_handle = BAD_GL_VALUE;
	this->green_handle = BAD_GL_VALUE;
	this->blue_handle = BAD_GL_VALUE;
	this->alpha_handle = BAD_GL_VALUE;
	this->size_handle = BAD_GL_VALUE;
}

void Shader::CommonSetup(const float time, const GLint * size, const GLfloat * projection, const GLfloat * modelview, const GLfloat * mvp, const GLfloat * nm)
{
	glUniform1f(this->time_handle, time);
	glUniform2iv(this->size_handle, 1, size);
	glUniformMatrix4fv(this->projection_matrix_handle, 1, GL_FALSE, projection);
	glUniformMatrix4fv(this->modelview_matrix_handle, 1, GL_FALSE, modelview);
	glUniformMatrix4fv(this->mvp_handle, 1, GL_FALSE, mvp);
	glUniformMatrix3fv(this->normal_matrix_handle, 1, GL_FALSE, nm);

}

void Shader::Use()
{
	assert(this->program_id != BAD_GL_VALUE);
	glUseProgram(this->program_id);
}

bool Shader::Initialize(char * vertex_shader_file, char * fragment_shader_file)
{
	GLint check_value;

	if (GLReturnedError("Shader::Initialize - on entrance"))
		return false;

	this->vertex_shader_id = glCreateShader(GL_VERTEX_SHADER);
	this->LoadShader(vertex_shader_file, this->vertex_shader_id);
	glCompileShader(this->vertex_shader_id);
	glGetShaderiv(this->vertex_shader_id, GL_COMPILE_STATUS, &check_value);
	if (check_value != GL_TRUE)
	{
		cerr << this->GetShaderLog(vertex_shader_id).str();
		cerr << "GLSL compilation failed - vertex shader: " << vertex_shader_file << endl;
		return false;
	}

	if (GLReturnedError("Shader::Initialize - after processing vertex shader"))
		return false;

	this->fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);
	this->LoadShader(fragment_shader_file, this->fragment_shader_id);
	glCompileShader(this->fragment_shader_id);
	glGetShaderiv(this->fragment_shader_id, GL_COMPILE_STATUS, &check_value);
	if (check_value != GL_TRUE)
	{
		cerr << this->GetShaderLog(fragment_shader_id).str();
		cerr << "GLSL compilation failed - fragment shader: " << fragment_shader_file << endl;
		return false;
	}

	this->program_id = glCreateProgram();
	glAttachShader(this->program_id, this->vertex_shader_id);
	glAttachShader(this->program_id, this->fragment_shader_id);
	glLinkProgram(program_id);

	glDeleteShader(vertex_shader_id);
	glDeleteShader(fragment_shader_id);

	glUseProgram(this->program_id);

	this->modelview_matrix_handle = glGetUniformLocation(this->program_id, (const GLchar *) "modelview_matrix");
	this->projection_matrix_handle = glGetUniformLocation(this->program_id, (const GLchar *) "projection_matrix");
	this->normal_matrix_handle = glGetUniformLocation(this->program_id, (const GLchar *) "normal_matrix");
	this->mvp_handle = glGetUniformLocation(this->program_id, (const GLchar *) "mvp");
	this->size_handle = glGetUniformLocation(this->program_id, (const GLchar *) "size");
	this->time_handle = glGetUniformLocation(this->program_id, (const GLchar *) "time");
	this->red_handle = glGetUniformLocation(this->program_id, (const GLchar *) "red");
	this->green_handle = glGetUniformLocation(this->program_id, (const GLchar *) "green");
	this->blue_handle = glGetUniformLocation(this->program_id, (const GLchar *) "blue");
	this->alpha_handle = glGetUniformLocation(this->program_id, (const GLchar *) "alpha");

	glUseProgram(0);

	return !GLReturnedError("Shader::Initialize - on exit");
}

//If we want to change the color of the object dynamically
void Shader::CustomSetup(vec3 color)
{
	glUniform1f(this->red_handle, color.x);
	glUniform1f(this->green_handle, color.y);
	glUniform1f(this->blue_handle, color.z);
}

//If we want to change the color and opacity of the object dynamically
void Shader::CustomSetup2(vec4 color)
{
	glUniform1f(this->red_handle, color.x);
	glUniform1f(this->green_handle, color.y);
	glUniform1f(this->blue_handle, color.z);
	glUniform1f(this->alpha_handle, color.a);
}


void Shader::TakeDown()
{
	GLint temp;
	GLsizei size;

	if (this->program_id == (GLuint) -1)
		return;

	glGetProgramiv(this->program_id, GL_ATTACHED_SHADERS, &temp);
	if (temp > 0)
	{
		GLuint * shader_list = new GLuint[temp];
		glGetAttachedShaders(this->program_id, temp, &size, shader_list);
		for (GLsizei i = 0; i < size; i++)
		{
			glDetachShader(this->program_id, shader_list[i]);
		}
		delete [] shader_list;
	}

	glDeleteProgram(this->program_id);
	this->program_id = (GLuint) -1;
}

bool Shader::LoadShader(const char * file_name, GLuint shader_id)
{
	assert(file_name != NULL);
	if (GLReturnedError("Shader::LoadShader - on entrance"))
		return false;

	FILE * file_handle = NULL;
	fopen_s(&file_handle, file_name, "rb");
	if (file_handle == NULL)
	{
		cerr <<  "Cannot open shader: " << file_name << endl;
		return false;
	}
	fseek(file_handle, 0, SEEK_END);
	int length = ftell(file_handle);
	fseek(file_handle, 0, SEEK_SET);
	GLubyte * buffer = new GLubyte[length + 1];
	fread(buffer, sizeof(GLubyte), length, file_handle);
	fclose(file_handle);
	buffer[length] = 0;
	glShaderSource(shader_id, 1, (const char **) &buffer, NULL);
	delete [] buffer;

	return !GLReturnedError("Shader::LoadShader - on exit");
}

stringstream Shader::GetShaderLog(GLuint shader_id)
{
	stringstream s;
	GLint log_length;
	glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &log_length);
	if (log_length <= 0)
		s << "No shader log information available." << endl;
	else
	{
		GLchar * buffer = new GLchar[log_length];
		glGetShaderInfoLog(shader_id, log_length, NULL, buffer);
		s << "Shader log:" << endl;
		s << buffer << endl;
		delete [] buffer;
	}
	return s;
}

bool Shader::GLReturnedError(char * s)
{
	bool return_error = false;
	GLenum glerror;

	while ((glerror = glGetError()) != GL_NO_ERROR)
	{
		return_error = true;
		cerr << s << ": " << gluErrorString(glerror) << endl;
	}

	return return_error;
}

BackgroundShader::BackgroundShader() : super()
{
	this->color_array_handle = BAD_GL_VALUE;
}

bool BackgroundShader::Initialize(char * vertex_shader_file, char * fragment_shader_file)
{
	if (!super::Initialize(vertex_shader_file, fragment_shader_file))
		return false;

	this->Use();
	this->color_array_handle = glGetUniformLocation(this->program_id, (const GLchar *) "color_array");
	glUseProgram(0);
	return true;
}

void BackgroundShader::CustomSetup(vec4 * color_array)
{
	glUniform4fv(this->color_array_handle, 4, (GLfloat *) color_array);
}
