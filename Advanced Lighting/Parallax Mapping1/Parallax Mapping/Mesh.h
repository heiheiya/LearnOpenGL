#ifndef _MESH_H_
#define _MESH_H_

#include <GLEW/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <string>
#include <vector>
#include "Shader.h"

using namespace std;

struct Vertex
{
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
	glm::vec3 Tangent;
};

struct Texture
{
	GLuint id;
	string type;
	aiString path;
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

public:
	GLuint VAO;
	GLuint VBO;
	GLuint EBO;
};

#endif // !_MESH_H_
