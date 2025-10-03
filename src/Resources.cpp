#include "Game.h"
#include "Resources.h"
#include "Log.h"

std::unordered_map<std::string, SDL_Texture *> Resources::imageTable;
std::unordered_map<std::string, Mix_Music *> Resources::musicTable;
std::unordered_map<std::string, Mix_Chunk *> Resources::soundTable;

SDL_Texture* Resources::GetImage(const std::string &file)
{
  Log::info("RESOURCES - Getting image: " + file);

  auto it = imageTable.find(file);

  if (it != imageTable.end()) return it->second;

  Log::warning("RESOURCES - Image not found, loading image: " + file);

  SDL_Texture *texture = IMG_LoadTexture(Game::GetRenderer(), file.c_str());

  imageTable.emplace(file, texture);

  return texture;
}

void Resources::ClearImages()
{
  Log::info("RESOURCES - Clearing images");

  for (const std::pair<const std::string, SDL_Texture *> &pair : imageTable)
  {
    SDL_DestroyTexture(pair.second);
  }

  imageTable.clear();
}

Mix_Music* Resources::GetMusic(const std::string &file)
{
  Log::info("RESOURCES - Getting music: " + file);

  auto it = musicTable.find(file);

  if (it != musicTable.end()) return it->second;

  Log::info("RESOURCES - Music not found, loading music: " + file);

  Mix_Music *music = Mix_LoadMUS(file.c_str());

  musicTable.emplace(file, music);

  return music;
}

void Resources::ClearMusics()
{
  Log::info("RESOURCES - Clearing musics");

  for (const std::pair<const std::string, Mix_Music *> &pair : musicTable)
  {
    Mix_FreeMusic(pair.second);
  }

  musicTable.clear();
}

Mix_Chunk* Resources::GetSound(const std::string &file)
{
  Log::info("RESOURCES - Getting sound: " + file);

  auto it = soundTable.find(file);

  if (it != soundTable.end()) return it->second;

  Log::info("RESOURCES - Sound not found, loading sound: " + file);

  Mix_Chunk *sound = Mix_LoadWAV(file.c_str());

  soundTable.emplace(file, sound);

  return sound;
}

void Resources::ClearSounds()
{
  Log::info("RESOURCES - Clearing sounds");

  for (const std::pair<const std::string, Mix_Chunk *> &pair : soundTable)
  {
    Mix_FreeChunk(pair.second);
  }

  soundTable.clear();
}
