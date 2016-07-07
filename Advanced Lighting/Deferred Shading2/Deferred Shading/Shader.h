#ifndef _SHADER_H_
#define _SHADER_H_

#include <GLEW/glew.h>

using namespace std;

class Shader
{
public:
	Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
	Shader(const GLchar* vertexPath, const GLchar* geomtryPath, const GLchar* fragmentPath);
	void Use();

public:
	GLuint m_program;
};
#endif //_SHADER_H_