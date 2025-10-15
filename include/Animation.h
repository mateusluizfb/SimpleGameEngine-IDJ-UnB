#ifndef ANIMATION_H
#define ANIMATION_H

#include <SDL_render.h>

class Animation {
public:
  int frameStart;
  int frameEnd;
  float frameTime;
  SDL_RendererFlip flip;

  Animation() : frameStart(0), frameEnd(0), frameTime(0.0f) {}
  Animation(int frameStart, int frameEnd, float frameTime, SDL_RendererFlip flip = SDL_FLIP_NONE);
};

#endif
