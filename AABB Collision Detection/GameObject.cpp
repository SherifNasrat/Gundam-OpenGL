#include "GameObject.h"


GameObject::GameObject(void)
{
	mPosition = glm::vec3(0);
	mDirection= glm::vec3(1.0f,0.0f,0.0f);
	mDirectionAngle=0;
	mModelMatrix = glm::mat4(1);
	mIsDestroyed = false;
}
GameObject::GameObject(glm::vec3 fPosition,glm::vec3 fDirection,bool fisDestroyed)
{
	mPosition = fPosition;
	mDirection = fDirection;
	mIsDestroyed = fisDestroyed;
	//To be tested!!
	mDirectionAngle = glm::atan(mDirection.z/mDirection.x);
	UpdateModelMatrix();
}

GameObject::~GameObject(void)
{
}
glm::mat4 GameObject::getModelMatrix()
{
	return mModelMatrix;
}
void GameObject::setModelMatrix(glm::mat4 fModelMatrix)
{
	mModelMatrix=fModelMatrix;
}
void GameObject::SetDirection(glm::vec3 fDirection)
{
	mDirection = fDirection;
	mDirectionAngle = atan2(mDirection.z,mDirection.x)*(180.0/PI);
}
glm::vec3 GameObject::getDirection()
{
	return mDirection;
}
void GameObject::setPosition(glm::vec3 fPosition)
{
	mPosition=fPosition;
}
glm::vec3 GameObject::getPosition()
{
	return mPosition;
}
void GameObject::UpdateModelMatrix()
{

	mModelMatrix = glm::translate(mPosition)*glm::rotate(mDirectionAngle,0.0f,1.0f,0.0f) * mInitialTransformations ;
	
}
void GameObject::Destroy()
{
	mIsDestroyed=true;
}

//Lighting 
void GameObject::setAmbient(glm::vec3 fAmbient)
{
	mAmbientLighting = fAmbient;
}

void GameObject::setDiffuse(glm::vec3 fDiffuse)
{
	mDiffuseLighting = fDiffuse;
}

void GameObject::setSpecular(glm::vec3 fSpecular)
{
	mSpecularLighting = fSpecular;
}

glm::vec3 GameObject::getAmbient()
{
	return mAmbientLighting;
}

glm::vec3 GameObject::getDiffuse()
{
	return mDiffuseLighting;
}

glm::vec3 GameObject::getSpecular()
{
	return mSpecularLighting;
}
