#ifndef SPRITE_H
#define SPRITE_H

#include "SDL_image.h"
#include "SDL_render.h"
#include <string>

class Sprite
{
private:
  SDL_Texture* texture;
  SDL_Rect clipRect;

  int width, height;
  int frameCountW, frameCountH;

public:
  bool cameraFollower;

  Sprite();
  Sprite(const std::string &file, int frameCountW = 1, int frameCountH = 1);
  ~Sprite();

  void Open(const std::string &file);
  void SetClip(int x, int y, int w, int h);
  void Render(int x, int y, int w, int h);
  int GetWidth();
  int GetHeight();
  bool IsOpen();
  void SetFrame(int frame);
  void SetFrameCount(int frameCountW, int frameCountH);
  int GetFrameCount();
};

#endif
