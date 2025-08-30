#include "Component.h"
#include "Log.h"

Component::Component(GameObject &associated) : associated(associated) {}

Component::~Component() {
  Log::info("COMPONENT - Destroying component");
}
