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

enum class EGameMode
{
  SINGLE = 0,
  MULTIPLAYER = 1
};
}