#include "Log.h"
#include "Component.h"
#include "GameObject.h"

Component::Component(GameObject &associated) : associated(associated) {}

Component::~Component() {
  Log::info("COMPONENT - Destroying component");
}

// void Component::Update(float dt) {
//   associated.Update(dt);
// }

// void Component::Render() {
//   associated.Render();
// }
