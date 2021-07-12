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
enum class EPlayerType
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
  COMMON::EPlayerType essence = COMMON::EPlayerType::HUMAN;
  // Колличество съеденых фишек
  uint32_t score = 0;
};
}