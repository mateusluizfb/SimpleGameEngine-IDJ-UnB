#ifndef TILESET_H
#define TILESET_H

#include <string>
#include <Sprite.h>

//  TileSet (tileWidth : int,
// tileHeight : int,
// file : std::string)

// + RenderTile (index : unsigned,
// x : float,
// y : float) : void
// + GetTileWidth () : int
// + GetTileHeight() : int

// - tileSet : Sprite
// - tileWidth : int
// - tileHeight : int
// - tileCount : int

class TileSet {
private:
  Sprite tileSet;
  int tileWidth;
  int tileHeight;
  int tileCount;

public:
  TileSet(int tileWidth, int tileHeight, std::string file);

  void RenderTile(unsigned index, float x, float y);
  int GetTileWidth();
  int GetTileHeight();
};

#endif
