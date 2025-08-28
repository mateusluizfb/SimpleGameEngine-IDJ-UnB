#ifndef MUSIC_H
#define MUSIC_H

#include "SDL_mixer.h"
#include <string>

class Music {
private:
  Mix_Music* music;

public:
  Music();
  Music(const std::string &file);
  ~Music();

  void Play(int times = -1);
  void Stop(int msToStop = 1500);
  void Open(const std::string &file);
  bool IsOpen();
};

#endif
