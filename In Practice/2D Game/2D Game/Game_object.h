#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <GLEW/glew.h>
#include <glm/glm.hpp>

#include "Texture.h"
#include "Sprite_renderer.h"

class GameObject
{
public:
	GameObject();
	GameObject(glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec3 color = glm::vec3(1.0f), glm::vec2 velocity = glm::vec2(0.0f, 0.0f));

public:
	virtual void Draw(SpriteRenderer& renderer);

public:
	glm::vec2 Position;
	glm::vec2 Size;
	glm::vec2 Velocity;
	glm::vec3 Color;
	GLfloat   Rotation;
	GLboolean IsSolid;
	GLboolean Destroyed;
	Texture2D Sprite;
};

#endif //GAME_OBJECT_H