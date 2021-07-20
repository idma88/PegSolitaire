#pragma once

#include "../Common/Common.h"
#include "stdint.h"

#include <glog/logging.h>
#include <iostream>
#include <memory>
#include <vector>

class IGame
{
public:
  // Конструктор
  IGame() = default;
  // Деструктор
  ~IGame() = default;

public:
  // Получить информацию о игровом режиме
  COMMON::EGameMode GetGameModeInformation();
  // Создание новой игры
  virtual bool CreateNewGame();
  // Выполнение хода
  virtual bool MakingMove();
  // Загрузить копию поля
  void SetField(std::vector<COMMON::ECell> field,
                uint8_t width,
                uint8_t height);
  // Проверка возможности указанного хода/последовательности ходов
  bool CheckMove(uint8_t x, uint8_t y);
  // Проверка конца игры
  bool CheckTheEndOfTheGame();
  // Установить список игроков
  void SetPlayerList(uint8_t num_player);
  // Получить список игроков
  uint8_t GetPlayerList();
  // Активный пользователь (тот, которому предоставлен ход)
  bool SubmitActivity(uint8_t num_player);

private:
  // Копия игрового поля
  std::vector<COMMON::ECell> m_copy_field;
  // Копия ширина поля
  uint8_t m_copy_width = 7;
  // Копия высота поля
  uint8_t m_copy_height = 7;
  // Cписок пользователей
  std::vector<uint8_t> m_list_player;
  // Активный пользователь
  uint8_t m_active_user = 0;
  // Режим игры
  COMMON::EGameMode m_mode_game;
};