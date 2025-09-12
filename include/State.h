#ifndef STATE_H
#define STATE_H

#include <string>
#include <GameObject.h>
#include <Music.h>
#include <TileMap.h>
#include <Zombie.h>

class State
{
private:
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
  void RequestQuit();
};

#endif
