#ifndef STATE_H
#define STATE_H

#include <GameObject.h>
#include <Sprite.h>
#include <Music.h>
#include <string>

class State
{
private:
  Sprite bg;
  Music music;
  bool quitRequested;
  std::vector<std::unique_ptr<GameObject>> objectArray;

public:
  State();
  ~State();

  void AddObject(GameObject* go);
  bool QuitRequested();
  void LoadAssets();
  void Update(float dt);
  void Render();
};

#endif
