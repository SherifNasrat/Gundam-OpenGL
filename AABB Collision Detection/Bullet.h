#ifndef Bullet_h__
#define Bullet_h__
#include <GameObject.h>
#include "Model\Model.h"
#include "CollisionDetection\CollidableModel.h"
class Bullet : public GameObject, public CollidableModel
{
	float mTravelDist;
	float mDamage;
	Model* mBulletModel;
public:
	Bullet(void);
	Bullet(glm::vec3 fPosition,glm::vec3 fDirection,float fDamage,ObjectType fBulletSource,bool fisDestroyed = false);
	virtual void Collided(ObjectType);
	void DrawBullet();
	~Bullet(void);
};
#endif // Bullet_h__
