#ifndef Hero_h__
#define Hero_h__
#include "GameObject.h"
#include <memory>
#include "Third Person Camera\ThirdPersonCamera.h"
#include "EulerCamera\EulerCamera.h"
#include "CollisionDetection\CollidableModel.h"
#include "MD2Model\md2model.h"
#include <gl\glfw3.h>
class Hero : public GameObject,public CMD2Model
{
	KeyFrameAnimationShader* mShader;
	animState_t mAnimationState;
	glm::vec3 mInitialCameraOffset;
	void Move(glm::vec3 fDirection);
	bool onGround;
	int temp;
	int lastKeyPressed;
	float counter;
public:
	std::unique_ptr<ThirdPersonCamera> Camera;
	Hero(void);
	Hero(KeyFrameAnimationShader* fShader);
	Hero(KeyFrameAnimationShader* fShader,glm::vec3 fPosition,glm::vec3 fDirection,bool fisDestroyed);
	~Hero(void);
	virtual void Collided(ObjectType fObject); //Collision Function of Hero class.
	void UpdateAnimation (float deltatime);
	void Initialize();
	void Render(glm::mat4 VP);
	void Walk(float dist);
	void Strafe(float dist);
	void Attack();
	void Crouch();
	void Jump();

};
#endif // Hero_h__

