#ifndef AABoundingBox_h__
#define AABoundingBox_h__
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>


class AABoundingBox
{
	glm::vec3 size;
	glm::vec3 center;
	glm::vec3 halfSize;
public:
	AABoundingBox();
	AABoundingBox(glm::vec3 fCenter, glm::vec3 fSize);
	~AABoundingBox(void);

	void SetCenter(glm::vec3 fCenter);
	void SetSize(glm::vec3 fSize);
	
	inline glm::vec3 GetCenter() { return center;}
	inline glm::vec3 GetSize() { return size;}
	inline glm::vec3 GetHalfSize() {return halfSize;}

	bool IsIntersecting(AABoundingBox box);

	void Scale(glm::vec3 scale);
	void Scale(float scaleX,float scaleY, float scaleZ);
	void Translate(glm::vec3 translation);
	void Translate(float translateX, float translateY, float translateZ);
	void Rotate(glm::mat4 rotationMatrix);
	void Rotate(float angle,float axisX,float axisY, float axisZ);
};

#endif // AABoundingBox_h__
