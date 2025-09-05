#ifndef ANIMATOR_H
#define ANIMATOR_H

#include <string>
#include <unordered_map>
#include "Animation.h"
#include "GameObject.h"

class Animator : public Component {
private:
  std::unordered_map<std::string, Animation> animations;
  int frameStart;
  int frameEnd;
  float frameTime;
  int currentFrame;
  float timeElapsed;

public:
  Animator(GameObject &associated);

  void SetAnimation(std::string name);
  void AddAnimation(std::string name, Animation anim);

  void Update(float dt);
  void Render();
};

#endif
