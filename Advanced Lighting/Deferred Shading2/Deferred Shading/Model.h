#ifndef _MODEL_H_
#define _MODEL_H_

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Mesh.h"

class Model
{
public:
	Model(GLchar* path)
	{
		this->loadModel(path);
	}
	void Draw(Shader shader);

private:
	void loadModel(string path);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	vector<Texture> loadMaterialTexture(aiMaterial* mat, aiTextureType type, string typeName);

public:
	vector<Mesh> meshes;
	vector<Texture> textures_loaded;

private:
	string directory;

};

GLint TextureFromFile(const char* path, string directory);

#endif // !_MODEL_H_
