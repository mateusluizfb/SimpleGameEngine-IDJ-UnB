#include "Sprite.h"

#include "SDL_image.h"
#include "SDL_render.h"
#include "Game.h"
#include "Log.h"

Sprite::Sprite()
{
  texture = nullptr;
}

Sprite::Sprite(const std::string &file)
{
  texture = nullptr;
  Open(file);
}

Sprite::~Sprite()
{
  if (texture != nullptr)
  {
    SDL_DestroyTexture(texture);
    texture = nullptr;
  }
}

void Sprite::Open(const std::string &file)
{
  Log::info("Opening sprite: " + file);

  if (texture != nullptr) return;

  SDL_Texture *loadedTexture = IMG_LoadTexture(Game::GetRenderer(), file.c_str());

  if (loadedTexture == nullptr)
  {
    throw std::runtime_error("Failed open texture: " + std::string(SDL_GetError()));
  }

  Log::info("Successfully opened sprite: " + file);

  texture = loadedTexture;
  SDL_QueryTexture(loadedTexture, nullptr, nullptr, &width, &height);
  SetClip(0, 0, width, height);
}

void Sprite::SetClip(int x, int y, int w, int h)
{
  clipRect = {x, y, w, h};
}

void Sprite::Render(int x, int y)
{
  Log::info("Rendering sprite at: (" + std::to_string(x) + ", " + std::to_string(y) + ")");

  SDL_Rect dsRect = {x, y, clipRect.w, clipRect.h};
  SDL_RenderCopy(Game::GetRenderer(), texture, &clipRect, &dsRect);
}

int Sprite::GetWidth() {
  return clipRect.w;
}

int Sprite::GetHeight() {
  return clipRect.h;
}

bool Sprite::IsOpen() {
  return texture != nullptr;
}
