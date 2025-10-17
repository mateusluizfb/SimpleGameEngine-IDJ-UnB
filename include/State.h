#ifndef STATE_H
#define STATE_H

#include <string>
#include <GameObject.h>
#include <Music.h>
#include <TileMap.h>

#include <memory>
#include <Zombie.h>

class State
{
private:
  bool started;
  std::vector<std::shared_ptr<GameObject>> objectArray;
  Music music;
  bool quitRequested;

public:
  State();
  ~State();

  void Start();
  std::weak_ptr<GameObject> AddObject(GameObject *go);
  std::weak_ptr<GameObject> GetObjectPtr(GameObject *go);
  std::vector<std::shared_ptr<GameObject>> GetObjectArray();
  bool QuitRequested();
  void LoadAssets();
  void Update(float dt);
  void Render();
  void RequestQuit();
  std::weak_ptr<GameObject> GetPlayerPtr();
};

#endif
