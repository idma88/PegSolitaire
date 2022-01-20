#include "SingleMode.h"

SingleMode::SingleMode()
{
  m_mode_game = COMMON::EGameMode::SINGLE;
}

bool
SingleMode::CreateNewGame()
{
  // Вызовим родительский метод для создания игры
  if (!IGame::CreateNewGame()) return false;
  // Копируем поле
  std::vector<COMMON::ECell> fieldRaw = m_field.GetField();

  // Обновляем счёт и устанавливаем его
  uint16_t count_cell = std::count_if(fieldRaw.begin(), fieldRaw.end(), [](COMMON::ECell cell) {
    return cell == COMMON::ECell::SET;
  });

  // Обновляем счёт
  m_list_player[m_active_user].SetBeginScore(count_cell);
  return true;
}

bool
SingleMode::DoMove(uint8_t x, uint8_t y, const std::vector<COMMON::EDirect>& directions)
{
  // Сделаем направление ходов и если true, то вычесть очки
  if (!IGame::DoMove(x, y, directions)) return false;
  // Вычитвем очки
  return m_list_player[m_active_user].AddPoints(-1 * (int16_t)directions.size());
  // По дефолту вернуть false
  return false;
}
