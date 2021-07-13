#include "../src/Game/Player.h"
#include "../src/Common/Common.h"
#include "CommonTest.h"
#include "gtest/gtest.h"

// Фикстуры ClassPlayer
class PlayerTest : public ::testing::TestWithParam<int>
{
public:
  // Экземпляр класса player
  Player player;

  // Ожидаемое значение имени
  std::string expected_name = "Sanya";
  // Пустая строка
  std::string empty_name = "";
  // Ожидаемыйы максимально возможный счёт 64х64 = 4096
  const uint16_t expected_max_score = 4096;
  const uint16_t expected_min_score = 0;
};

// Подаваемые положительные значения
INSTANTIATE_TEST_SUITE_P(Positive,
                         PlayerTest,
                         ::testing::Values(COMMON::EPlayerType::HUMAN,
                                           COMMON::EPlayerType::COMPUTER));

TEST_P(PlayerTest, CheckingPositiveValSetEssence)
{
  // Получение возможнных параметров
  auto xmode = static_cast<COMMON::EPlayerType>(GetParam());
  // Проверка возвращаемой сущности
  ASSERT_TRUE(player.SetEssence(xmode));
  // Сравниваем установленный параметр с возвращаемым значением
  ASSERT_EQ(xmode, player.GetEssence());
}

TEST_F(PlayerTest, CheckingNegativeVal)
{
  // Ожидаемое возвращаемое значение false при неверных параметрах
  ASSERT_FALSE(player.SetEssence(static_cast<COMMON::EPlayerType>(3)));
  // Ожидаемое возвращаемое значение false при пустой строке
  ASSERT_FALSE(player.SetName(empty_name));
}

TEST_F(PlayerTest, CheckingInputData)
{
  // Устанавливаем имя
  player.SetName(expected_name);
  // Проверяем возращаемое значение
  ASSERT_EQ(expected_name, player.GetName());

  // Проверим начальное значение счётчика
  ASSERT_EQ(expected_min_score, player.GetScore());

  // Добавляемый к счёту максимальное значение
  player.AddPoints(expected_max_score);
  // Сравниваем записанное значение с возвращаемым результатом
  ASSERT_EQ(expected_max_score, player.GetScore());
}
