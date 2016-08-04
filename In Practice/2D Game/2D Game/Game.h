#ifndef GAME_H
#define GAME_H

#include <vector>
#include <tuple>

#include <GLEW/glew.h>
#include <GLFW/glfw3.h>

#include "Game_level.h"
#include "Game_object.h"
#include "Ball_object.h"
#include "Power_up.h"

enum GameState
{
	GAME_ACTIVE,
	GAME_MENU,
	GAME_WIN
};

enum Direction
{
    UP,
    RIGHT,
    DOWN,
    LEFT
};

typedef std::tuple<GLboolean, Direction, glm::vec2> Collision;

const glm::vec2 PLAYER_SIZE(100, 20);
const GLfloat PLAYER_VELOCITY(500.0f);
const glm::vec2 INITIAL_BALL_VELOCITY(100.0f, -350.0f);
const GLfloat BALL_RADIUS = 12.5f;

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
	void DoCollisions();
    void ResetLevel();
    void ResetPlayer();
	void SpawnPowerUps(GameObject& block);
	void UpdatePowerUps(GLfloat dt);

private:
	GLboolean CheckCollision(GameObject& one, GameObject& two);
	Collision CheckCollision(BallObject& one, GameObject& two);
    Direction VectorDirection(glm::vec2 target);
	GLboolean ShouldSpawn(GLuint chance);
	void ActivatePowerUp(PowerUp& powerUp);
	GLboolean IsOtherPowerUpActive(std::vector<PowerUp> &powerUps, std::string type);

public:
	GameState              State;
	GLboolean              Keys[1024];
	GLuint                 Width;
	GLuint                 Height;
	std::vector<GameLevel> Levels;
	GLuint                 Level;
	std::vector<PowerUp>   PowerUps;
	GLuint                 Lives;
	GLboolean              KeysProcessed[1024];
};

#endif //GAME_H