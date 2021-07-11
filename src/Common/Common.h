#pragma once

#include "stdint.h"
#include <string>

namespace COMMON {

// Возможные состояния ячейки
enum class ECell
{
  LOCK = 0,
  FREE = 1,
  SET = 2
};

// Тип поля
enum class ETypeField
{
  ENGLISH = 0,
  EUROPEAN = 1
};

// Игрок или компьютер
enum class ENature
{
  HUMAN = 0,
  COMPUTER = 1
};

// Структура для выдачи информации
struct Information
{
  // Имя игрока
  std::string name = "";
  // сущность (игрок или комьютер)
  COMMON::ENature essence = COMMON::ENature::HUMAN;
  // Колличество съеденых фишек
  uint32_t points = 0;
  // Колличество оставшихся фишек
  uint32_t remain_points = 0;
};
}