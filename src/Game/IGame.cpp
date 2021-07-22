#include "IGame.h"

COMMON::EGameMode
IGame::GetGameMode() const
{
  // Вернём режим игры
  return m_mode_game;
}

bool
IGame::SetGameMode(COMMON::EGameMode mode)
{
  if ((mode != COMMON::EGameMode::SINGLE) ||
      (mode != COMMON::EGameMode::MULTIPLAYER)) {
    LOG(ERROR) << "IGame::SetGameMode :  Invalid mode type value!";
    return false;
  }

  m_mode_game = mode;
  return true;
}

bool
IGame::CreateNewGame()
{
  /*
  override in mode game
  */
  return false;
}

bool
IGame::MakingMove(uint8_t x, uint8_t y, std::vector<COMMON::EDirect> directions)
{
  // Проходимся по списку направлений и меняем фишки
  for (auto dir = directions.begin(); dir != directions.end(); ++dir) {
    // В случае если нет возможности куда то походить будет false
    if (!MakingMoveField(x, y, *dir, m_field))
      return false;
    // Меняем координату X
    x += (*dir == COMMON::EDirect::RIGHT
            ? 2
            : (*dir == COMMON::EDirect::LEFT ? -2 : 0));
    // Меняем координату Y
    y +=
      (*dir == COMMON::EDirect::DOWN ? 2
                                     : (*dir == COMMON::EDirect::UP ? -2 : 0));
  }

  return true;
}

void
IGame::SetField(Field field)
{
  m_field = field;
}

bool
IGame::CheckMove(uint8_t x, uint8_t y, std::vector<COMMON::EDirect> directions)
{
  // скопируем объект
  Field copy_field = m_field;

  for (auto dir = directions.begin(); dir != directions.end(); ++dir) {
    // В случае если нет возможности куда то походить будет false
    if (!MakingMoveField(x, y, *dir, copy_field))
      return false;
    // Меняем координату X
    x += (*dir == COMMON::EDirect::RIGHT
            ? 2
            : (*dir == COMMON::EDirect::LEFT ? -2 : 0));
    // Меняем координату Y
    y +=
      (*dir == COMMON::EDirect::DOWN ? 2
                                     : (*dir == COMMON::EDirect::UP ? -2 : 0));
  }

  return true;
}

bool
IGame::CheckMovingOneCell(uint8_t x,
                          uint8_t y,
                          COMMON::EDirect direction,
                          Field& field)
{
  bool cell1, cell2, cell3;

  switch (direction) {
    case COMMON::EDirect::RIGHT:
      // Проверим соответствие фишки, в случае выхода за диапазон будет false
      cell1 = field.GetCell(x, y) == COMMON::ECell::SET;
      cell2 = field.GetCell(x + 1, y) == COMMON::ECell::SET;
      cell3 = field.GetCell(x + 2, y) == COMMON::ECell::FREE;
      // Перемножим результат соответствия
      return cell1 && cell2 && cell3;
      break;
    case COMMON::EDirect::LEFT:
      // Проверим соответствие фишки, в случае выхода за диапазон будет false
      cell1 = field.GetCell(x, y) == COMMON::ECell::SET;
      cell2 = field.GetCell(x - 1, y) == COMMON::ECell::SET;
      cell3 = field.GetCell(x - 2, y) == COMMON::ECell::FREE;
      // Перемножим результат соответствия
      return cell1 && cell2 && cell3;
      break;
    case COMMON::EDirect::UP:
      // Проверим соответствие фишки, в случае выхода за диапазон будет false
      cell1 = field.GetCell(x, y) == COMMON::ECell::SET;
      cell2 = field.GetCell(x, y - 1) == COMMON::ECell::SET;
      cell3 = field.GetCell(x, y - 2) == COMMON::ECell::FREE;
      // Перемножим результат соответствия
      return cell1 && cell2 && cell3;
      break;
    case COMMON::EDirect::DOWN:
      // Проверим соответствие фишки, в случае выхода за диапазон будет false
      cell1 = field.GetCell(x, y) == COMMON::ECell::SET;
      cell2 = field.GetCell(x, y + 1) == COMMON::ECell::SET;
      cell3 = field.GetCell(x, y + 2) == COMMON::ECell::FREE;
      // Перемножим результат соответствия
      return cell1 && cell2 && cell3;
      break;
  }

  return false;
}

bool
IGame::MakingMoveField(uint8_t x,
                       uint8_t y,
                       COMMON::EDirect direction,
                       Field& field)
{
  uint8_t width = m_field.GetWidth();
  uint8_t height = m_field.GetHeight();

  // Проверяем диапазон
  if ((width <= x) || (height <= y)) {
    LOG(ERROR) << "Field::MakingMoveCopyField : The entered coordinates are "
                  "out of range!";
    return false;
  }

  switch (direction) {
    case COMMON::EDirect::RIGHT:
      field.SetCell(x, y, COMMON::ECell::FREE);
      field.SetCell(x + 1, y, COMMON::ECell::FREE);
      field.SetCell(x + 2, y, COMMON::ECell::SET);
      return true;
      break;
    case COMMON::EDirect::LEFT:
      field.SetCell(x, y, COMMON::ECell::FREE);
      field.SetCell(x - 1, y, COMMON::ECell::FREE);
      field.SetCell(x - 2, y, COMMON::ECell::SET);
      return true;
      break;
    case COMMON::EDirect::UP:
      field.SetCell(x, y, COMMON::ECell::FREE);
      field.SetCell(x, y - 1, COMMON::ECell::FREE);
      field.SetCell(x, y - 2, COMMON::ECell::SET);
      return true;
      break;
    case COMMON::EDirect::DOWN:
      field.SetCell(x, y, COMMON::ECell::FREE);
      field.SetCell(x, y + 1, COMMON::ECell::FREE);
      field.SetCell(x, y + 2, COMMON::ECell::SET);
      return true;
      break;
  }

  return false;
}

bool
IGame::IsGameOver()
{
  uint8_t width = m_field.GetWidth();
  uint8_t height = m_field.GetHeight();

  // Проверим возможность хода куда нибудь, если такой вариант имеется, то хотя
  // бы одно true вернётся
  for (int i(0); i < width; i++) {
    for (int j(0); j < height; j++) {
      for (int direct(0); direct < 4; direct++) {
        if (CheckMovingOneCell(
              i, j, static_cast<COMMON::EDirect>(direct), m_field))
          return true;
      }
    }
  }

  return false;
}

void
IGame::SetPlayerList(std::vector<Player> lists_player)
{
  // Установим список игроков
  m_list_player = lists_player;
}

std::vector<Player>
IGame::GetPlayerList() const
{
  // Вернём список игроков
  return m_list_player;
}

uint8_t
IGame::GetActivePlayerId() const
{
  return m_active_user;
}