#include "Player.h"

Player::Player(const std::string& name,
               uint16_t score,
               COMMON::EPlayerType type)
  : m_name(name)
  , m_score(score)
  , m_essence(type)
{}

Player::~Player() {}

bool
Player::SetName(const std::string name)
{
  // Проверяем пустая ли строка
  if (name.empty()) {
    LOG(ERROR) << "Player::SetName : Empty name!";
    return false;
  }
  // Записываем имя
  m_name = name;
  return true;
}

bool
Player::SetEssence(const COMMON::EPlayerType type)
{
  // Проверка типа
  if ((type != COMMON::EPlayerType::HUMAN) &&
      (type != COMMON::EPlayerType::COMPUTER)) {
    LOG(ERROR)
      << "Player::SetEssence : Invalid field type value in SetEssence()!";
    return false;
  }
  // Устанавливаем сущность
  m_essence = type;
  return true;
}

bool
Player::SetBeginScore(const uint16_t score)
{
  if (score > m_max_score) {
    LOG(ERROR) << "Player::SetBeginScore : Ivalid begin data score < 0 ";
    return false;
  }
  // Обновляем счёт
  m_score = score;
  return true;
}

bool
Player::AddPoints(const int16_t score)
{
  if (((int16_t)m_score + score) < 0) {
    LOG(ERROR) << "Player::AddPoints : Ivalid data score < 0 ";
    return false;
  }
  // Обновляем счёт
  m_score = (int16_t)m_score + score;
  return true;
}

std::string
Player::GetName()
{
  // Возвращаем имя
  return m_name;
}

COMMON::EPlayerType
Player::GetEssence()
{
  // Возвращаем сущность
  return m_essence;
}

uint16_t
Player::GetScore()
{
  // Возвращаем счёт
  return m_score;
}