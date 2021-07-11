#include "Player.h"

Player::Player()
{
  /*
  code
  */
}

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
Player::SetEssence(const COMMON::ENature type)
{
  m_essence = type;
  return true;
}

void
Player::AddPoints(const uint32_t points)
{
  m_points = m_points + points;
}

void
Player::SetRemainPoints(const uint32_t remain_points)
{
  m_remain_points = m_remain_points;
}

COMMON::Information
Player::GetInformationPlayer()
{
  // Обновляем данные
  m_information.name = m_name;
  m_information.essence = m_essence;
  m_information.points = m_points;
  m_information.remain_points = m_remain_points;

  return m_information;
}