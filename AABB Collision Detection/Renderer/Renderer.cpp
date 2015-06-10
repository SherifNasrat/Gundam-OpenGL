#include "Renderer.h"

#include <glm/gtc/matrix_transform.hpp> 
#include <glm/gtx/transform.hpp>
#include "OBJLoader/objloader.hpp"

Renderer::Renderer()
{
    
}

Renderer::~Renderer()
{
    Cleanup();
}

void Renderer::Initialize()
{

	collisionManager = std::unique_ptr<CollisionManager>( new CollisionManager());
	//////////////////////////////////////////////////////////////////////////
	
	//LOADING THE HERO-PLAYER and Skybox
	//////////////////////////////////////////////////////////////////////////
	Player = std::unique_ptr<Hero>(new Hero(&animatedModelShader));
	collisionManager->AddCollidableModel((CollidableModel*)Player.get());
	sky = std::unique_ptr<Skybox>(new Skybox(&staticModelShader));
	//////////////////////////////////////////////////////////////////////////
	
	//////////////////////////////////////////////////////////////////////////
	Chest = std::unique_ptr<Model3D>(new Model3D());
	Chest->LoadFromFile("data/models/treasure_chest_obj/chest.obj",true);
	Chest->Initialize();
	Chest->SetBoundingBox(CollidableModel::CalculateBoundingBox(Chest->GetVertices()));
	collisionManager->AddCollidableModel((CollidableModel*) Chest.get());
	//////////////////////////////////////////////////////////////////////////

	//drawing a square.
	floor = std::unique_ptr<Model>(new Model());

	floor->VertexData.push_back(glm::vec3(-1.0f, -1.0f, 0.0f));
	floor->UVData.push_back(glm::vec2(0.0f,0.0f));
	floor->VertexData.push_back(glm::vec3(1.0f, -1.0f, 0.0f));
	floor->UVData.push_back(glm::vec2(10.0f,0.0f));
	floor->VertexData.push_back(glm::vec3( 1.0f,  1.0f, 0.0f));
	floor->UVData.push_back(glm::vec2(10.0f,10.0f));
	floor->VertexData.push_back(glm::vec3( -1.0f,  1.0f, 0.0f));
	floor->UVData.push_back(glm::vec2(0.0f,10.0f));
	
	//first triangle.
	floor->IndicesData.push_back(0);
	floor->IndicesData.push_back(1);
	floor->IndicesData.push_back(3);

	//second triangle.
	floor->IndicesData.push_back(1);
	floor->IndicesData.push_back(2);
	floor->IndicesData.push_back(3);
	glm::vec3 squareNormal = glm::vec3(0.0,0.0,1.0);
	floor->NormalsData.push_back(squareNormal);
	floor->NormalsData.push_back(squareNormal);
	floor->NormalsData.push_back(squareNormal);
	floor->NormalsData.push_back(squareNormal);
	floor->Initialize();

	floorTexture = std::unique_ptr<Texture>(new Texture("data/textures/top.jpg",0));
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	//load model.
	mySpider = std::unique_ptr<Model3D>(new Model3D());
	//read model and it's textures from HDD.
	mySpider->LoadFromFile("data/models/Spider/Spider.obj",true);
	//send the meshes to the GPU.
	mySpider->Initialize();
	mySpider->SetBoundingBox(CollidableModel::CalculateBoundingBox(mySpider->GetVertices()));
	collisionManager->AddCollidableModel((CollidableModel*) mySpider.get());
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	/*house = std::unique_ptr<Model3D>(new Model3D());
	house->LoadFromFile("data/models/House/house.3ds");
	house->Initialize();
	house->SetBoundingBox(CollidableModel::CalculateBoundingBox(house->GetVertices(),-2.0f));
	collisionManager->AddCollidableModel((CollidableModel*) house.get());*/
	//////////////////////////////////////////////////////////////////////////



	//////////////////////////////////////////////////////////////////////////
	// Create and compile our GLSL program from the shaders
	animatedModelShader.LoadProgram();
	staticModelShader.LoadProgram();
	//////////////////////////////////////////////////////////////////////////

	

	//////////////////////////////////////////////////////////////////////////
	// Configure the light.
	//setup the light position.
	staticModelShader.UseProgram();
	LightPositionID = glGetUniformLocation(staticModelShader.programID,"LightPosition_worldspace");
	lightPosition = glm::vec3(0.0,50.0,0.0);
	glUniform3fv(LightPositionID,1, &lightPosition[0]);
	//setup the ambient light component.
	AmbientLightID = glGetUniformLocation(staticModelShader.programID,"ambientLight");
	ambientLight = glm::vec3(0.5,0.5,0.5);
	glUniform3fv(AmbientLightID,1, &ambientLight[0]);
	//setup the eye position.
	EyePositionID = glGetUniformLocation(staticModelShader.programID,"EyePosition_worldspace");
	//send the eye position to the shaders.
	glUniform3fv(EyePositionID,1, &Player->Camera->GetEyePosition()[0]);

	///////////////////////////////////////////////////
	//repeat the process for the animated models shader.
	animatedModelShader.UseProgram();
	LightPositionID = glGetUniformLocation(animatedModelShader.programID,"LightPosition_worldspace");
	lightPosition = glm::vec3(0.0,5.0,0.0);
	glUniform3fv(LightPositionID,1, &lightPosition[0]);
	//setup the ambient light component.
	AmbientLightID = glGetUniformLocation(animatedModelShader.programID,"ambientLight");
	ambientLight = glm::vec3(0.5,0.5,0.5);
	glUniform3fv(AmbientLightID,1, &ambientLight[0]);
	//setup the eye position.
	EyePositionID = glGetUniformLocation(animatedModelShader.programID,"EyePosition_worldspace");
	//send the eye position to the shaders.
	glUniform3fv(EyePositionID,1, &Player->Camera->GetEyePosition()[0]);
	//////////////////////////////////////////////////////////////////////////

	

	//////////////////////////////////////////////////////////////////////////
	//Setting the initaial transformations
	floorM =  glm::scale(50.0f,2.0f,50.0f)*glm::rotate(-90.0f,glm::vec3(1.0f,0.0f,0.0f));
	spiderM = glm::translate(0.0f,0.25f,-2.0f) * glm::scale(0.005f,0.005f,0.005f);
	ChestM = glm::translate(0.0f,0.0f,-2.0f)*glm::scale(0.003f,0.003f,0.003f);
	auto ChestBB = Chest->GetBoundingBox();
	ChestBB.Scale(0.003f,0.003f,0.003f);
	ChestBB.Translate(0.0f,0.0f,-2.0f);
	Chest->SetBoundingBox(ChestBB);
	//we have to scale and translate the 's bounding box to match the new position and size.
	auto tempBox = mySpider->GetBoundingBox();
	tempBox.Scale(0.005f,0.005f,0.005f);
	tempBox.Translate(0.0f,0.25f,-2.0f);
	
	mySpider->SetBoundingBox(tempBox);
	


	//houseM = glm::rotate(90.0f,1.0f,0.0f,0.0f) *glm::scale(0.1f,0.1f,0.1f);
	//tempBox = house->GetBoundingBox();
	//tempBox.Scale(0.1f,0.1f,0.1f); 
	//tempBox.Rotate(90.0f,1.0f,0.0f,0.0f);
	//house->SetBoundingBox(tempBox);


	//////////////////////////////////////////////////////////////////////////

}

void Renderer::Draw()
{		

		//Bind the VP matrix (Camera matrices) to the current shader.
		glm::mat4 VP = Player->Camera->GetProjectionMatrix() * Player->Camera->GetViewMatrix();

		
		staticModelShader.UseProgram();
		staticModelShader.BindVPMatrix(&VP[0][0]);
		sky->setAmbient(glm::vec3(1.0f,1.0f,1.0f));
		sky->setDiffuse(glm::vec3(1.0f,1.0f,1.0f));
		sky->setSpecular(glm::vec3(0.0f,0.0f,0.0f));
		sky->Render(VP);
		staticModelShader.BindModelMatrix(&floorM[0][0]);
		floorTexture->Bind();
		floor->Draw();

		
		mySpider->Render(&staticModelShader,spiderM);
		//Chest->Render(&staticModelShader,ChestM);
		/*house->Render(&staticModelShader,houseM);*/
		
		Player->setAmbient(glm::vec3(1.0f,1.0f,1.0f));
		Player->setDiffuse(glm::vec3(1.0f,1.0f,1.0f));
		Player->setSpecular(glm::vec3(1.0f,1.0f,1.0f));
		Player->Render(VP);
		
		

}

void Renderer::Cleanup()
{
}

void Renderer::Update(double deltaTime)
{
	Player->UpdateAnimation(deltaTime*0.001);
	collisionManager->UpdateCollisions();
}

void Renderer::HandleKeyboardInput(int key)
{
	float step = 0.07f;
	//auto tempbox = blade.GetBoundingBox();

	//NOTE!!! 
	//this is the worst way possible for moving an object with the camera.
	// but it'll serve our purpose for now.

	switch (key)
	{
		//Moving forward
	case GLFW_KEY_UP:
	case GLFW_KEY_W:
		Player->Walk(step);
		
		break;

		//Moving backword
	case GLFW_KEY_DOWN:
	case GLFW_KEY_S:
		Player->Walk(-step);
		break;

		// Moving right
	case GLFW_KEY_RIGHT:
	case GLFW_KEY_D:
		Player->Strafe(step);
		break;

		// Moving left
	case GLFW_KEY_LEFT:
	case GLFW_KEY_A:
		Player->Strafe(-step);
		break;

		// Moving up
	case GLFW_KEY_SPACE:
	case GLFW_KEY_R:
		//Player->Attack();
		Player->Jump();
		break;

		// Moving down
	case GLFW_KEY_LEFT_CONTROL:
	case GLFW_KEY_F:
		Player->Crouch();

		break;
	default:
		break;
	}

	//Set the transformed bounding box again.


	//continue the remaining movements.


	//update the eye position uniform.
	staticModelShader.UseProgram();
	EyePositionID = glGetUniformLocation(staticModelShader.programID,"EyePosition_worldspace");
	glUniform3fv(EyePositionID,1, &Player->Camera->GetEyePosition()[0]);

	animatedModelShader.UseProgram();
	EyePositionID = glGetUniformLocation(animatedModelShader.programID,"EyePosition_worldspace");
	glUniform3fv(EyePositionID,1, &Player->Camera->GetEyePosition()[0]);
}

void Renderer::HandleMouse(double deltaX,double deltaY)
{	
	double RotSpeed = 30.0f;
	Player->Camera->Yaw(-deltaX*RotSpeed);
	Player->Camera->Pitch(-deltaY*RotSpeed);
	Player->Camera->UpdateViewMatrix();
}

