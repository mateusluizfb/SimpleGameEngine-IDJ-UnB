#include "Sprite.h"

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
  if (texture == nullptr) return;

  Log::warning("Destroying sprite texture");

  SDL_DestroyTexture(texture);
  texture = nullptr;
}

void Sprite::Open(const std::string &file)
{
  Log::info("Opening sprite: " + file);

  if (texture != nullptr)
  {
    Log::debug("Sprite already opened, skipping: " + file);
    return;
  };

  texture = IMG_LoadTexture(Game::GetRenderer(), file.c_str());

  if (texture == nullptr)
  {
    throw std::runtime_error("Failed open texture: " + std::string(IMG_GetError()));
  }

  Log::info("Successfully opened sprite: " + file);

  int result = SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);

  if (result != 0) {
    throw std::runtime_error("Failed to query texture: " + std::string(SDL_GetError()));
  }
  
  SetClip(0, 0, width, height);

  Log::debug("Rendering sprite at: (" + std::to_string(clipRect.x) + ", " + std::to_string(clipRect.y) + ", " + std::to_string(clipRect.w) + ", " + std::to_string(clipRect.h) + ")");
}

void Sprite::SetClip(int x, int y, int w, int h)
{
  clipRect = {x, y, w, h};
}

void Sprite::Render(int x, int y)
{
  SDL_Rect dsRect = {x, y, clipRect.w, clipRect.h};

  int result = SDL_RenderCopy(Game::GetRenderer(), texture, &clipRect, &dsRect);

  if (result != 0) {
    throw std::runtime_error("Failed to render sprite: " + std::string(SDL_GetError()));
  }
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
