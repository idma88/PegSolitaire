#include "Player.h"

Player::Player()
  : m_score(0)
  , m_essence(COMMON::EPlayerType::HUMAN)
{}

Player::~Player() {}

bool
Player::SetName(const std::string name)
{
  // Записываем имя
  m_name = name;
  return true;
}

bool
Player::SetEssence(const COMMON::EPlayerType type)
{
  // Устанавливаем сущность
  m_essence = type;
  return true;
}

void
Player::AddPoints(const uint32_t score)
{
  // Обновляем счёт
  m_score = m_score + m_score;
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

uint32_t
Player::GetScore()
{
  // Возвращаем счёт
  return m_score;
}