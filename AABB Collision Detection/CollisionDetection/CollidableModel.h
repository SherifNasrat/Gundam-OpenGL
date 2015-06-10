#ifndef CollidableModel_h__
#define CollidableModel_h__

#include "AABoundingBox.h"
#include <vector>
#include <glm\glm.hpp>

class CollidableModel
{
	AABoundingBox boundingBox;

public:
	enum ObjectType {
		Hero,Model3D,Enemy,Model,MD2Model
	};
	ObjectType obj; //Object of type ObjectType(enum).
	CollidableModel(void);
	~CollidableModel(void);
	void SetBoundingBox(AABoundingBox fBoundingBox) { boundingBox = fBoundingBox;}
	AABoundingBox GetBoundingBox(){ return boundingBox;}
	//calculates the bounding box of a set of vertices. the box's size can be increased/decreased using the parameter boxOffset.
	static AABoundingBox CalculateBoundingBox(std::vector<glm::vec3> vertices, float boxOffset = 0.0f);

	//handles collision, is virtual since each derived class handle collision differently.
	virtual void Collided(ObjectType);
};
#endif // CollidableModel_h__

