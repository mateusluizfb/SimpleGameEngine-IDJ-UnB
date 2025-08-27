#ifndef SPRITE_H
#define SPRITE_H

#include <SDL_render.h>
#include <string>

class Sprite
{
private:
  SDL_Texture* texture;
  int width;
  int height;
  SDL_Rect clipRect;

public:
  Sprite();
  Sprite(const std::string &file);
  ~Sprite();

  void Open(const std::string &file);
  void SetClip(int x, int y, int w, int h);
  void Render(int x, int y);
  int GetWidth();
  int GetHeight();
  bool IsOpen();
};

#endif
