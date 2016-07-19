#ifndef SPRITE_RENDERER_H
#define SPRITE_RENDERER_H

#include <GLEW/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Texture.h"
#include "Shader.h"

class SpriteRenderer
{
public:
	SpriteRenderer(Shader& shader);
	~SpriteRenderer();

public:
	void DrawSprite(Texture2D& texture, glm::vec2 position, glm::vec2 size = glm::vec2(10, 10), GLfloat rotate = 0.0f, glm::vec3 color = glm::vec3(1.0f));

private:
	void initRenderData();

private:
	Shader shader;
	GLuint quadVAO;
};

#endif //SPRITE_RENDERER_H