#include "Sprite.h"

#include "Music.h"
#include "Game.h"
#include "Log.h"

Music::Music()
{
  music = nullptr;
}

Music::Music(const std::string &file)
{
  music = nullptr;
  Open(file);
}

Music::~Music()
{
  if (music == nullptr) return;

  Log::info("MUSIC - Destroying music");

  Mix_FreeMusic(music);
  music = nullptr;
}

void Music::Play(int times)
{
  if (music == nullptr) {
    throw std::runtime_error("Failed to play song: music is null");
  }

  int result = Mix_PlayMusic(music, times);

  if (result != 0) {
    throw std::runtime_error("Failed to play song: " + std::string(SDL_GetError()));
  }
}

void Music::Stop(int msToStop)
{
  Log::info("MUSIC - Fadding out song");

  int result = Mix_FadeOutMusic(msToStop);

  if (result == 0)
  {
    Log::warning("MUSIC - No song playing to fade out");
  }
}

void Music::Open(const std::string &file)
{
  Log::info("MUSIC - Opening song: " + file);

  if (music != nullptr) {
    Log::debug("MUSIC - Song already opened, skipping: " + file);
  }

  music = Mix_LoadMUS(file.c_str());

  if (music == nullptr)
  {
    throw std::runtime_error("Failed to open song: " + std::string(Mix_GetError()));
  }

  Log::info("MUSIC - Successfully opened song: " + file);
}

bool Music::IsOpen()
{
  return music != nullptr;
}
