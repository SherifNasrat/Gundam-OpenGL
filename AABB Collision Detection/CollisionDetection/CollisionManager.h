#ifndef CollisionManager_h__
#define CollisionManager_h__

#include <vector>
#include "CollidableModel.h"

class CollisionManager
{
	std::vector<CollidableModel*> collidableModels;
public:
	CollisionManager(void);
	~CollisionManager(void);
	void UpdateCollisions();
	void SetCollidableModels(std::vector<CollidableModel*> fCollidableModels);
	void AddCollidableModel(CollidableModel* model);
	void RemoveCollidableModel(int modelIndex);
	void RemoveCollidableModel(CollidableModel* model);
};

#endif // CollisionManager_h__
