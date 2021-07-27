#include "../src/Game/IGame.h"
#include "../src/Common/Common.h"
#include "../src/Field/Field.h"
#include "../src/Game/Player.h"
#include "CommonTest.h"
#include "gtest/gtest.h"

// Фикстуры ClassIGame
class IGameTest : public ::testing::TestWithParam<int>
{
public:
  // Экземпляр класса IGame
  IGame igame;
  // Экземпляр класса Field
  Field field;
  // Направления движения
  std::vector<COMMON::EDirect> direct;

  // Экземпляры игроков
  Player player_1{ "Alex", 0, COMMON::EPlayerType::HUMAN };
  Player player_2{ "Dima", 0, COMMON::EPlayerType::HUMAN };
  Player player_3{ "Lexa", 0, COMMON::EPlayerType::HUMAN };

  // Список игроков
  std::vector<Player> ListPlayerActual;
  std::vector<Player> ListPlayerExpected;
};

// Подаваемые значения для выбора режима
// INSTANTIATE_TEST_SUITE_P(ModeL,
//                          IGameTest,
//                          ::testing::Values(COMMON::ETypeField::ENGLISH,
//                                            COMMON::ETypeField::EUROPEAN));

// TEST_P(FieldTest, CheckingPositiveTheCreationOfFields)
// {
//   // Получение возможнных параметров
//   auto xmode = static_cast<COMMON::ETypeField>(GetParam());
//   // Создание поля с для английской версии
//   ASSERT_TRUE(field.Create(xmode));
//   // Получить это поле
//   field_expected = field.GetField();
//   // Проверяем соответствие размеров
//   ASSERT_EQ(field_expected.size(), Size);
// }

TEST_F(IGameTest, CheckingSetPlayerList)
{
  // Загружаем список игроков
  ListPlayerActual.push_back(player_1);
  ListPlayerActual.push_back(player_2);
  ListPlayerActual.push_back(player_3);
  // Передаём интерфейсу список
  igame.SetPlayerList(ListPlayerActual);
  // Получаем его из класса
  ListPlayerExpected = igame.GetPlayerList();
  // Проверяем соответствие векторов
  ASSERT_TRUE(ListPlayerActual == ListPlayerExpected);
}

TEST_F(IGameTest, CheckingPositiveSetGameMode)
{
  // Устанавливаем режим одиночной игры
  auto mode = COMMON::EGameMode::SINGLE;
  // Установим игровой режим
  ASSERT_TRUE(igame.SetGameMode(mode));
  // Получаем игровой режим
  ASSERT_EQ(mode, igame.GetGameMode());

  // Устанавливаем режим многопользовательской игры
  mode = COMMON::EGameMode::MULTIPLAYER;
  // Установим игровой режим
  ASSERT_TRUE(igame.SetGameMode(mode));
  // Получаем игровой режим
  ASSERT_EQ(mode, igame.GetGameMode());
}

TEST_F(IGameTest, CheckingNegativeSetGameMode)
{
  // Устанавливаем неверное значение
  auto mode = static_cast<COMMON::EGameMode>(3);
  // Установим игровой режим
  ASSERT_FALSE(igame.SetGameMode(mode));
}

TEST_F(IGameTest, CheckingFieldMove)
{
  // Создадим поле для английской версии
  ASSERT_TRUE(field.Create(COMMON::ETypeField::ENGLISH));
  // Передадим класс IGame поле
  igame.SetField(field);
  // Проверим что не конец игры
  ASSERT_TRUE(!igame.IsGameOver());

  //  Выберем фишку x = 5, y = 3
  //    0 1 2 3 4 5 6
  //  0     • • •
  //  1     • • •
  //  2 • • • • • • •
  //  3 • • • o • X •
  //  4 • • • • • • •
  //  5     • • •
  //  6     • • •
  //  Зададим одно направление влево

  // Установим направление влево
  direct = { COMMON::EDirect::LEFT };
  // Проверим что туда можно походить
  ASSERT_TRUE(igame.CheckMove(5, 3, direct));
  // Установим значение направо
  direct = { COMMON::EDirect::RIGHT };
  // Проверим что туда нельзя походить
  ASSERT_FALSE(igame.CheckMove(5, 3, direct));

  // Проверим явно недопустимые варианты
  ASSERT_FALSE(igame.CheckMove(3, 3, direct));
  ASSERT_FALSE(igame.CheckMove(6, 6, direct));
}
