## Instructions:

1. Make sure you have g++ and all sdl2 libs installed
2. Run `make all`
3. Run `./JOGO`

### Known Bugs:

1. `src/Zombie.cpp - row 88` - Clicking slightly outside of the zombie's hit box, still hits it.

### Possible Improvements:

1. Move the parallax factor out of the TileMap. Maybe it's possible to create a WorldMap/Background object that encapsulates the parallax factor, and which layer it corresponds.
