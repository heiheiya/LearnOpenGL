#ifndef _SHADER_H_
#define _SHADER_H_

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <GLEW/glew.h>

using namespace std;

class Shader
{
public:
	Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
	void Use();

public:
	GLuint m_program;
};
#endif //_SHADER_H_