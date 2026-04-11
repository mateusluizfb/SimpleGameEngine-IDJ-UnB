#ifndef TILEMAP_H
#define TILEMAP_H

#include <vector>
#include <Component.h>

#include <memory>
#include <TileSet.h>

class TileMap : public Component {
private:
  std::vector<int> tileMatrix;
  std::unique_ptr<TileSet> tileSet;

  int mapWidth;
  int mapHeight;
  int mapDepth;

public:
  TileMap(GameObject &associated, std::string file, TileSet *tileSet);

  void Load(std::string file);
  void SetTileSet(TileSet *tileSet);
  int& At(int x, int y, int z = 0);

  void RenderLayer();
  void Render() override;
  void Update(float dt) override;

  int GetWidth();
  int GetHeight();
  int GetDepth();
  std::vector<int> GetTileMatrix();
};

#endif
