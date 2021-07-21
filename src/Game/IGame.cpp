#include "IGame.h"

COMMON::EGameMode
IGame::GetGameModeInformation()
{
  // Вернём режим игры
  return m_mode_game;
}

void
IGame::SetGameMode(COMMON::EGameMode mode)
{
  m_mode_game = mode;
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
IGame::MakingMove()
{
  /*
  override in mode game
  */
  return false;
}

void
IGame::SetField(Field field)
{
  m_field = field;
}

bool
IGame::CheckMove(uint8_t x, uint8_t y, COMMON::EDirect direct)
{
  bool cell1, cell2, cell3;

  switch (direct) {
    case COMMON::EDirect::RIGHT:
      // Проверим соответствие фишки, в случае выхода за диапазон будет false
      cell1 = m_field.CheckCell(x, y, COMMON::ECell::SET);
      cell2 = m_field.CheckCell(x + 1, y, COMMON::ECell::SET);
      cell3 = m_field.CheckCell(x + 2, y, COMMON::ECell::FREE);
      // Перемножим результат соответствия
      return cell1 && cell2 && cell3;
      break;
    case COMMON::EDirect::LEFT:
      // Проверим соответствие фишки, в случае выхода за диапазон будет false
      cell1 = m_field.CheckCell(x, y, COMMON::ECell::SET);
      cell2 = m_field.CheckCell(x - 1, y, COMMON::ECell::SET);
      cell3 = m_field.CheckCell(x - 2, y, COMMON::ECell::FREE);
      // Перемножим результат соответствия
      return cell1 && cell2 && cell3;
      break;
    case COMMON::EDirect::UP:
      // Проверим соответствие фишки, в случае выхода за диапазон будет false
      cell1 = m_field.CheckCell(x, y, COMMON::ECell::SET);
      cell2 = m_field.CheckCell(x, y + 1, COMMON::ECell::SET);
      cell3 = m_field.CheckCell(x, y + 2, COMMON::ECell::FREE);
      // Перемножим результат соответствия
      return cell1 && cell2 && cell3;
      break;
    case COMMON::EDirect::DOWN:
      // Проверим соответствие фишки, в случае выхода за диапазон будет false
      cell1 = m_field.CheckCell(x, y, COMMON::ECell::SET);
      cell2 = m_field.CheckCell(x, y - 1, COMMON::ECell::SET);
      cell3 = m_field.CheckCell(x, y - 2, COMMON::ECell::FREE);
      // Перемножим результат соответствия
      return cell1 && cell2 && cell3;
      break;
  }

  return false;
}

bool
IGame::CheckTheEndOfTheGame()
{
  uint8_t width = m_field.GetWidth();
  uint8_t height = m_field.GetHeight();

  // Проверим возможность хода куда нибудь, если такой вариант имеется, то хотя
  // бы одно true вернётся
  for (int direct(0); direct < 3; direct++) {
    for (int i(0); i < width; i++) {
      for (int j(0); j < height; j++) {
        if (CheckMove(i, j, static_cast<COMMON::EDirect>(direct)))
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
IGame::GetPlayerList()
{
  // Вернём список игроков
  return m_list_player;
}

bool
IGame::SubmitActivity(uint8_t num_player)
{
  // Проверяем есть ли пользователь
  if (m_list_player.size() < num_player) {
    LOG(ERROR) << "No existing user!";
    return false;
  }

  // Устанавливаем активным его
  m_active_user = num_player;
  return true;
}

uint8_t
IGame::GetSubmitActivity()
{
  return m_active_user;
}