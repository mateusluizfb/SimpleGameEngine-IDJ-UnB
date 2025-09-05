CXX = g++
CXXFLAGS = -g -Wall -std=c++17 -I/opt/homebrew/include/SDL2 -I../include
LDFLAGS = -L/opt/homebrew/lib -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -lgtest -lgtest_main -pthread

main ?= $(wildcard ../src/*.cpp)
test ?= $(wildcard ../test/*.cpp)
test_sources = $(filter-out ../src/Main.cpp, $(main)) $(wildcard ../test/*.cpp)

BIN = game

clean:
	rm -f $(BIN)
	rm -f *.o src/*.o
	rm -rf minimal_sdl2_**
	rm -rf game.**

build-test:
	$(CXX) $(CXXFLAGS) $(test_sources) -o $(BIN) $(LDFLAGS)

test: build-test
	./$(BIN)

test-bench:
	$(CXX) $(CXXFLAGS) ./TestBench.cpp -o test_bench $(LDFLAGS)
	./test_bench
	rm -f test_bench
