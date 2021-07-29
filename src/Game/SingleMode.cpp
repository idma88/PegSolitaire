#include "SingleMode.h"

SingleMode::SingleMode() {}

SingleMode::~SingleMode() {}

bool
SingleMode::CreateNewGame()
{
  // Копируем поле
  std::vector<COMMON::ECell> fieldRaw = m_field.GetField();

  // Обновляем счёт и устанавливаем его
  uint8_t count_cell =
    std::count_if(fieldRaw.begin(), fieldRaw.end(), [](auto cell) {
      return cell == COMMON::ECell::SET;
    });

  // Обновляем счёт
  m_list_player[m_active_user].SetBeginScore(count_cell);
  return true;
}

bool
SingleMode::DoMove(uint8_t x,
                   uint8_t y,
                   std::vector<COMMON::EDirect> directions)
{
  // Сделаем направление ходов и если true, то вычесть очки
  if (IGame::DoMove(x, y, directions)) {
    return m_list_player[m_active_user].AddPoints((int16_t)directions.size() *
                                                  (-1));
  }
  // По дефолту вернуть false
  return false;
}
