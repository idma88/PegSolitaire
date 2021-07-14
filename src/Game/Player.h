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
  Player(const std::string& name = "User",
         uint16_t score = 0,
         COMMON::EPlayerType type = COMMON::EPlayerType::HUMAN);
  // Деструктор
  ~Player();

public:
  // Метод установки имени
  bool SetName(const std::string name);
  // Метод установки сущности
  bool SetEssence(const COMMON::EPlayerType type);
  // Установить начальный счёт
  bool SetBeginScore(const uint16_t score);
  // Добавить кол-во съеденых фишек
  bool AddPoints(const int16_t score);
  // Получить информация Имя
  std::string GetName();
  // Получить сущность
  COMMON::EPlayerType GetEssence();
  // Получить счёт
  uint16_t GetScore();

private:
  // Имя игрока
  std::string m_name = "";
  // сущность (игрок или комьютер)
  COMMON::EPlayerType m_essence = COMMON::EPlayerType::HUMAN;
  // Колличество съеденых или оставшихся фишек
  uint32_t m_score = 0;
  // Максимально возможное кол-во очков 64х64 - 2 = 4094
  uint16_t m_max_score = 4094;
};