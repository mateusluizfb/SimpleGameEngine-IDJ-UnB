#include "GameObject.h"

GameObject::GameObject() : isDead(false) {}

GameObject::~GameObject() {
  // TODO
}

void GameObject::Update(float dt)
{
  // TODO
}

void GameObject::Render()
{
  // TODO
}

bool GameObject::IsDead()
{
  return isDead;
}

void GameObject::RequestDelete()
{
  // TODO
}

void GameObject::AddComponent(Component* component)
{
  // TODO
}

void GameObject::RemoveComponent(Component *component)
{
  // TODO
}
