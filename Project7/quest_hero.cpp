#include "quest_hero.h"

QuestHero::QuestHero(
    double x, double y,
    const std::string& file_img,
    const std::string& file_for_quest,
    const std::string& file_after_quest,
    const std::string& file_for_quest_text,
    int reward, int x_img, int y_img,
    int width_img, int height_img, int passed_quest)
  : coor_(x, y)
  , image_file_(file_img)
  , file_for_quest_(file_for_quest)
  , file_after_quest_(file_after_quest)
  , file_for_quest_text_(file_for_quest_text)
  , reward_exp_(reward)
  , coor_for_img_(x_img, y_img)
  , size_for_img_(width_img, height_img)
  , passed_quest_(passed_quest) {

  image_->loadFromFile(image_file_);
  image_->createMaskFromColor(sf::Color(255, 255, 255));
  texture_->loadFromImage(*image_);
  sprite_->setTexture(*texture_);
  sf::IntRect rect(coor_for_img_.first, coor_for_img_.second, size_for_img_.first, size_for_img_.second);
  sprite_->setTextureRect(rect);
  sprite_->setPosition(x, y);

  std::ifstream get_text_for_quest(file_for_quest_);
  getline(get_text_for_quest, text_for_quest_);
  std::ifstream get_text_after_quest(file_after_quest_);
  getline(get_text_after_quest, text_after_quest_);
  std::ifstream get_task_text(file_for_quest_text);
  getline(get_task_text, task_text_);
}

const sf::Sprite* QuestHero::GetSprite() const {
  return sprite_;
}

double QuestHero::GetX() const {
  return coor_.x;
}

double QuestHero::GetY() const {
  return coor_.y;
}

std::string QuestHero::GetText() const {
  return is_quest_ready_ ? text_after_quest_ : text_for_quest_;
}

std::string QuestHero::GetTask() const {
  return task_text_;
}

bool QuestHero::IsQuestReady() const {
  return is_quest_ready_;
}

int QuestHero::GiveReward() {
  if (is_quest_ready_ && !is_exp_given_) {
    is_exp_given_ = true;
    return reward_exp_;
  }
  return 0;
}

void QuestHero::SetQuestReady() {
  is_quest_ready_ = true;
}

int QuestHero::GetPassedQuest() const {
  return passed_quest_;
}