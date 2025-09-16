#ifndef CAMERA_H
#define CAMERA_H

#include "GameObject.h"
#include "Vec2.h"

class Camera {
private:
  GameObject* focus;

public:
  Vec2 pos;
  Vec2 speed;
  float speedMultiplier = 1.0f;

  static Camera& GetInstance();

  void Follow(GameObject* newFocus);
  void Unfollow();
  void Update(float dt);

  void SetPosition(float x, float y);
  void SetSpeed(float x, float y);
  void SetSpeedMultiplier(float speedMultiplier);
  void ResetSpeedMultiplier();
  float GetPositionX();
  float GetPositionY();
};

#endif
