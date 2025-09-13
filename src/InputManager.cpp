#include <SDL_events.h>
#include <SDL_keycode.h>

#include "Log.h"
#include "InputManager.h"
#include "Camera.h"

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
      quitRequested = true;
      break;
    case SDL_MOUSEBUTTONDOWN:
      mouseState[event->button.button] = true;
      mouseUpdate[event->button.button] = updateCounter;
      break;
    case SDL_MOUSEBUTTONUP:
      mouseState[event->button.button] = false;
      mouseUpdate[event->button.button] = updateCounter;
      break;
    case SDL_KEYDOWN:
      keyState[event->key.keysym.sym] = true;
      keyUpdate[event->key.keysym.sym] = updateCounter;
      break;
    case SDL_KEYUP:
      keyState[event->key.keysym.sym] = false;
      keyUpdate[event->key.keysym.sym] = updateCounter;
      break;
    default:
      break;
  }

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

int InputManager::GetMouseXWorld()
{
  return mouseX + Camera::GetInstance().GetPositionX();
}

int InputManager::GetMouseYWorld()
{
  return mouseY + Camera::GetInstance().GetPositionY();
}

bool InputManager::QuitRequested()
{
  return quitRequested;
}
