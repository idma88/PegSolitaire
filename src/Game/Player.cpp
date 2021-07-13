#include "Player.h"

Player::Player()
  : m_score(0)
  , m_essence(COMMON::EPlayerType::HUMAN)
{}

Player::~Player() {}

bool
Player::SetName(const std::string name)
{
  // Проверяем пустая ли строка
  if (name.empty()) {
    LOG(ERROR) << "Empty name!";
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
    LOG(ERROR) << "Invalid field type value in SetEssence()!";
    return false;
  }
  // Устанавливаем сущность
  m_essence = type;
  return true;
}

void
Player::AddPoints(const uint16_t score)
{
  // Обновляем счёт
  m_score += score;
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