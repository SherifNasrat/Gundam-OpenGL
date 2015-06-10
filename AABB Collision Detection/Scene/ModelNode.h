#ifndef ModelNode_h__
#define ModelNode_h__

#include <vector>
#include <string>
#include <glm/glm.hpp>
#include <gl/glew.h>

#include "TexturedModel.h"
#include "GraphicsDevice\ShaderProgram.h"
#include "Texture\texture.h"

class ModelNode
{
	
public:
	std::string name;
	ModelNode* parent;
	std::vector<ModelNode*> children;
	std::vector<TexturedModel*> meshes;
	//std::vector<Texture> textures;
	glm::mat4 transforms;

	ModelNode();
	~ModelNode();

	void Render(ShaderProgram* shaderProgram, glm::mat4 parentTransforms);
	std::vector<glm::vec3> GetVertices(glm::mat4 parentTransforms = (glm::mat4(1)));
	ModelNode* FindNode(std::string name);
};

#endif // Model_h__