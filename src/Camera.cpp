#include "Camera.h"
#include "InputManager.h"
#include "Log.h"

Camera& Camera::GetInstance() {
  static Camera instance; 
  return instance;
}

void Camera::Follow(GameObject* newFocus) {
  focus = newFocus;
}

void Camera::Unfollow() {
  focus = nullptr;
}

void Camera::SetPosition(float x, float y) {
  pos.x = x;
  pos.y = y;
}

void Camera::SetSpeed(float x, float y) {
  speed.x = x;
  speed.y = y;
}

void Camera::SetSpeedMultiplier(float speedMultiplier) {
  this->speedMultiplier = speedMultiplier;
}

void Camera::ResetSpeedMultiplier() {
  speedMultiplier = 1.0f;
}

float Camera::GetPositionX() {
  return pos.x * speedMultiplier;
}

float Camera::GetPositionY()
{
  return pos.y * speedMultiplier;
}

void Camera::Update(float dt) {
  // TODO: Support focus following

  if (InputManager::GetInstance().IsKeyDown(LEFT_ARROW_KEY))
    pos.x -= speed.x * dt;

  if (InputManager::GetInstance().IsKeyDown(RIGHT_ARROW_KEY))
    pos.x += speed.x * dt;

  if (InputManager::GetInstance().IsKeyDown(UP_ARROW_KEY))
    pos.y -= speed.y * dt;

  if (InputManager::GetInstance().IsKeyDown(DOWN_ARROW_KEY))
    pos.y += speed.y * dt;
}
