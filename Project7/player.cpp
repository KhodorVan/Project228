#include "constants.h"
#include "player.h"

#include <iostream>

Player::Player(
	const sf::String& file,
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

void Player::Move(int time, const std::vector<std::vector<int>>& map) {
  speed_ = 2.0;  // 0.3
  cur_frame_ += 0.05 * time;
  if (cur_frame_ > 4) {
    cur_frame_ -= 4;
  }

  sf::IntRect rectangle;
  switch (dir_) {
    case Direction::N: {
      rectangle = sf::IntRect(2 + 40 * int(cur_frame_), 168, 36, 54);
      direct_speed_.x = 0;
      direct_speed_.y = -speed_;
      break;
    }
    case Direction::S: {
      rectangle = sf::IntRect(2 + 40 * int(cur_frame_), 1, 36, 54);
      direct_speed_.x = 0;
      direct_speed_.y = speed_;
      break;
    }
    case Direction::E: {
      rectangle = sf::IntRect(7 + 40 * int(cur_frame_), 111, 22, 54);
      direct_speed_.x = speed_;
      direct_speed_.y = 0;
      break;
    }
    case Direction::W: {
      rectangle = sf::IntRect(9 + 40 * int(cur_frame_), 56, 22, 54);
      direct_speed_.x = -speed_;
      direct_speed_.y = 0;
      break;
    }
    case Direction::STAY: {
      rectangle = last_rect_;
      direct_speed_.x = 0;
      direct_speed_.y = 0;
	  return;
    }
  }
  coor_.x += direct_speed_.x * time;
  coor_.y += direct_speed_.y * time;

  int h = 54, w = 30;  // 36 ? 
  CheckMap(time, coor_.x, coor_.y, h, w, map);
	
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

void Player::CheckMap(double time, double x, double y, int h, int w,
                      const std::vector<std::vector<int>>& map) {
	x = ceil(x);
	y = ceil(y);
	int left_i = y / TILE_SIZE;
    int right_i = (y + h) / TILE_SIZE;
	int left_j = x / TILE_SIZE;
	int right_j = (x + w) / TILE_SIZE;
	  for (int i = left_i; i <= right_i; ++i) {
		for (int j = left_j; j <= right_j; ++j) {
			if (!IsCantGo(map[i][j])) continue;
			coor_.y -= direct_speed_.y * time;
			coor_.x -= direct_speed_.x * time;
			return;
		}
	  }
}
