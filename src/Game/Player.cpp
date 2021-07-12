#include "Player.h"

Player::Player()
  : m_score(0)
  , m_essence(COMMON::EPlayerType::HUMAN)
{}

Player::~Player()
{
  /*
  code
  */
}

bool
Player::SetName(const std::string name)
{
  m_name = name;
  return true;
}

bool
Player::SetEssence(const COMMON::EPlayerType type)
{
  m_essence = type;
  return true;
}

void
Player::AddPoints(const uint32_t score)
{
  m_score = m_score + m_score;
}

COMMON::Information
Player::GetInformationPlayer()
{
  // Хранит информациюю для выдачи и перед запросом обновляется
  COMMON::Information information;
  // Обновляем данные
  information.name = m_name;
  information.score = m_score;

  return information;
}