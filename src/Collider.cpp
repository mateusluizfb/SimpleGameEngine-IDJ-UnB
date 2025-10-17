#include "Collider.h"
#include "GameObject.h"

Collider::Collider(GameObject &associated, Vec2 scale, Vec2 offset)
  : Component(associated),
    box(),
    scale(scale),
    offset(offset)
{}

void Collider::Update(float dt) {
  box = Rect(associated.box.x + offset.x,
             associated.box.y + offset.y,
             associated.box.w * scale.x,
             associated.box.h * scale.y);
}

void Collider::Render() {
  // Implementado em src/ColliderRender.cpp
}

void Collider::SetScale(Vec2 scale) {
  this->scale = scale;
}

void Collider::SetOffset(Vec2 offset) {
  this->offset = offset;
}

Rect& Collider::GetBox() {
  return box;
}
