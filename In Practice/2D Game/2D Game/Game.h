#ifndef GAME_H
#define GAME_H

#include <GLEW/glew.h>
#include <GLFW/glfw3.h>

enum GameState
{
	GAME_ACTIVE,
	GAME_MENU,
	GAME_WIN
};

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
};

#endif //GAME_H