#ifndef BALL_OBJECT_H
#define BALL_OBJECT_H

#include <GLEW/glew.h>
#include <glm/glm.hpp>

#include "Texture.h"
#include "Sprite_renderer.h"
#include "Game_object.h"

class BallObject :public GameObject
{
public:
	BallObject();
	BallObject(glm::vec2 pos, GLfloat radius, glm::vec2 velocity, Texture2D sprite);

public:
	glm::vec2 Move(GLfloat dt, GLuint window_width);
	void Reset(glm::vec2 position, glm::vec2 velocity);

public:
	GLfloat   Radius;
	GLboolean Stuck;
	GLboolean Sticky;
	GLboolean PassThrough;
};

#endif //BALL_OBJECT_H