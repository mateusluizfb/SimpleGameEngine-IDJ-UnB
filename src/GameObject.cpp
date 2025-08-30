#include "Log.h"
#include "GameObject.h"

#include <iostream>

GameObject::GameObject() : isDead(false) {}

/*
Notes:
- There might be cases where you need to **it (dereference twice), one for the iterator and another one for the pointer.
*/
GameObject::~GameObject() {
  Log::info("GAME_OBJECT - Destroying game object");

  for (auto it = components.rbegin(); it != components.rend(); ++it)
  {
    delete *it;
  }

  components.clear();
}

void GameObject::Update(float dt)
{
  Log::info("GAME_OBJECT - Updating game object");

  for(Component *component : components)
  {
    component->Update(dt);
  }
}

void GameObject::Render()
{
  Log::info("GAME_OBJECT - Rendering game object");

  for (Component *component : components)
  {
    component->Render();
  }
}

bool GameObject::IsDead()
{
  return isDead;
}

void GameObject::RequestDelete()
{
  Log::info("GAME_OBJECT - Requesting delete");

  isDead = true;
}

void GameObject::AddComponent(Component* component)
{
  Log::info("GAME_OBJECT - Adding component to game object");

  components.push_back(component);
}

void GameObject::RemoveComponent(Component *component)
{
  Log::info("GAME_OBJECT - Removing component from game object");

  components.erase(std::remove(components.begin(), components.end(), component), components.end());
}
