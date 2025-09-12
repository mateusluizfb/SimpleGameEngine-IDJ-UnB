#include <SDL_events.h>
#include <SDL_keycode.h>

#include "Log.h"
#include "InputManager.h"

InputManager::InputManager() : quitRequested(false), updateCounter(0), mouseX(0), mouseY(0)
{
  for (int i = 0; i < 6; i++)
  {
    mouseState[i] = false;
    mouseUpdate[i] = 0;
  }
}

InputManager& InputManager::GetInstance()
{
  static InputManager instance;
  return instance;
}

InputManager::~InputManager() {
  keyState.clear();
  keyUpdate.clear();
}

void InputManager::Update()
{
  SDL_Event* event = new SDL_Event();
  int result = SDL_PollEvent(event);
  
  SDL_GetMouseState(&mouseX, &mouseY);
  quitRequested = false;
  updateCounter++;
  
  if (result == 0) {
    return;
  }

  switch (event->type)
  {
    case SDL_QUIT:
      Log::info("INPUT_MANAGER - Quit requested");
      quitRequested = true;
      break;
    case SDL_MOUSEBUTTONDOWN:
      Log::debug("INPUT_MANAGER - Mouse button " + std::to_string(event->button.button) + " down");
      mouseState[event->button.button] = true;
      mouseUpdate[event->button.button] = updateCounter;
      break;
    case SDL_MOUSEBUTTONUP:
      Log::debug("INPUT_MANAGER - Mouse button " + std::to_string(event->button.button) + " up");
      mouseState[event->button.button] = false;
      mouseUpdate[event->button.button] = updateCounter;
      break;
    case SDL_KEYDOWN:
      Log::debug("INPUT_MANAGER - Key " + std::to_string(event->key.keysym.sym) + " down");

      keyState[event->key.keysym.sym] = true;
      keyUpdate[event->key.keysym.sym] = updateCounter;
      break;
    case SDL_KEYUP:
      Log::debug("INPUT_MANAGER - Key " + std::to_string(event->key.keysym.sym) + " up");

      keyState[event->key.keysym.sym] = false;
      keyUpdate[event->key.keysym.sym] = updateCounter;
      break;
    default:
      break;
  }

  // Note Reminder: What happens if the updateCounter reaches the max int value?
  if (updateCounter < 0) {
    throw std::runtime_error("InputManager updateCounter overflow");
  }
}

bool InputManager::KeyPress(int key)
{
  return (keyState[key] && keyUpdate[key] == updateCounter);
}

bool InputManager::KeyRelease(int key)
{
  return (!keyState[key] && keyUpdate[key] == updateCounter);
}

bool InputManager::IsKeyDown(int key)
{
  return keyState[key];
}

bool InputManager::MousePress(int button)
{
  return (mouseState[button] && mouseUpdate[button] == updateCounter);
}

bool InputManager::MouseRelease(int button)
{
  return (!mouseState[button] && mouseUpdate[button] == updateCounter);
}

bool InputManager::IsMouseDown(int button)
{
  return mouseState[button];
}
int InputManager::GetMouseX()
{
  return mouseX;
}

int InputManager::GetMouseY()
{
  return mouseY;
}

bool InputManager::QuitRequested()
{
  return quitRequested;
}
