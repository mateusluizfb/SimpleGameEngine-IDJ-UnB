#include <gtest/gtest.h>
#include <vector>
#include "Game.h"
#include "Log.h"
#include "TileMap.h"
#include "TileSet.h"

TEST(TileMapTest, Constructor)
{
  Game *game = &Game::GetInstance("Test Game", 800, 600);

  Log::debug(" --- TileMapTest Logs ----");
  GameObject *obj = new GameObject();
  TileSet *tileSet = new TileSet(64, 64, "assets/img/Tileset.png");
  TileMap *tileMap = new TileMap(*obj, "assets/map/map.txt", tileSet);

  std::vector<int> matrix = tileMap->GetTileMatrix(); 

  EXPECT_EQ(tileMap->GetWidth(), 40);
  EXPECT_EQ(tileMap->GetHeight(), 40);
  EXPECT_EQ(tileMap->GetDepth(), 2);
  EXPECT_EQ(matrix.size(), 3200);

  delete obj;
  delete tileSet;
  delete game;
}

TEST(TileMapTest, At) 
{
  Game *game = &Game::GetInstance("Test Game", 800, 600);

  Log::debug(" --- TileMapTest At Method Logs ----");
  GameObject *obj = new GameObject();
  TileSet *tileSet = new TileSet(64, 64, "assets/img/Tileset.png");
  TileMap *tileMap = new TileMap(*obj, "assets/map/map.txt", tileSet);

  EXPECT_EQ(tileMap->At(0, 0, 0), 5);
  EXPECT_EQ(tileMap->At(1, 1, 0), 12);
  EXPECT_EQ(tileMap->At(0, 0, 1), 0);
  EXPECT_EQ(tileMap->At(1, 1, 1), 0);

  EXPECT_THROW(tileMap->At(-1, 0, 0), std::out_of_range);
  EXPECT_THROW(tileMap->At(0, -1, 0), std::out_of_range);
  EXPECT_THROW(tileMap->At(0, 0, -1), std::out_of_range);
  EXPECT_THROW(tileMap->At(40, 0, 0), std::out_of_range);
  EXPECT_THROW(tileMap->At(0, 40, 0), std::out_of_range);
  EXPECT_THROW(tileMap->At(0, 0, 2), std::out_of_range);

  delete obj;
  delete tileSet;
  delete game;
}
