#ifndef TEXT_RENDERER_H
#define TEXT_RENDERER_H

#include <map>

#include <GLEW/glew.h>
#include <glm/glm.hpp>

#include "Texture.h"
#include "Shader.h"

struct Character
{
	GLuint TextureID;
	glm::ivec2 Size;
	glm::ivec2 Bearing;
	GLuint Advance;
};

class TextRenderer
{
public:
	TextRenderer(GLuint width, GLuint height);

public:
	void Load(std::string font, GLuint fontSize);
	void RenderText(std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color = glm::vec3(1.0f));

public:
	std::map<GLchar, Character> Characters;
	Shader TextShader;

private:
	GLuint VAO;
	GLuint VBO;
};

#endif //TEXT_RENDERER_H