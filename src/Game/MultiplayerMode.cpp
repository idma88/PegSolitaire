#include "MultiplayerMode.h"

MultiplayerMode::MultiplayerMode()
{
  m_mode_game = COMMON::EGameMode::MULTIPLAYER;
}

bool
MultiplayerMode::CreateNewGame()
{
  // Вызовим родительский метод для создания игры
  if (!IGame::CreateNewGame())
    return false;

  // Обновляем счёт
  for (auto& i : m_list_player) {
    if (!i.SetBeginScore(0))
      return false;
  }
  return true;
}

bool
MultiplayerMode::DoMove(uint8_t x,
                        uint8_t y,
                        const std::vector<COMMON::EDirect>& directions)
{
  // Сделаем направление ходов и если true, то вычесть очки
  if (!IGame::DoMove(x, y, directions))
    return false;

  // Добавим очки к активному игроку
  if (!m_list_player[m_active_user].AddPoints((int16_t)directions.size()))
    return false;

  // Если достигли последнего игрока, то переключим на первого
  m_active_user = (m_active_user + 1) % m_list_player.size();

  return true;
}