#include "Log.h"
#include "Component.h"
#include "GameObject.h"

Component::Component(GameObject &associated) : associated(associated) {
  Log::info("COMPONENT - Creating component");
}

Component::~Component() {
  Log::info("COMPONENT - Destroying component");
}

void Component::Start() {}
