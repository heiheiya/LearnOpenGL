#include "Game.h"

#include "Resource_manager.h"
#include "Sprite_renderer.h"
#include "Game_object.h"
#include "Ball_object.h"

const glm::vec2 INITIAL_BALL_VELOCITY(100.0f, -350.0f);
const GLfloat BALL_RADIUS = 12.5f;

SpriteRenderer *Renderer;
GameObject     *Player;
BallObject     *Ball;


Game::Game(GLuint width, GLuint height)
	:State(GAME_ACTIVE),
	Keys(),
	Width(width),
	Height(height)
{

}

Game::~Game()
{
	delete Renderer;
	delete Player;
}

void Game::Init()
{
	ResourceManager::LoadShader("shaders/sprite.vs", "shaders/sprite.frag", nullptr, "sprite");

	glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(this->Width), static_cast<GLfloat>(this->Height), 0.0f, -1.0f, 1.0f);

	ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
	ResourceManager::GetShader("sprite").Use().SetMatrix4("projection", projection);

	ResourceManager::LoadTexture("textures/background.jpg", GL_FALSE, "background");
	ResourceManager::LoadTexture("textures/awesomeface.png", GL_TRUE, "face");
	ResourceManager::LoadTexture("textures/block.png", GL_FALSE, "block");
	ResourceManager::LoadTexture("textures/block_solid.png", GL_FALSE, "block_solid");
	ResourceManager::LoadTexture("textures/paddle.png", GL_TRUE, "paddle");

	Renderer = new SpriteRenderer(ResourceManager::GetShader("sprite"));

	GameLevel one;
	one.Load("levels/one.lvl", this->Width, this->Height * 0.5);
	GameLevel two;
	two.Load("levels/two.lvl", this->Width, this->Height * 0.5);
	GameLevel three;
	three.Load("levels/three.lvl", this->Width, this->Height * 0.5);
	GameLevel four;
	four.Load("levels/four.lvl", this->Width, this->Height * 0.5);
	this->Levels.push_back(one);
	this->Levels.push_back(two);
	this->Levels.push_back(three);
	this->Levels.push_back(four);
	this->Level = 0;

	glm::vec2 playerPos = glm::vec2(this->Width / 2 - PLAYER_SIZE.x / 2, this->Height - PLAYER_SIZE.y);
	Player = new GameObject(playerPos, PLAYER_SIZE, ResourceManager::GetTexture("paddle"));

	glm::vec2 ballPos = playerPos + glm::vec2(PLAYER_SIZE.x / 2 - BALL_RADIUS, -BALL_RADIUS * 2);
	Ball = new BallObject(ballPos, BALL_RADIUS, INITIAL_BALL_VELOCITY, ResourceManager::GetTexture("face"));
}

void Game::ProcessInput(GLfloat dt)
{
	if (this->State == GAME_ACTIVE)
	{
		GLfloat velocity = PLAYER_VELOCITY * dt;
		if (this->Keys[GLFW_KEY_A])
		{
			if (Player->Position.x >= 0)
			{
				Player->Position.x -= velocity;
				if (Ball->Stuck)
				{
					Ball->Position.x -= velocity;
				}
			}
		}
		if (this->Keys[GLFW_KEY_D])
		{
			if (Player->Position.x <= this->Width - Player->Size.x)
			{
				Player->Position.x += velocity;
				if (Ball->Stuck)
				{
					Ball->Position.x += velocity;
				}
			}
		}
		if (this->Keys[GLFW_KEY_SPACE])
		{
			Ball->Stuck = false;
		}
	}
}

void Game::Update(GLfloat dt)
{
	Ball->Move(dt, this->Width);
	this->DoCollisions();
}

void Game::Render()
{
	if (this->State == GAME_ACTIVE)
	{
		Renderer->DrawSprite(ResourceManager::GetTexture("background"), glm::vec2(0, 0), glm::vec2(this->Width, this->Height), 0.0f);
		this->Levels[this->Level].Draw(*Renderer);
		Player->Draw(*Renderer);
		Ball->Draw(*Renderer);
	}
}

void Game::DoCollisions()
{
	for (GameObject &box : this->Levels[this->Level].Bricks)
	{
		if (!box.Destroyed)
		{
			if (CheckCollision(*Ball, box))
			{
				if (!box.IsSolid)
				{
					box.Destroyed = GL_TRUE;
				}
			}
		}
	}
}

GLboolean Game::CheckCollision(GameObject& one, GameObject& two)
{
	bool collisionX = one.Position.x + one.Size.x >= two.Position.x &&
		two.Position.x + two.Size.x >= one.Position.x;
	bool collisionY = one.Position.y + one.Size.y >= two.Position.y &&
		two.Position.y + two.Size.y >= one.Position.y;

	return collisionX && collisionY;
}

GLboolean Game::CheckCollision(BallObject& one, GameObject& two)
{
	glm::vec2 center(one.Position + one.Radius);
	glm::vec2 aabb_half_extents(two.Size.x / 2, two.Size.y / 2);
	glm::vec2 aabb_center(two.Position.x + aabb_half_extents.x,
		two.Position.y + aabb_half_extents.y);

	glm::vec2 different = center - aabb_center;
	glm::vec2 clamped = glm::clamp(different, -aabb_half_extents, aabb_half_extents);
	glm::vec2 closest = aabb_center + clamped;
	different = closest - center;

	return glm::length(different) < one.Radius;
}
