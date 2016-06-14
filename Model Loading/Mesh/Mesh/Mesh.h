#ifndef _MESH_H_
#define _MESH_H_

#include <GLEW/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>
#include <vector>
#include "shader.h"

using namespace std;

struct Vertex
{
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
};

struct Texture
{
	GLuint id;
	string type;
};

class Mesh
{
public:

	Mesh(vector<Vertex> vertices, vector<GLuint> indices, vector<Texture> textures);

	void Draw(Shader shader);

public:
	vector<Vertex> vertices;
	vector<GLuint> indices;
	vector<Texture> textures;

private:
	void setupMesh();

private:
	GLuint VAO;
	GLuint VBO;
	GLuint EBO;
};

#endif // !_MESH_H_
