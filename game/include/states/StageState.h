#ifndef STAGESTATE_H
#define STAGESTATE_H

#include <string>
#include <memory>
#include "GameObject.h"
#include "Music.h"
#include "TileMap.h"
#include "Zombie.h"
#include "State.h"
#include "CollisionSystem.h"

class StageState : public State
{
private:
  Music music;
  CollisionSystem collisionSystem;

public:
  StageState();
  ~StageState();

  void LoadAssets() override;
  void Start() override;
  void Pause() override;
  void Resume() override;
  void Update(float dt) override;
  void Render() override;
};

#endif
