CXX = g++
CXXFLAGS = -g -Wall -I/opt/homebrew/include/SDL2 -Iinclude
LDFLAGS = -L/opt/homebrew/lib -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf

main ?= src/Sprite.cpp src/State.cpp src/Game.cpp src/Main.cpp
extra ?=

BIN = game

build:
	$(CXX) $(CXXFLAGS) $(main) $(extra) -o $(BIN) $(LDFLAGS)

build-dry:
	$(CXX) $(CXXFLAGS) -c $(main) $(extra)

build-run: build
	./$(BIN)

clean:
	rm -f $(BIN)
	rm -f *.o src/*.o
