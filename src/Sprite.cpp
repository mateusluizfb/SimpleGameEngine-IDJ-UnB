#include "Sprite.h"
#include "Game.h"
#include "Log.h"

Sprite::Sprite() : texture(nullptr) {}

Sprite::Sprite(const std::string &file, int frameCountW, int frameCountH)
: frameCountW(frameCountW), frameCountH(frameCountH)
{
  texture = nullptr;
  Open(file);
}

Sprite::~Sprite()
{
  if (texture == nullptr) return;

  Log::info("SPRITE - Destroying sprite texture");

  SDL_DestroyTexture(texture);
  texture = nullptr;
}

void Sprite::Open(const std::string &file)
{
  Log::info("SPRITE - Opening sprite: " + file);

  if (texture != nullptr)
  {
    Log::debug("SPRITE - Sprite already opened, skipping: " + file);
    return;
  };

  texture = IMG_LoadTexture(Game::GetRenderer(), file.c_str());

  if (texture == nullptr)
  {
    throw std::runtime_error("Failed open texture: " + std::string(IMG_GetError()));
  }

  Log::info("SPRITE - Successfully opened sprite: " + file);

  int result = SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);

  if (result != 0) {
    throw std::runtime_error("Failed to query texture: " + std::string(SDL_GetError()));
  }
}

void Sprite::SetClip(int x, int y, int w, int h)
{
  clipRect = {x, y, w, h};
}

void Sprite::Render(int x, int y, int w, int h)
{
  SDL_Rect dsRect = {x, y, clipRect.w, clipRect.h};

  int result = SDL_RenderCopy(Game::GetRenderer(), texture, &clipRect, &dsRect);

  if (result != 0) {
    throw std::runtime_error("Failed to render sprite: " + std::string(SDL_GetError()));
  }
}

int Sprite::GetWidth() {
  return width;
}

int Sprite::GetHeight() {
  return height;
}

bool Sprite::IsOpen() {
  return texture != nullptr;
}

void Sprite::SetFrame(int frame) {
  /*
    Exemplo: Sprite sheet com 5 frames em 1 linha (500x100 px)
    frameCountW = 5, frameCountH = 1
    frameWidth = 500 / 5 = 100
    frameHeight = 100 / 1 = 100
    Para frame 3 (índice 2): row = 2 / 5 = 0, col = 2 % 5 = 2
    x = 2 * 100 = 200, y = 0 * 100 = 0
    SetClip(200, 0, 100, 100);
  */

  int row = frame / frameCountW; // Qual linha da sprite sheet
  int col = frame % frameCountW; // Qual coluna da sprite sheet

  int frameWidth = width / frameCountW; // Largura de cada frame na sprite sheet
  int frameHeight = height / frameCountH;  // Altura de cada frame na sprite sheet

  int x = col * frameWidth; // Posição x do frame na sprite sheet, considerando a coluna onde está
  int y = row * frameHeight; // Posição y do frame na sprite sheet, considerando a linha

  SetClip(x, y, frameWidth, frameHeight);
}

void Sprite::SetFrameCount(int frameCountW, int frameCountH) {
  this->frameCountW = frameCountW;
  this->frameCountH = frameCountH;
}

int Sprite::GetFrameCount() {
  return this->frameCountW * this->frameCountH;
}
