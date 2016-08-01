#ifndef POST_PROCESSOR_H
#define POST_PROCESSOR_H

#include <GLEW/glew.h>
#include <glm/glm.hpp>

#include "Texture.h"
#include "Sprite_renderer.h"
#include "Shader.h"

class PostProcessor
{
public:
	PostProcessor(Shader shader, GLuint width, GLuint height);
	
public:
	void BeginRender();
	void EndRender();
	void Render(GLfloat time);

private:
	void InitRenderData();

public:
	Shader PostProcessingShader;
	Texture2D Texture;
	GLuint Width;
	GLuint Height;
	GLboolean Confuse;
	GLboolean Chaos;
	GLboolean Shake;

private:
	GLuint MSFBO;
	GLuint FBO;
	GLuint RBO;
	GLuint VAO;
};

#endif //POST_PROCESSOR_H