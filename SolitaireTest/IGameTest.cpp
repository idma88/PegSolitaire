#include "../src/Game/IGame.h"
#include "../src/Common/Common.h"
#include "../src/Game/Player.h"
#include "CommonTest.h"
#include "gtest/gtest.h"

// Фикстуры ClassIGame
class IGameTest : public ::testing::TestWithParam<int>
{
public:
  // Экземпляр класса IGame
  IGame igame;

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

  LOG(INFO) << "Size player";
  LOG(INFO) << sizeof(player_1);

  LOG(INFO) << "Size list actual";
  LOG(INFO) << sizeof(ListPlayerActual);

  LOG(INFO) << "Size list expected";
  LOG(INFO) << sizeof(ListPlayerExpected);

  ASSERT_EQ(
    0,
    memcmp(&ListPlayerActual, &ListPlayerExpected, sizeof(ListPlayerActual)));
}