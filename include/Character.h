#ifndef CHARACTER_H
#define CHARACTER_H

#include <queue>
#include "Component.h"
#include "GameObject.h"
#include "Timer.h"
#include "Vec2.h"

enum CommandType
{
  MOVE,
  SHOOT
};

class Character : public Component
{
public:
  class Command
  {
  public:
    Command(CommandType type, float x, float y);
    CommandType type;
    Vec2 pos;
  };

  Character* player;

  Character(GameObject &associated, std::string sprite);
  ~Character();

  void Start();
  void Update(float dt);
  void Render();
  void Issue(Command command);
  std::queue<Command> GetTaskQueue();
  Vec2 GetSpeed();

private:
  std::weak_ptr<GameObject> gun;
  std::queue<Command> taskQueue;
  Vec2 speed;
  float linearSpeed;
  int hp;
  Timer deathTimer;
};

#endif
