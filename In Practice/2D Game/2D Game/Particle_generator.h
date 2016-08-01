#ifndef PARTICLE_GENERATOR_H
#define PARTICLE_GENERATOR_H

#include <vector>

#include <GLEW/glew.h>
#include <glm/glm.hpp>

#include "Shader.h"
#include "Texture.h"
#include "Game_object.h"

struct Particle
{
	glm::vec2 Position;
	glm::vec2 Velocity;
	glm::vec4 Color;
	GLfloat   Life;

	Particle() :Position(0.0f), Velocity(0.0f), Color(1.0f), Life(0.0f){}
};

class ParticleGenerator
{
public:
	ParticleGenerator(Shader shader, Texture2D texture, GLuint amount);

public:
	void Update(GLfloat dt, GameObject &object, GLuint newParticles, glm::vec2 offset = glm::vec2(0.0f, 0.0f));
	void Draw();

private:
	void Init();
	GLuint FirstUnusedParticle();
	void RespawnParticle(Particle &particle, GameObject &object, glm::vec2 offset = glm::vec2(0.0f, 0.0f));

private:
	std::vector<Particle> particles;
	GLuint amount;
	Shader shader;
	Texture2D texture;
	GLuint VAO;
};

#endif //PARTICLE_GENERATOR_H