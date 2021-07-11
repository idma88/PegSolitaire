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
  bool SetEssence(const COMMON::ENature type);
  // Добавить кол-во съеденых фишек
  void AddPoints(const uint32_t points);
  // Установить кол-во оставшихся фишек
  void SetRemainPoints(const uint32_t remain_points);
  // Получить информация об игроке
  COMMON::Information GetInformationPlayer();

private:
  // Имя игрока
  std::string m_name = "";
  // сущность (игрок или комьютер)
  COMMON::ENature m_essence = COMMON::ENature::HUMAN;
  // Колличество съеденых фишек
  uint32_t m_points = 0;
  // Колличество оставшихся фишек
  uint32_t m_remain_points = 0;
  // Хранит информациюю для выдачи и перед запросом обновляется
  COMMON::Information m_information;
};