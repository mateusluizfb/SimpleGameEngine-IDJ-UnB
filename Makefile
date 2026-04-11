COMPILER = g++
RMDIR = rm -rdf
RM = rm -f

DEP_FLAGS = -M -MT $@ -MT $(BIN_PATH)/$(*F).o -MP -MF $@ -Wall
LIBS = -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -lm

# Include paths for engine and game
ENGINE_INC = engine/include/core engine/include/math engine/include/rendering engine/include/physics engine/include/input engine/include/audio engine/include/tiles engine/include/camera engine/include/utils
GAME_INC = game/include/entities game/include/controllers game/include/states game/include/systems

INC_PATHS = $(addprefix -I,$(ENGINE_INC)) $(addprefix -I,$(GAME_INC)) $(addprefix -I,$(SDL_INC_PATH))

FLAGS = -std=c++11 -Wall -pedantic -Wextra -Wno-unused-parameter -Werror=init-self

DFLAGS = -ggdb -O0 -DDEBUG

RFLAGS = -O3 -mtune=native

BIN_PATH = bin
DEP_PATH = dep

# Find all source files in engine and game
ENGINE_CPP_FILES = $(wildcard engine/src/*/*.cpp)
GAME_CPP_FILES = $(wildcard game/src/*/*.cpp) game/src/Main.cpp
CPP_FILES = $(ENGINE_CPP_FILES) $(GAME_CPP_FILES)

# Create flattened object file names (replacing / with _)
OBJ_FILES = $(patsubst engine/src/%.cpp,$(BIN_PATH)/engine_%.o,$(subst /,_,$(ENGINE_CPP_FILES))) \
            $(patsubst game/src/%.cpp,$(BIN_PATH)/game_%.o,$(subst /,_,$(GAME_CPP_FILES)))

# Actually, let's use simpler naming
ENGINE_OBJ_FILES = $(foreach file,$(ENGINE_CPP_FILES),$(BIN_PATH)/$(subst /,_,$(patsubst engine/src/%.cpp,%.o,$(file))))
GAME_OBJ_FILES = $(foreach file,$(GAME_CPP_FILES),$(BIN_PATH)/$(subst /,_,$(patsubst game/src/%.cpp,%.o,$(file))))
ALL_OBJ_FILES = $(ENGINE_OBJ_FILES) $(GAME_OBJ_FILES)

EXEC = JOGO

# SE FOR WINDOWS
ifeq ($(OS),Windows_NT)
RMDIR = rd /s /q
RM = del /q

SDL_PATHS = C:/SDL2

SDL_INC_PATH += $(addsuffix /include,$(SDL_PATHS))
LINK_PATH = $(addprefix -L,$(addsuffix /lib,$(SDL_PATHS)))
FLAGS += -mwindows
DFLAGS += -mconsole
LIBS := -lmingw32 -lSDL2main $(LIBS)

EXEC := $(EXEC).exe

else

UNAME_S := $(shell uname -s)

# SE FOR MAC
ifeq ($(UNAME_S), Darwin)
	BREW_PREFIX := $(shell brew --prefix)

	LIBS = -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -lm
	SDL_INC_PATH += $(BREW_PREFIX)/include/SDL2
	LINK_PATH += -L$(BREW_PREFIX)/lib

else
# SE FOR LINUX
	SDL_INC_PATH += /usr/include/SDL2
	LINK_PATH += -L/usr/lib
endif
endif

.PHONY: all release debug clean folders help

all: $(EXEC)

$(EXEC): $(ALL_OBJ_FILES) | folders
	$(COMPILER) -o $@ $^ $(LINK_PATH) $(LIBS) $(FLAGS)

# Pattern rule for engine object files
$(BIN_PATH)/%_cpp.o: engine/src/%.cpp | folders
	$(COMPILER) $(INC_PATHS) $< -c $(FLAGS) -o $@

# Specific rules for each subdirectory in engine
$(BIN_PATH)/core_%.o: engine/src/core/%.cpp | folders
	$(COMPILER) $(INC_PATHS) $< -c $(FLAGS) -o $@

$(BIN_PATH)/math_%.o: engine/src/math/%.cpp | folders
	$(COMPILER) $(INC_PATHS) $< -c $(FLAGS) -o $@

$(BIN_PATH)/rendering_%.o: engine/src/rendering/%.cpp | folders
	$(COMPILER) $(INC_PATHS) $< -c $(FLAGS) -o $@

$(BIN_PATH)/physics_%.o: engine/src/physics/%.cpp | folders
	$(COMPILER) $(INC_PATHS) $< -c $(FLAGS) -o $@

$(BIN_PATH)/input_%.o: engine/src/input/%.cpp | folders
	$(COMPILER) $(INC_PATHS) $< -c $(FLAGS) -o $@

$(BIN_PATH)/audio_%.o: engine/src/audio/%.cpp | folders
	$(COMPILER) $(INC_PATHS) $< -c $(FLAGS) -o $@

$(BIN_PATH)/tiles_%.o: engine/src/tiles/%.cpp | folders
	$(COMPILER) $(INC_PATHS) $< -c $(FLAGS) -o $@

$(BIN_PATH)/camera_%.o: engine/src/camera/%.cpp | folders
	$(COMPILER) $(INC_PATHS) $< -c $(FLAGS) -o $@

# Game object files
$(BIN_PATH)/entities_%.o: game/src/entities/%.cpp | folders
	$(COMPILER) $(INC_PATHS) $< -c $(FLAGS) -o $@

$(BIN_PATH)/controllers_%.o: game/src/controllers/%.cpp | folders
	$(COMPILER) $(INC_PATHS) $< -c $(FLAGS) -o $@

$(BIN_PATH)/states_%.o: game/src/states/%.cpp | folders
	$(COMPILER) $(INC_PATHS) $< -c $(FLAGS) -o $@

$(BIN_PATH)/systems_%.o: game/src/systems/%.cpp | folders
	$(COMPILER) $(INC_PATHS) $< -c $(FLAGS) -o $@

$(BIN_PATH)/Main.o: game/src/Main.cpp | folders
	$(COMPILER) $(INC_PATHS) $< -c $(FLAGS) -o $@

clean:
	$(RMDIR) $(DEP_PATH)
	$(RMDIR) $(BIN_PATH)
	$(RM) $(EXEC)

release: FLAGS += $(RFLAGS)
release: $(EXEC)

debug: FLAGS += $(DFLAGS)
debug: $(EXEC)

folders:
ifeq ($(OS), Windows_NT)
	@if NOT exist $(DEP_PATH) (mkdir $(DEP_PATH))
	@if NOT exist $(BIN_PATH) (mkdir $(BIN_PATH))
else
	@mkdir -p $(DEP_PATH) $(BIN_PATH)
endif

print-% : ; echo $* = $($*)

help:
ifeq ($(OS), Windows_NT)
	echo.
endif
	@echo Available targets:
	@echo - all: Builds the game
	@echo - release: Builds the release version
	@echo - debug: Builds the debug version
	@echo - clean: Cleans generated files
	@echo - folders: Generates project directories
	@echo - help: Show help
ifeq ($(OS), Windows_NT)
	echo.
endif
