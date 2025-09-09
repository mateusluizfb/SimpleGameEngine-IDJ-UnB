#ifndef RESOURCES_H
#define RESOURCES_H

#include "SDL_render.h"
#include "SDL_mixer.h"
#include <unordered_map>

class Resources {
private:
  static std::unordered_map<std::string, SDL_Texture *> imageTable;
  static std::unordered_map<std::string, Mix_Music *> musicTable;
  static std::unordered_map<std::string, Mix_Chunk *> soundTable;

public:
  static SDL_Texture* GetImage(const std::string &file);
  static void ClearImages();

  static Mix_Music *GetMusic(const std::string &file);
  static void ClearMusics();

  static Mix_Chunk *GetSound(const std::string &file);
  static void ClearSounds();
};

#endif
