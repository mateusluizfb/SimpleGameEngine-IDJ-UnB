#include <string>
#include "TileSet.h"
#include "Log.h"

TileSet::TileSet(int tileWidth, int tileHeight, std::string file)
: tileSet(file), tileWidth(tileWidth), tileHeight(tileHeight)
{
  Log::info("TileSet::TileSet - Initing TileSet from: " + file);

  // Reminder note: Should I set the setclip here?
  tileSet.SetClip(0, 0, tileWidth, tileHeight);

  int cols = tileSet.GetWidth() / tileWidth;
  int rows = tileSet.GetHeight() / tileHeight;

  tileSet.SetFrameCount(cols, rows);
};

void TileSet::RenderTile (unsigned index, float x, float y) {
  if (index < 0 || index >= tileSet.GetFrameCount())
  {
    throw std::runtime_error("Tile index out of bounds: " + std::to_string(index));
  }

  tileSet.SetFrame(index);
  tileSet.Render(x, y, tileWidth, tileHeight);
}

int TileSet::GetTileWidth() {
  return tileWidth;
}

int TileSet::GetTileHeight()
{
  return tileHeight;
}
