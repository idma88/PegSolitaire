#pragma once

#include "../Common/Common.h"
#include "stdint.h"

#include <glog/logging.h>
#include <iostream>
#include <string>

class Player
{
public:
  // Конструктор
  Player();
  // Деструктор
  ~Player();

public:
  // Метод установки имени
  bool SetName(const std::string name);
  // Метод установки сущности
  bool SetEssence(const COMMON::EPlayerType type);
  // Добавить кол-во съеденых фишек
  void AddPoints(const uint32_t score);
  // Получить информация об игроке
  COMMON::Information GetInformationPlayer();

private:
  // Имя игрока
  std::string m_name = "";
  // сущность (игрок или комьютер)
  COMMON::EPlayerType m_essence = COMMON::EPlayerType::HUMAN;
  // Колличество съеденых или оставшихся фишек
  uint32_t m_score = 0;
};