#ifndef GameObject_h__
#define GameObject_h__
#include <glm/glm.hpp>
#include <glm\gtx\transform.hpp>
#include "GraphicsDevice\ShaderProgram.h"
#define PI 3.14159265359
class GameObject
{
protected:
	glm::mat4 mModelMatrix; //Move,Rotate,Scale any object.
	glm::vec3 mDirection; //Which direction is the object looking at.
	glm::vec3 mPosition;  //Where the object is in the world space.
	float mDirectionAngle; //The angle of rotation for any object.
	bool mIsDestroyed; 
	glm::mat4 mInitialTransformations; 
	//Lighting 
	glm::vec3 mAmbientLighting; 
	glm::vec3 mDiffuseLighting;
	glm::vec3 mSpecularLighting;
public:
	GameObject(void); 
	GameObject(glm::vec3 fPosition,glm::vec3 fDirection,bool fisDestroyed);
	void UpdateModelMatrix();
	glm::mat4 getModelMatrix();
	void setModelMatrix(glm::mat4 fModelMatrix);
	~GameObject(void);
	void SetDirection(glm::vec3 fDirection);
	glm::vec3 getDirection();
	void setPosition(glm::vec3 fPosition);
	glm::vec3 getPosition();
	void Destroy();
	//Lighting
	void setAmbient(glm::vec3);
	void setDiffuse(glm::vec3);
	void setSpecular(glm::vec3);
	glm::vec3 getAmbient();
	glm::vec3 getDiffuse();
	glm::vec3 getSpecular();
};


#endif // !GameObject_h__
