#include "Game.h"

#include "Resource_manager.h"
#include "Sprite_renderer.h"


SpriteRenderer *Renderer;

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
}

void Game::Init()
{
	ResourceManager::LoadShader("shaders/sprite.vs", "shaders/sprite.frag", nullptr, "sprite");

	glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(this->Width), static_cast<GLfloat>(this->Height), 0.0f, -1.0f, 1.0f);

	ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
	ResourceManager::GetShader("sprite").Use().SetMatrix4("projection", projection);

	Renderer = new SpriteRenderer(ResourceManager::GetShader("sprite"));

	ResourceManager::LoadTexture("textures/awesomeface.png", GL_TRUE, "face");
}

void Game::ProcessInput(GLfloat dt)
{

}

void Game::Update(GLfloat dt)
{

}

void Game::Render()
{
	Renderer->DrawSprite(ResourceManager::GetTexture("face"), glm::vec2(200, 200), glm::vec2(300, 400), 45.0f, glm::vec3(0.0f, 1.0f, 0.0f));
}
