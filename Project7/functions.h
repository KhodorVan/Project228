#ifndef PROJECT228_FUNCTIONS_H
#define PROJECT228_FUNCTIONS_H

#include <iostream>
#include <fstream>
#include "main_headers.h"
#include "constants.h"
#include "player.h"

struct TileInfo {
  int x;
  int y;
  int width;
  int height;

  friend std::istream& operator>>(std::istream& in, TileInfo& x);
};

std::istream& operator>>(std::istream& in, TileInfo& x) {
  in >> x.x >> x.y >> x.width >> x.height;
  return in;
}

void GetAllInformation(std::vector<std::vector<int>>& map_tiles,
                       std::vector<TileInfo>& tiles) {
  std::ifstream get_map("files/main_map.txt");
  for (int i = 0; i < MAP_HEIGHT_FIRST; ++i) {
    for (int j = 0; j < MAP_WIDTH_FIRST; ++j) {
      get_map >> map_tiles[i][j];
    }
  }

  std::fstream get_tiles("files/sprite coordinates.txt");
  for (auto& tile : tiles) {
    int nom;
    get_tiles >> nom;
    get_tiles >> tile;
  }
}

void DrawMap(sf::RenderWindow* window,
             const std::vector<std::vector<int>>& map_types,
             const std::vector<TileInfo>& tiles, sf::Sprite& map) {
  for (int i = 0; i < MAP_HEIGHT_FIRST; ++i) {
    for (int j = 0; j < MAP_WIDTH_FIRST; ++j) {
      int num = map_types[i][j] - 1;
      map.setTextureRect(sf::IntRect(tiles[num].x, tiles[num].y,
                                      tiles[num].width, tiles[num].height));

      map.setPosition(j * TILE_SIZE, i * TILE_SIZE);
      window->draw(map);
    }
  }
}

void KeyboardTreatment(Player* player) {
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
    player->SetDirection(Direction::N);
  }
  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
    player->SetDirection(Direction::W);
  }
  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
    player->SetDirection(Direction::S);
  }
  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
    player->SetDirection(Direction::E);
  }
  else {
    player->SetDirection(Direction::STAY);
  }
}

#endif  // PROJECT228_FUNCTIONS_H
