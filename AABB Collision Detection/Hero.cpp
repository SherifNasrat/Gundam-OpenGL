#include "Hero.h"



Hero::Hero(KeyFrameAnimationShader* fShader) : GameObject()
{
	counter=0.2f;
	onGround= true;
	obj = ObjectType::Hero;
	temp=1;
	mShader = fShader;
	lastKeyPressed=0;
	Initialize();
}
Hero::Hero(KeyFrameAnimationShader* fShader,glm::vec3 fPosition,glm::vec3 fDirection,bool fisDestroyed) : GameObject(fPosition,fDirection,fisDestroyed)
{
	counter=0.2f;
	onGround=true;
	obj = ObjectType::Hero;
	temp=1;
	mShader = fShader;
	Initialize();
	auto tempBoundingBox = CMD2Model::GetBoundingBox();
	tempBoundingBox.Translate(fPosition);
	lastKeyPressed=0;
}

void Hero::UpdateAnimation(float deltaTime)
{

	CMD2Model::UpdateAnimation(&mAnimationState,deltaTime);
	/*if(onGround==false)
	{
		
		
		Move(glm::vec3(0.0f,-0.01f,0.0f));
		counter-=0.01f;
		if(counter <= -0.02f)
		{
			onGround=true;
		}
		
	}*/
	if(CMD2Model::isAnimationFinished == true && mAnimationState.type != animType_t::STAND)
	{
		mAnimationState = CMD2Model::StartAnimation(animType_t::STAND);
	}
	
	
}
Hero::~Hero(void)
{

}
void Hero::Initialize()
{
	CMD2Model::LoadModel("data/models/blade/tris.md2");
	mAnimationState = this->StartAnimation(animType_t::STAND);
	CMD2Model::SetBoundingBox(CollidableModel::CalculateBoundingBox(CMD2Model::GetVertices()));
	mInitialTransformations = glm::translate(0.0f,0.25f,0.0f)*glm::rotate(-90.0f,1.0f,0.0f,0.0f)*glm::scale(0.01f,0.01f,0.01f);
	GameObject::UpdateModelMatrix();

	//Collision-Bounding Box for Hero.
	auto tempBoundingBox = CMD2Model::GetBoundingBox();
	tempBoundingBox.Scale(0.01f,0.01f,0.1f);
	tempBoundingBox.Rotate(-90.0f,0.0f,1.0f,0.0f);
	tempBoundingBox.Translate(0.0f,0.25f,0.0f);
	CMD2Model::SetBoundingBox(tempBoundingBox);

	mInitialCameraOffset = glm::vec3(0.0f,1.0f,2.0f);
	Camera = std::unique_ptr<ThirdPersonCamera>(new ThirdPersonCamera());
	auto position = GameObject::getPosition();
	Camera->Reset(position+mInitialCameraOffset,position,glm::vec3(0.0f,1.0f,0.0f));
	Camera->SetPerspectiveProjection(45.0f,4.0f/3.0f,0.1f,100.0f);
	
}
void Hero::Render(glm::mat4 VP)
{
	if(mIsDestroyed==false)
	{

	
	mShader->UseProgram();
	mShader->BindVPMatrix(&VP[0][0]);
	GLuint AmbientModel =  glGetUniformLocation(mShader->programID,"mAmbient");
	GLuint DiffuseModel = glGetUniformLocation(mShader->programID,"mDiffuse");
	GLuint SpecularModel = glGetUniformLocation(mShader->programID,"mSpecular");
	glUniform3fv(AmbientModel,1, &mAmbientLighting[0]);
	glUniform3fv(DiffuseModel,1, &mDiffuseLighting[0]);
	glUniform3fv(SpecularModel,1, &mDiffuseLighting[0]);
	mShader->BindModelMatrix(&(GameObject::getModelMatrix()[0][0]));
	CMD2Model::RenderModel(&mAnimationState,mShader);
	}
	else
	{
		   

	}
}
void Hero::Collided(ObjectType fObject)
{
	//mAnimationState = CMD2Model::StartAnimation(animType_t::DEATH_FALLBACK);
	
	if(fObject==ObjectType::Model3D){
 printf("Player collided with Model3D %d times \n",temp-1);  
  mIsDestroyed=true;
 }
	else if(fObject == ObjectType::Model)
		printf("Player collided with Model %d",temp-1);
	temp++;
}
void Hero::Move(glm::vec3 fDirection)
{
	//auto oldDirection =GameObject::getDirection();
	
//	GameObject::SetDirection(fDirection);
	auto newPosition = GameObject::getPosition();
	newPosition = newPosition + fDirection;
	GameObject::setPosition(newPosition);
	fDirection.z*=-1;
	fDirection = glm::normalize(fDirection);
	GameObject::SetDirection(fDirection);
	GameObject::UpdateModelMatrix();
	//Updating the Bounding Box.
	auto newBoundingBox = CollidableModel::GetBoundingBox();
	newBoundingBox.SetCenter(newPosition);
	CMD2Model::SetBoundingBox(newBoundingBox);

	

//	float rotationAngle = glm::acos(glm::dot(oldDirection,fDirection));
	//newBoundingBox.Rotate(rotationAngle,0.0f,1.0f,0.0f);
	if(CMD2Model::isAnimationFinished == true || mAnimationState.type != animType_t::RUN)
	{
		mAnimationState = CMD2Model::StartAnimation(animType_t::RUN);
		
	}

}
void Hero::Walk(float dist)
{
	auto CameraDirection = Camera->GetDirection();
	auto direction =  dist*glm::vec3(CameraDirection.x,0,CameraDirection.z);
	Hero::Move(direction);
	auto HeroBB = CollidableModel::GetBoundingBox();
	HeroBB.Translate(direction);
	CollidableModel::SetBoundingBox(HeroBB);
	//dist 
	Camera->Walk(dist);
	Camera->UpdateViewMatrix();

}
void Hero::Strafe(float dist)
{
	auto cameraRight = Camera->GetRight();
	auto direction = dist*glm::vec3 (cameraRight.x,0,cameraRight.z);
	Hero::Move(direction);
	auto HeroBB = CollidableModel::GetBoundingBox();
	HeroBB.Translate(direction);
	CollidableModel::SetBoundingBox(HeroBB);
	//dist
	Camera->Strafe(dist);
	Camera->UpdateViewMatrix();
	if(dist > 0.0f)
	{
		lastKeyPressed = GLFW_KEY_D;
	}
	else
	{
		lastKeyPressed=GLFW_KEY_A;
	}
}

void Hero::Attack()
{
	if(CMD2Model::isAnimationFinished == true || mAnimationState.type != animType_t::ATTACK)
	{
		mAnimationState = CMD2Model::StartAnimation(animType_t::ATTACK);
	}
}

void Hero::Crouch()
{
	if(CMD2Model::isAnimationFinished == true || mAnimationState.type != animType_t::CROUCH_STAND)
	{
		mAnimationState = CMD2Model::StartAnimation(animType_t::CROUCH_STAND);
	}
}

void Hero::Jump()
{
	counter=0.2f;
	auto fDirection = GameObject::getDirection();
	glm::vec3 jumping = glm::vec3 (0.0f,0.2f,0.0f);
	Hero::Move(jumping);
	onGround=false;
	if(CMD2Model::isAnimationFinished == true || mAnimationState.type != animType_t::JUMP)
	{
		mAnimationState = CMD2Model::StartAnimation(animType_t::JUMP);
	}
}

