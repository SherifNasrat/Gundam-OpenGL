#ifndef Skybox_h__
#define Skybox_h__
#include <GameObject.h>
#include <Model\Model.h>
#include <vector>
#include <memory>
#include <iostream>

#include "Texture\texture.h"
class Skybox : public GameObject, public Model
{
	//Skybox Textures
	std::unique_ptr<Texture>Top;
	std::unique_ptr<Texture>Bottom;
	std::unique_ptr<Texture>Left;
	std::unique_ptr<Texture>Right;
	std::unique_ptr<Texture>Front;
	std::unique_ptr<Texture>Back;
	//Skybox MM
	glm::mat4 TopMM;
	glm::mat4 BottomMM;
	glm::mat4 LeftMM;
	glm::mat4 RightMM;
	glm::mat4 FrontMM;
	glm::mat4 BackMM;
	//Shader
	ShaderProgram* mShader;
public:
	Skybox(ShaderProgram* fShader);
	void Render(glm::mat4 VP);
	~Skybox(void);
};

#endif // !Skybox_h__

