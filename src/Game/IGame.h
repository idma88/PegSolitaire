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
  IGame();
  // Деструктор
  ~IGame();

public:
  // Получить информацию о игровом режиме
  void GetGameModeInformation();
  // Создание новой игры
  bool CreateNewGame();
  // Проверка возможности указанного хода/последовательности ходов
  bool CheckMove(uint8_t x, uint8_t y);
  // Выполнение хода
  void MakingMove();
  // Проверка конца игры
  void CheckTheEndOfTheGame();
  // Установить список игроков
  void SetPlayerList(uint8_t num_player);
  // Получить список игроков
  uint8_t GetPlayerList();
  // Активный пользователь (тот, которому предоставлен ход)
  bool SubmitActivity(uint8_t num_player);

private:
  // Копия игрового поля
  std::vector<COMMON::ECell> m_field;
  // Cписок пользователей
  std::vector<uint8_t> m_list_player;
  // Активный пользователь
  uint8_t m_active_user;
  // Режим игры
  COMMON::EGameMode m_mode_game;
};