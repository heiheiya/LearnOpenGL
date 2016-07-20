#ifndef GAME_LEVEL_H
#define GAME_LEVEL_H

#include <vector>

#include <GLEW/glew.h>
#include <glm/glm.hpp>

#include "Game_object.h"
#include "Sprite_renderer.h"
#include "Resource_manager.h"

class GameLevel
{
public:
	GameLevel(){}

public:
	void Load(const GLchar* file, GLuint levelWidth, GLuint levelHeight);
	void Draw(SpriteRenderer& renderer);
	GLboolean IsCompleted();

private:
	void Init(std::vector<std::vector<GLuint>> tileData, GLuint levelWidth, GLuint levelHeight);

private:
	std::vector<GameObject> Bricks;
};

#endif //GAME_LEVEL_H