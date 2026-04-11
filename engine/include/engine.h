#ifndef ENGINE_H
#define ENGINE_H

// Core
#include "core/Game.h"
#include "core/State.h"
#include "core/GameObject.h"
#include "core/Component.h"

// Math
#include "math/Vec2.h"
#include "math/Rect.h"
#include "math/Timer.h"

// Rendering
#include "rendering/Sprite.h"
#include "rendering/SpriteRenderer.h"
#include "rendering/Animation.h"
#include "rendering/Animator.h"
#include "rendering/Text.h"

// Physics
#include "physics/Collider.h"
#include "physics/Collision.h"
#include "physics/CollisionSystem.h"

// Input
#include "input/InputManager.h"

// Audio
#include "game/audio/Music.h"
#include "game/audio/Sound.h"
#include "game/audio/Resources.h"

// Tiles
#include "tiles/TileMap.h"
#include "tiles/TileSet.h"

// Camera
#include "camera/Camera.h"

// Utilities
#include "utils/Log.h"
#include "utils/SDL_include.h"

#endif
