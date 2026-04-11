#ifndef COLLISION_SYSTEM_H
#define COLLISION_SYSTEM_H

#include <vector>
#include <memory>
#include "GameObject.h"

class CollisionSystem {
public:
  CollisionSystem();
  
  void Update(std::vector<std::shared_ptr<GameObject>>& objects);
};

#endif
