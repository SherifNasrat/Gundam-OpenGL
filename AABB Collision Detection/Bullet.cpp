#include "Bullet.h"


Bullet::Bullet(void)
{
}
Bullet::Bullet(glm::vec3 fPosition,glm::vec3 fDirection,float fDamage,ObjectType fBulletSource,bool fisDestroyed = false) : GameObject::GameObject(fPosition,fDirection,fisDestroyed)
{
	CollidableModel::obj = fBulletSource;
	mDamage =fDamage;
	AABoundingBox bulletBB(fPosition,glm::vec3(0.1f,0.1f,0.1f));
	CollidableModel::SetBoundingBox(bulletBB);

}


Bullet::~Bullet(void)
{

}
void Bullet::Collided(ObjectType obj)
{
	GameObject::Destroy();

}
void Bullet::DrawBullet()
{

}
