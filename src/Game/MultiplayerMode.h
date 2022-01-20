#pragma once

#include "IGame.h"

class MultiplayerMode : public IGame
{
public:
  // Коструктор
  MultiplayerMode();
  // Деструктор
  ~MultiplayerMode() = default;

public:
  // Переопределяем создание новой игры
  bool CreateNewGame() override;
  // Вызываем сначала метод IGame, после свой функционал
  bool DoMove(uint8_t x, uint8_t y, const std::vector<COMMON::EDirect>& directions) override;
};