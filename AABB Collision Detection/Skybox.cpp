#include "Skybox\Skybox.h"




Skybox::Skybox(ShaderProgram* fShader):Model()
{
	mShader = fShader;
	
	//Pushing Verts
	Model::VertexData.push_back(glm::vec3(-1.0f, 1.0f, 0.0f));
	Model::VertexData.push_back(glm::vec3(-1.0f, -1.0f, 0.0f));
	Model::VertexData.push_back(glm::vec3(1.0f,  -1.0f, 0.0f));
	Model::VertexData.push_back(glm::vec3(1.0f, 1.0f, 0.0f));
	//Pushing RGB Values
	Model::ColorData.push_back(glm::vec3(0.0f,1.0f,0.0f));
	Model::ColorData.push_back(glm::vec3(0.0f,0.0f,1.0f));
	Model::ColorData.push_back(glm::vec3(0.0f,1.0f,0.0f));
	Model::ColorData.push_back(glm::vec3(1.0f,0.0f,0.0f));
	//Pushing Verts Indices
	Model::IndicesData.push_back(0);
	Model::IndicesData.push_back(1);
	Model::IndicesData.push_back(2);
	Model::IndicesData.push_back(3);
	Model::IndicesData.push_back(0);
	Model::IndicesData.push_back(2);
	//UV-Coords
	Model::UVData.push_back(glm::vec2(0,1));
	Model::UVData.push_back(glm::vec2(0,0));
	Model::UVData.push_back(glm::vec2(1,0));
	Model::UVData.push_back(glm::vec2(1,1));
	
	//ModelMatrices
	TopMM = glm::translate(0.0f, 50.0f,-25.0f)*glm::rotate(90.0f,1.0f,0.0f,0.0f)*glm::scale(50.0f, 50.0f, 50.0f);
	BottomMM = glm::translate(0.0f,-50.0f,-25.0f)*glm::rotate(90.0f,1.0f,0.0f,0.0f)*glm::scale(50.0f, 50.0f, 50.0f);
	LeftMM = glm::translate(-50.0f,0.0f,-25.0f)*glm::rotate(90.0f,0.0f,1.0f,0.0f)*glm::scale(50.0f, 50.0f, 50.0f);
	RightMM = glm::translate(50.0f,0.0f,-25.0f)*glm::rotate(90.0f,0.0f,1.0f,0.0f)*glm::scale(50.0f, 50.0f, 50.0f);
	FrontMM = glm::translate(0.0f,0.0f,25.0f)*glm::scale(50.0f, 50.0f, 50.0f);
	BackMM = glm::translate(0.0f,0.0f,-75.0f)*glm::scale(50.0f, 50.0f, 50.0f);
	
	Model::Initialize();
	//Loading Textures
	Top = std::unique_ptr<Texture>(new Texture("data/textures/top.jpg",0));
	Bottom = std::unique_ptr<Texture>(new Texture("data/textures/bottom.jpg",1));
	Left = std::unique_ptr<Texture>(new Texture("data/textures/left.jpg",2));
	Right = std::unique_ptr<Texture>(new Texture("data/textures/right.jpg",3));
	Front = std::unique_ptr<Texture>(new Texture("data/textures/front.jpg",4));
	Back = std::unique_ptr<Texture>(new Texture("data/textures/back.jpg",5));
	}


void Skybox::Render(glm::mat4 VP)
{
	mShader->UseProgram();
	mShader->BindVPMatrix(&VP[0][0]);
	//Skybox Lighting.
	GLuint AmbientModel =  glGetUniformLocation(mShader->programID,"mAmbient");
	GLuint DiffuseModel = glGetUniformLocation(mShader->programID,"mDiffuse");
	GLuint SpecularModel = glGetUniformLocation(mShader->programID,"mSpecular");
	glUniform3fv(AmbientModel,1, &mAmbientLighting[0]);
	glUniform3fv(DiffuseModel,1, &mDiffuseLighting[0]);
	glUniform3fv(SpecularModel,1, &mDiffuseLighting[0]);

	glDisable(GL_DEPTH_TEST);
	//Front Surface
	Front->Bind();
	glm::mat4 FrontMVP =   VP * FrontMM;
	mShader->BindModelMatrix(&FrontMM[0][0]);
	Model::Draw();
	//Top Surface
	Top->Bind();
	glm::mat4 TopMVP =   VP * TopMM;
	mShader->BindModelMatrix(&TopMM[0][0]);
	Model::Draw();
	//Right Surface
	Right->Bind();
	glm::mat4 RightMVP =   VP * RightMM;
	mShader->BindModelMatrix(&RightMM[0][0]);
	Model::Draw();
	//Back Surface
	Back->Bind();
	glm::mat4 BackMVP =   VP * BackMM;
	mShader->BindModelMatrix(&BackMM[0][0]);
	Model::Draw();
	//Bottom Surface
	Bottom->Bind();
	glm::mat4 BottomMVP =   VP * BottomMM;
	mShader->BindModelMatrix(&BottomMM[0][0]);
	Model::Draw();
	//Left Surface
	Left->Bind();
	glm::mat4 LeftMVP =   VP * LeftMM;
	mShader->BindModelMatrix(&LeftMM[0][0]);
	Model::Draw();

	glEnable(GL_DEPTH_TEST);

}

Skybox::~Skybox(void)
{
}
