#pragma once

#include "stdint.h"

namespace COMMON {

// Возможные состояния ячейки
enum ECell
{
  LOCK = 0,
  FREE = 1,
  SET = 2
};

enum class ETypeField
{
  ENGLISH = 0,
  EUROPEAN = 1
};
}