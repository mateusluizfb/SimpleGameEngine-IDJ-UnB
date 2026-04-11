## Instructions:

1. Make sure you have g++ and all sdl2 libs installed
2. Run `make all`
3. Run `./JOGO`

### Known Bugs:

- N/A

### Possible Improvements:

- Implement the Z/Y Sorting from the 5th lesson.
- Find a better place for collision detection, currently is all in the State class. Hard to test in isolation.
- Implement Wave Spawner Command Queue, for waiting, spawn zombie or spawn npc.
- Clear only the current state's resources on pop
- Make the title screen text blink
- Move assets loading to LoadAssets
