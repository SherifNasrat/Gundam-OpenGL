#include "ThirdPersonCamera.h"

ThirdPersonCamera::ThirdPersonCamera(void)
{
	mAngleX = 0;
	mAngleY = 0;
	this->Reset(0, 0, 0, 
		0, 0, -1, 
		0, 1, 0);

	SetPerspectiveProjection(45.0f,4.0f/3.0f,0.1f,100.0f);
}

ThirdPersonCamera::~ThirdPersonCamera(void)
{
}

glm::vec3 ThirdPersonCamera::GetLookDirection()
{
	return -mDirection;
}

void ThirdPersonCamera::Reset(float eyeX, float eyeY, float eyeZ, float centerX, float centerY, float centerZ, float upX, float upY, float upZ)
{
	glm::vec3 eyePt(eyeX, eyeY, eyeZ);
	glm::vec3 centerPt(centerX, centerY, centerZ);
	glm::vec3 upVec(upX, upY, upZ);
	Reset(eyePt, centerPt, upVec);
}

void ThirdPersonCamera::Reset(const glm::vec3 &eye, const glm::vec3 &center, glm::vec3 &up)
{
	mPosition = eye;
	
	//still needs normalization
	mDirection = center - mPosition;
	//i = j x k
	mRight = glm::cross( mDirection,up );
	//j = k x i
	mUp = up;
	//normalize all
	mUp = glm::normalize(mUp);
	mRight = glm::normalize(mRight);
	mDirection = glm::normalize(mDirection);
	mCenter = center;
	mViewMatrix = glm::lookAt(mPosition,center,mUp);
	//UpdateViewMatrix();
}

glm::mat4 ThirdPersonCamera::GetViewMatrix()
{
	return mViewMatrix;
}

void ThirdPersonCamera::UpdateViewMatrix()
{
	const float PI = 3.14f;
	auto yawRotation = glm::rotate((float)-mAngleX,0.0f,1.0f,0.0f);
	auto pitchRotation  = glm::rotate((float)-mAngleY,mRight);
	auto newPosition = glm::vec3(pitchRotation*yawRotation*glm::vec4(0,1,2,1));
	newPosition += mCenter;

	mDirection = mCenter - newPosition;
	mDirection = glm::normalize(mDirection);


	mRight = glm::cross(mDirection,glm::vec3(0,1,0));
	mRight = glm::normalize(mRight);
	mUp = glm::cross(mRight,mDirection);
	mUp = glm::normalize(mUp);

	//glm::vec3 center = mPosition + mDirection;
	//mCenter = center;
	mViewMatrix = glm::lookAt(newPosition,mCenter,mUp);

	//glm::mat4 view = glm::mat4(	mRight.x,		mRight.y,		mRight.z,		-glm::dot(mPosition,mRight),
	//	mUp.x,			mUp.y,			mUp.z,			-glm::dot(mPosition,mUp),
	//	mDirection.x,	mDirection.y,	mDirection.z,	-glm::dot(mPosition,mDirection),
	//	0,				0,				0,				1);
	//mViewMatrix = glm::transpose(view);
}

glm::mat4 ThirdPersonCamera::GetProjectionMatrix()
{
	return mProjectionMatrix;
}

void ThirdPersonCamera::SetPerspectiveProjection(float FOV, float aspectRatio, float near, float far)
{
	mProjectionMatrix = glm::perspective(FOV,aspectRatio,near,far);
}

void ThirdPersonCamera::Slide(float stepR, float stepU, float stepD)
{
	mPosition += stepR *mRight;
	mPosition += stepU * mUp;
	//next transition needs to be tested!!.
	mPosition += stepD * mDirection;
}

void ThirdPersonCamera::Yaw(float angleDegrees)
{
	mAngleX +=angleDegrees;

}

void ThirdPersonCamera::Pitch(float angleDegrees)
{
	double PI = 3.14;
	if (mAngleY + angleDegrees < 90 && mAngleY + angleDegrees >  -20)
		mAngleY +=angleDegrees;
}

void ThirdPersonCamera::Roll(float angleDegrees)
{
	//no ROLL!!!
}

void ThirdPersonCamera::Walk(float dist)
{
	mPosition += dist * glm::vec3(mDirection.x,0,mDirection.z);
	mCenter += dist * glm::vec3(mDirection.x,0,mDirection.z);
}

void ThirdPersonCamera::Strafe(float dist)
{
	mPosition += dist  * glm::vec3(mRight.x,0,mRight.z);
	mCenter += dist  * glm::vec3(mRight.x,0,mRight.z);
}

void ThirdPersonCamera::Fly(float dist)
{
	//NO Fly!
}
glm::vec3 ThirdPersonCamera::GetEyePosition()
{
	return mPosition;
}
glm::vec3 ThirdPersonCamera::GetDirection()
{
	return mDirection;
}
glm::vec3 ThirdPersonCamera::GetRight()
{
	return mRight;
}