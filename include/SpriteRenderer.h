#ifndef SPRITE_RENDERER_H
#define SPRITE_RENDERER_H

#include <string>
#include "Component.h"

class SpriteRenderer : public Component {
private:
  class Sprite* sprite;

public:
  SpriteRenderer(GameObject &associated);
  SpriteRenderer(GameObject &associated, std::string file, int frameCountW = 1, int frameCountH = 1);

  void Open(std::string file);
  void SetFrameCount(int frameCountW, int frameCountH);
  void SetFrame(int frame);

  // Notes: override flags that these methods override virtual methods in the base class
  void Update(float dt) override;
  void Render() override;
};

#endif
