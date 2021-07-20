#include "IGame.h"

COMMON::EGameMode
IGame::GetGameModeInformation()
{
  // Вернём режим игры
  return m_mode_game;
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
IGame::SetField(std::vector<COMMON::ECell> field, uint8_t width, uint8_t height)
{
  // Копируем поле
  m_copy_field = field;
  // Копируем ширину поля
  m_copy_width = width;
  // Копируем высоту поля
  m_copy_height = height;
}

bool
IGame::CheckMove(uint8_t x, uint8_t y)
{
  std::vector<COMMON::ECell> sample_vec = { COMMON::ECell::SET,
                                            COMMON::ECell::SET,
                                            COMMON::ECell::FREE };

  std::vector<COMMON::ECell> temp_vec = { COMMON::ECell::FREE,
                                          COMMON::ECell::FREE,
                                          COMMON::ECell::FREE };

  // 1 - куда возможен ход 0 - не возможен
  struct ChanceDirect
  {
    uint8_t RIGHT = 0;
    uint8_t LEFT = 0;
    uint8_t UP = 0;
    uint8_t DOWN = 0;
  };

  ChanceDirect _chance_direct;

  if (y * m_copy_width + x + 2 < Field::MAX_WIDTH * Field::MAX_HEIGHT) {
    temp_vec[0] = m_copy_field[y * m_copy_width + x];
    temp_vec[1] = m_copy_field[y * m_copy_width + x + 1];
    temp_vec[2] = m_copy_field[y * m_copy_width + x + 2];
  } else {
    _chance_direct.RIGHT = 0;
  }

  if (temp_vec == sample_vec)
    _chance_direct.RIGHT = 1;

  temp_vec = { COMMON::ECell::FREE, COMMON::ECell::FREE, COMMON::ECell::FREE };

  if (y * m_copy_width + x - 2 >= 0) {
    temp_vec[0] = m_copy_field[y * m_copy_width + x];
    temp_vec[1] = m_copy_field[y * m_copy_width + x - 1];
    temp_vec[2] = m_copy_field[y * m_copy_width + x - 2];
  } else {
    _chance_direct.LEFT = 0;
  }

  if (temp_vec == sample_vec)
    _chance_direct.LEFT = 1;

  temp_vec = { COMMON::ECell::FREE, COMMON::ECell::FREE, COMMON::ECell::FREE };

  if (y * m_copy_width + x - m_copy_width * 2 >= 0) {
    temp_vec[0] = m_copy_field[y * m_copy_width + x];
    temp_vec[1] = m_copy_field[y * m_copy_width + x - m_copy_width];
    temp_vec[2] = m_copy_field[y * m_copy_width + x - m_copy_width * 2];
  } else {
    _chance_direct.UP = 0;
  }

  if (temp_vec == sample_vec)
    _chance_direct.UP = 1;

  temp_vec = { COMMON::ECell::FREE, COMMON::ECell::FREE, COMMON::ECell::FREE };

  if (y * m_copy_width + x + m_copy_width * 2 <
      Field::MAX_WIDTH * Field::MAX_HEIGHT) {
    temp_vec[0] = m_copy_field[y * m_copy_width + x];
    temp_vec[1] = m_copy_field[y * m_copy_width + x + m_copy_width];
    temp_vec[2] = m_copy_field[y * m_copy_width + x + m_copy_width * 2];
  } else {
    _chance_direct.UP = 0;
  }
  if (temp_vec == sample_vec)
    _chance_direct.UP = 1;

  temp_vec = { COMMON::ECell::FREE, COMMON::ECell::FREE, COMMON::ECell::FREE };
}

// ***************ПОМЕТКА****************
// Предварительные проверки, необходимо добавить граничные условия, понять
// зависимость и сократить код!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//                         x
//                         o
//                     x o i o x
//                         o
//                         x
//
// Проверяет возможен ли переход от i к x при условии что o - установлена
// фишка, x - свободное пространство, i - выбранная фишка

// Проверка для горизонтали
if ((m_copy_field[y * m_copy_width + x + 2] == COMMON::ECell::FREE) &&
    (m_copy_field[x + 1] == COMMON::ECell::SET))
  return true;
if ((m_copy_field[y * m_copy_width + x - 2] == COMMON::ECell::FREE) &&
    (m_copy_field[y * m_copy_width + x - 1] == COMMON::ECell::SET))
  return true;
// Проверка для вертикали
if ((m_copy_field[y * m_copy_width + x - m_copy_width * 2] ==
     COMMON::ECell::FREE) &&
    (m_copy_field[y * m_copy_width + x - m_copy_width] == COMMON::ECell::SET))
  return true;
if ((m_copy_field[y * m_copy_width + x + m_copy_width * 2] ==
     COMMON::ECell::FREE) &&
    (m_copy_field[y * m_copy_width + x + m_copy_width] == COMMON::ECell::SET))
  return true;

return false;
}

bool
IGame::CheckTheEndOfTheGame()
{
  // Конец игры определяется тем, когда некуда ходить, а именно что нет рядом
  // двух фишек

  // ***************ПОМЕТКА****************
  // Большая куча говна, в тоерии она заработает если наложить ограничения, но
  // это кусок говна
  // Подумать и переделать !!!!

  for (int i(0); i < (int)m_copy_field.size(); ++i) {
    // По оси х в плюс
    if ((m_copy_field[i] == COMMON::ECell::SET) &&
        (m_copy_field[i + 1] == COMMON::ECell::SET))
      return false;
    // По оси х в минус
    if ((m_copy_field[i] == COMMON::ECell::SET) &&
        (m_copy_field[i - 1] == COMMON::ECell::SET))
      return false;
    // По оси y в плюс
    if ((m_copy_field[i] == COMMON::ECell::SET) &&
        (m_copy_field[i + m_copy_width] == COMMON::ECell::SET))
      return false;
    // По оси y в минус
    if ((m_copy_field[i] == COMMON::ECell::SET) &&
        (m_copy_field[i - m_copy_width] == COMMON::ECell::SET))
      return false;
  }
  return true;
}

void
IGame::SetPlayerList(uint8_t num_player)
{
  // Возможно сделать какие нибудь проверки

  // Переопределим размер вектора
  m_list_player.resize(num_player);
}

uint8_t
IGame::GetPlayerList()
{
  return (uint8_t)m_list_player.size();
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

// O  O  O  O  O  O  O
// O  O  O  O  O  O  O
// O  O  O  O  O  O  O
// O  O  O  O  O  O  O
// O  O  O  O  O  O  O
// O  O  O  O  O  O  O
// O  O  O  O  O  O  O

// ixOOOOO | OOOOOOO | OOOOOOO | OOOOOOO | OOOOOOO | OOOOOOO | OOOOOOO
// xixxOOO | OOOOOOO | OOOOOOO | OOOOOOO | OOOOOOO | OOOOOOO | OOOOOOO

// OOOOOxi | OOOOOOO | OOOOOOO | OOOOOOO | OOOOOOO | OOOOOOO | OOOOOOO
// OOOOOOx | ixOOOOO | OOOOOOO | OOOOOOO | OOOOOOO | OOOOOOO | OOOOOOO

// OOOOOOO | OOOOOOO | OOOOOOO | OOOOOOO | OOOOOOO | OOOOOxi | xOOOOOO
// OOOOOOO | OOOOOOO | OOOOOOO | OOOOOOO | OOOOOOO | OOOOOOO | OOOOOxi