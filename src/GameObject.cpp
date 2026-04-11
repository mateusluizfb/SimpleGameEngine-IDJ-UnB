
#include <iostream>
#include <algorithm>
#include <cmath>
#include "Log.h"
#include "GameObject.h"

GameObject::GameObject() : started(false), isDead(false), angleDeg(0), tag("") {}

/*
Notes:
- There might be cases where you need to **it (dereference twice), one for the iterator and another one for the pointer.
*/
GameObject::~GameObject() {
  Log::info("GAME_OBJECT - Destroying game object");

  for (int i = components.size() - 1; i >= 0; --i) {
    delete components[i];
  }

  components.clear();
}

void GameObject::Start()
{
  Log::info("GAME_OBJECT - Starting game object");
  
  for (size_t i = 0; i < components.size(); i++)
  {
    components[i]->Start();
  }

  started = true;
}

void GameObject::Update(float dt)
{
  for(Component *component : components)
  {
    component->Update(dt);
  }
}

void GameObject::Render()
{
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

  if (started) {
    component->Start();
  }
}

void GameObject::RemoveComponent(Component *component)
{
  Log::info("GAME_OBJECT - Removing component from game object");

  components.erase(std::remove(components.begin(), components.end(), component), components.end());
}

float GameObject::GetAngleRad() {
  return angleDeg * (M_PI / 180.0f);
}

void GameObject::NotifyCollision(GameObject& other) {
  for (Component *component : components)
  {
    component->NotifyCollision(other);
  }
}
