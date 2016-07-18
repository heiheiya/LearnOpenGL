#ifndef TEXTURE_H
#define TEXTURE_H

#include <GLEW/glew.h>

class Texture2D
{
public:
	Texture2D();

public:
	void Generate(GLuint width, GLuint height, unsigned char* data);
	void Bind() const;

public:
	GLuint ID;
	GLuint Width;
	GLuint Height;
	GLuint Internal_Format;
	GLuint Image_Format;
	GLuint Wrap_S;
	GLuint Wrap_T;
	GLuint Filter_Min;
	GLuint Filter_Max;
};

#endif //TEXTURE_H