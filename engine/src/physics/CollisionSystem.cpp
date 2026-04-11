#include "CollisionSystem.h"
#include "Collider.h"
#include "Collision.h"
#include <algorithm>

CollisionSystem::CollisionSystem() {}

void CollisionSystem::Update(std::vector<std::shared_ptr<GameObject>>& objects)
{
  std::vector<std::shared_ptr<GameObject>> colliderGameObjects;
  std::copy_if(objects.begin(), objects.end(), std::back_inserter(colliderGameObjects),
               [](const std::shared_ptr<GameObject>& go) { return go->GetComponent<Collider>() != nullptr; });

  for (size_t i = 0; i < colliderGameObjects.size(); i++)
  {
    Collider* colliderA = colliderGameObjects[i]->GetComponent<Collider>();
    if (colliderA == nullptr) continue;

    for (size_t j = i + 1; j < colliderGameObjects.size(); j++)
    {
      Collider* colliderB = colliderGameObjects[j]->GetComponent<Collider>();
      if (colliderB == nullptr) continue;

      if (Collision::IsColliding(
        colliderA->GetBox(),
        colliderB->GetBox(),
        colliderGameObjects[i]->GetAngleRad(),
        colliderGameObjects[j]->GetAngleRad()
      ))
      {
        colliderGameObjects[i]->NotifyCollision(*colliderGameObjects[j]);
        colliderGameObjects[j]->NotifyCollision(*colliderGameObjects[i]);
      }
    } 
  }
}
