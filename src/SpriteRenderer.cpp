#include "Log.h"
#include "SpriteRenderer.h"
#include "GameObject.h"
#include "Sprite.h"

SpriteRenderer::SpriteRenderer(GameObject &associated)
: Component(associated), sprite(new Sprite()) {}

SpriteRenderer::SpriteRenderer(GameObject &associated, std::string file, int frameCountW, int frameCountH)
: Component(associated), sprite(new Sprite(file, frameCountW, frameCountH)) {
  associated.box.w = sprite->GetWidth();
  associated.box.h = sprite->GetHeight();

  sprite->SetFrameCount(frameCountW, frameCountH);
  sprite->SetFrame(0);
}

void SpriteRenderer::Open(std::string file)
{
  Log::info("SpriteRenderer - Opening sprite file: " + file);

  sprite->Open(file);
  associated.box.w = sprite->GetWidth();
  associated.box.h = sprite->GetHeight();
}

void SpriteRenderer::SetFrameCount(int frameCountW, int frameCountH)
{
  sprite->SetFrameCount(frameCountW, frameCountH);
}

void SpriteRenderer::SetFrame(int frame)
{
  sprite->SetFrame(frame);
}

void SpriteRenderer::Update(float dt) {
  // No update logic for static sprites
}

void SpriteRenderer::Render() {
  sprite->Render(associated.box.x, associated.box.y, associated.box.w, associated.box.h);
}
