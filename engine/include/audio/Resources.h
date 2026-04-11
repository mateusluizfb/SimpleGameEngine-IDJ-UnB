#ifndef RESOURCES_H
#define RESOURCES_H

#define INCLUDE_SDL
#define INCLUDE_SDL_MIXER
#define INCLUDE_SDL_TTF
#include "SDL_include.h"

#include <unordered_map>

class Resources {
private:
  static std::unordered_map<std::string, SDL_Texture *> imageTable;
  static std::unordered_map<std::string, Mix_Music *> musicTable;
  static std::unordered_map<std::string, Mix_Chunk *> soundTable;
  static std::unordered_map<std::string, TTF_Font *> fontTable;

public:
  static SDL_Texture* GetImage(const std::string &file);
  static void ClearImages();

  static Mix_Music *GetMusic(const std::string &file);
  static void ClearMusics();

  static Mix_Chunk *GetSound(const std::string &file);
  static void ClearSounds();

  static TTF_Font* GetFont(const std::string &file, int fontSize);
  static void ClearFonts();
};

#endif
