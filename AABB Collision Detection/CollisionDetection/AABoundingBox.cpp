#include "AABoundingBox.h"
#include "CollidableModel.h"




AABoundingBox::AABoundingBox()
{
	SetCenter(glm::vec3(0));
	SetSize(glm::vec3(0));
}

AABoundingBox::AABoundingBox(glm::vec3 fCenter, glm::vec3 fSize)
{
	SetCenter(fCenter);
	SetSize(fSize);
}

AABoundingBox::~AABoundingBox(void)
{

}

void AABoundingBox::SetCenter(glm::vec3 fCenter)
{
	center = fCenter;
}

void AABoundingBox::SetSize(glm::vec3 fSize)
{
	size = fSize;
	halfSize = size/2.0f;
}

bool AABoundingBox::IsIntersecting(AABoundingBox box)
{
	glm::vec3 absoluteDistance = glm::abs( this->center - box.GetCenter());
	glm::vec3 totalHalfSize = this->GetHalfSize() + box.GetHalfSize();
	if(		absoluteDistance.x < totalHalfSize.x
		&&	absoluteDistance.y < totalHalfSize.y
		&&	absoluteDistance.z < totalHalfSize.z)
	{
		return true;
	}
	return false;
}

void AABoundingBox::Scale(glm::vec3 scale)
{
	glm::vec3 scaledSize = this->size * scale;
	glm::vec3 scaledCenter = this->center *scale;
	SetSize(scaledSize);
	SetCenter(scaledCenter);
}

void AABoundingBox::Scale(float scaleX,float scaleY, float scaleZ)
{
	glm::vec3 scale = glm::vec3(scaleX,scaleY,scaleZ);
	Scale(scale);
}

void AABoundingBox::Translate(glm::vec3 translation)
{
	glm::vec3 translatedCenter = this->center + translation;
	SetCenter(translatedCenter);
}

void AABoundingBox::Translate(float translateX, float translateY, float translateZ)
{
	glm::vec3 translation = glm::vec3(translateX,translateY,translateZ);
	Translate(translation);
}

void AABoundingBox::Rotate(glm::mat4 rotationMatrix)
{
	// this solution will fail in many cases, if we rotated for 45 degrees for example.
	/*glm::vec3 rotatedSize = glm::vec3(rotationMatrix*glm::vec4(this->size,1));
	rotatedSize = glm::abs(rotatedSize);
	SetSize(rotatedSize);*/

#pragma region another solution to be tested
	std::vector<glm::vec3> corners;
	int numberOfCorners = 4;
	corners.resize(numberOfCorners);
	for (int i = 0; i < corners.size(); i++)
	{
		corners[i] = halfSize;
	}
	corners[1].y *= -1;
	corners[2].z *= -1;
	corners[3].y *= -1;
	corners[3].z *= -1;
	for (int i = 0; i < corners.size(); i++)
	{
		corners[i] = glm::vec3(rotationMatrix*glm::vec4(corners[i],1));
	}
	for (int i = 0; i < numberOfCorners; i++)
	{
		corners.push_back(corners[i] *-1.0f);
	}
	auto cornersBox = CollidableModel::CalculateBoundingBox(corners);
	SetSize(cornersBox.GetSize());
#pragma endregion another solution to be tested
	
}

void AABoundingBox::Rotate(float angle,float axisX,float axisY, float axisZ)
{
	glm::mat4 rotationMatrix = glm::rotate(angle,axisX,axisY,axisZ);
	Rotate(rotationMatrix);
}
