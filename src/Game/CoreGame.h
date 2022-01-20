#pragma once

#include "../Common/Common.h"
#include "stdint.h"

#include <glog/logging.h>
#include <iostream>
#include <memory>
#include <vector>

class CoreGame
{
public:
  // Конструктор
  CoreGame();
  // Деструктор
  ~CoreGame();

  // Запуск основного цикла игры
  void Lounch();

public:
  //
  void CreateNewGame();
};