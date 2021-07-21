#pragma once

#include "../Common/Common.h"
#include "../Field/Field.h"
#include "Player.h"
#include "stdint.h"

#include <functional>
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
  // Установить игровой режим
  void SetGameMode(COMMON::EGameMode mode);
  // Создание новой игры
  virtual bool CreateNewGame();
  // Выполнение хода
  virtual bool MakingMove();
  // Загрузить копию поля
  void SetField(Field field);
  // Проверка возможности указанного хода/последовательности ходов
  bool CheckMove(uint8_t x, uint8_t y, COMMON::EDirect direct);
  // Проверка конца игры
  bool CheckTheEndOfTheGame();
  // Установить список игроков
  void SetPlayerList(std::vector<Player> lists_player);
  // Получить список игроков
  std::vector<Player> GetPlayerList();
  // Активный пользователь (тот, которому предоставлен ход)
  bool SubmitActivity(uint8_t num_player);
  // Получить номер актиавного пользователя
  uint8_t GetSubmitActivity();

private:
  // Копия экземпляра Field
  Field m_field;
  // Cписок пользователей
  std::vector<Player> m_list_player;
  // Активный пользователь
  uint8_t m_active_user = 0;
  // Режим игры
  COMMON::EGameMode m_mode_game;
};