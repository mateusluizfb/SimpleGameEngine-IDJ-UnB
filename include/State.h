#ifndef STATE_H
#define STATE_H

#include <vector>
#include <memory>
#include "GameObject.h"
#include "Character.h"

class State {
public:
  State();
  virtual ~State();

  virtual void LoadAssets() = 0;
  virtual void Update(float dt) = 0;
  virtual void Render() = 0;

  virtual void Start() = 0;
  virtual void Pause();
  virtual void Resume();

  virtual std::weak_ptr<GameObject> AddObject(GameObject* go);
  virtual std::weak_ptr<GameObject> GetObjectPtr(GameObject* go);
  std::vector<std::shared_ptr<GameObject>> GetObjectArray();
  
  bool PopRequested();
  bool QuitRequested();

  // TODO: This shouln't be here
  std::weak_ptr<GameObject> GetPlayerPtr()
  {
    for (size_t i = 0; i < objectArray.size(); i++)
    {
      Character *characterComponent = objectArray[i]->GetComponent<Character>();

      if (characterComponent != nullptr && characterComponent->player != nullptr)
      {
        return objectArray[i];
      }
    }

    return std::weak_ptr<GameObject>();
  };

protected:
  bool popRequested;
  bool quitRequested;
  bool started;
  std::vector<std::shared_ptr<GameObject>> objectArray;

  void StartArray();
  void UpdateArray(float dt);
  void RenderArray();
};

#endif
