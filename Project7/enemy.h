#ifndef NEWPROJECT228_ENEMY_H
#define NEWPROJECT228_ENEMY_H

#include "bullet.h"
#include "main_headers.h"
#include "useful.h"
#include <string>

class Enemy {
 public:

  Enemy(double, double,
        const std::string&, int, int,
        int, int, int, int, int, int, int);

  void SetDirection(Direction);

  const sf::Sprite* GetSprite() const;
  double GetX() const;
  double GetY() const;
  bool IsOnBound() const;
  bool IsCorrect(Direction) const;

  int GiveReward();

  Direction GetLastDirection() const;

  void Move(int, const std::vector<std::vector<int>>&);

 private:

  sf::Vector2f coor_;

  std::string image_file_;

  int reward_exp_;

  sf::Vector2i coor_for_img_;
  sf::Vector2i size_for_img_;

  int health_;
  int defense_;
  int attack_;

  sf::Image* image_ = new sf::Image;
  sf::Texture* texture_ = new sf::Texture;
  sf::Sprite* sprite_ = new sf::Sprite;

  sf::Vector2i coor_map_tile_left_;
  sf::Vector2i coor_map_tile_right_;

  //  пока не знаю, нужно ли
  bool is_exp_given_ = false;

  //  хранит номер квеста, который завершает данный герой
  //  если таковой имеется
  int passed_quest_;

  bool is_exist_ = true;

  Bullet* bullet_ = new Bullet;
  Direction dir_ = Direction::kStay;
  Direction last_dir_ = Direction::kStay;
  double cur_frame_ = 0;
  sf::IntRect last_rect_ = sf::IntRect(0, 0, 0, 0);
  sf::Vector2f direct_speed_ = sf::Vector2f(0, 0);

  bool IsCantGo(int) const;
  void CheckMap(double, double, double, int, int,
                const std::vector<std::vector<int>>&);
};

#endif //NEWPROJECT228_ENEMY_H