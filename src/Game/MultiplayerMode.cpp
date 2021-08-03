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
  // Копируем поле
  std::vector<COMMON::ECell> fieldRaw = m_field.GetField();

  // Обновляем счёт и устанавливаем его
  uint16_t count_cell =
    std::count_if(fieldRaw.begin(), fieldRaw.end(), [](COMMON::ECell cell) {
      return cell == COMMON::ECell::SET;
    });

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
                        std::vector<COMMON::EDirect> directions)
{
  // Сделаем направление ходов и если true, то вычесть очки
  if (!IGame::DoMove(x, y, directions))
    return false;
  // Добавим очки к активному игроку
  return m_list_player[m_active_user].AddPoints((int16_t)directions.size());
  // По дефолту вернуть false
  return false;
}
