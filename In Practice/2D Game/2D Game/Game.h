#ifndef GAME_H
#define GAME_H

#include <GLEW/glew.h>
#include <GLFW/glfw3.h>

#include "Game_level.h"

enum GameState
{
	GAME_ACTIVE,
	GAME_MENU,
	GAME_WIN
};

const glm::vec2 PLAYER_SIZE(100, 20);
const GLfloat PLAYER_VELOCITY(500.0f);

class Game
{
public:
	Game(GLuint width, GLuint height);
	~Game();

public:
	void Init();
	void ProcessInput(GLfloat dt);
	void Update(GLfloat dt);
	void Render();

public:
	GameState State;
	GLboolean Keys[1024];
	GLuint    Width;
	GLuint    Height;
	std::vector<GameLevel> Levels;
	GLuint    Level;
};

#endif //GAME_H