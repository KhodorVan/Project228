//
// Created by Vanya Khodor on 04.04.2019.
//

#include "player.h"
#include <iostream>

Player::Player(const sf::String& file,
               double x,
               double y,
               int health,
               int attack,
               int defense)
    : health_(health)
    , coor_(Coordinate(x, y))
    , attack_(attack)
    , defense_(defense)
    , file_(file) {
  image_->loadFromFile("img/" + file_);
  image_->createMaskFromColor(sf::Color(255, 255, 255));
  texture_->loadFromImage(*image_);

  sprite_->setTexture(*texture_);
  last_rect_ = sf::IntRect(2, 168, 36, 54);
  sprite_->setTextureRect(last_rect_);
  sprite_->setPosition(x, y);
}

bool Player::IsAlive() const {
  return is_alive_;
}

void Player::SetDirection(Direction new_dir) {
  dir_ = new_dir;
}

void Player::Move(double time, const std::vector<std::vector<int>>& map) {
  speed_ = 0.3;
  cur_frame_ += 0.01 * time;
  if (cur_frame_ > 4) {
    cur_frame_ -= 4;
  }

  bool left_top_angle = false, left_down_angle = false,
      right_top_angle = false, right_down_angle = false;

  sf::IntRect rectangle;
  switch (dir_) {
    case Direction::N: {
      rectangle = sf::IntRect(2 + 40 * int(cur_frame_), 168, 36, 54);
      direct_speed_.x = 0;
      direct_speed_.y = -speed_;
      left_top_angle = true;
      right_top_angle = true;
      break;
    }
    case Direction::S: {
      rectangle = sf::IntRect(2 + 40 * int(cur_frame_), 1, 36, 54);
      direct_speed_.x = 0;
      direct_speed_.y = speed_;
      left_down_angle = true;
      right_down_angle = true;
      break;
    }
    case Direction::E: {
      rectangle = sf::IntRect(7 + 40 * int(cur_frame_), 111, 22, 54);
      direct_speed_.x = speed_;
      direct_speed_.y = 0;
      right_top_angle = true;
      right_down_angle = true;
      break;
    }
    case Direction::W: {
      rectangle = sf::IntRect(9 + 40 * int(cur_frame_), 56, 22, 54);
      direct_speed_.x = -speed_;
      direct_speed_.y = 0;
      left_top_angle = true;
      left_down_angle = true;
      break;
    }
    case Direction::STAY: {
      rectangle = last_rect_;
      direct_speed_.x = 0;
      direct_speed_.y = 0;
      break;
    }
  }
  coor_.x += direct_speed_.x * time;
  coor_.y += direct_speed_.y * time;
  speed_ = 0;

  // проверяем, можем ли мы пойти в следующую клетку
  int h = 54, w = (dir_ == Direction::N || dir_ == Direction::S) ? 36 : 22;
  if (left_top_angle) {
    CheckMap(time, coor_.x, coor_.y, h, w, map);
  }
  if (left_down_angle) {
    CheckMap(time, coor_.x, coor_.y + h, h, w, map);
  }
  if (right_top_angle) {
    CheckMap(time, coor_.x + w, coor_.y, h, w, map);
  }
  if (right_down_angle) {
    CheckMap(time, coor_.x + w, coor_.y + h, h, w, map);
  }

  sprite_->setPosition(coor_.x, coor_.y);

  sprite_->setTextureRect(rectangle);
  last_rect_ = rectangle;
}

sf::Sprite* Player::GetSprite() const {
  return sprite_;
}

double Player::GetX() const {
  return coor_.x;
}

double Player::GetY() const {
  return coor_.y;
}

bool Player::IsCantGo(int type) {
  return (type >= 31 && type <= 43);
}

bool Player::CheckMap(double time, double x, double y, int h, int w,
                      const std::vector<std::vector<int>>& map) {
  int left_i = static_cast<int>(y / 64),
      right_i = static_cast<int>((y + h) / 64);
  int left_j = static_cast<int>(x / 64),
      right_j = static_cast<int>((x + w) / 64);
  for (int i = left_i; i < right_i; ++i) {
    for (int j = left_j; j < right_j; ++j) {
      if (IsCantGo(map[i][j])) {
        coor_.x -= direct_speed_.x * time;
        coor_.y -= direct_speed_.y * time;
        return true;
      }
    }
  }
  return false;
}
