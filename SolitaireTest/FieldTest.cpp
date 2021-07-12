#include "../src/Field/Field.h"
#include "../src/Common/Common.h"
#include "CommonTest.h"
#include "gtest/gtest.h"

// Фикстуры ClassField
class FieldTest : public ::testing::TestWithParam<int>
{
public:
  FieldTest() = default;
  ~FieldTest() = default;

public:
  // Экземпляр класса Field
  Field field;
  // Ожидаемое поле
  std::vector<COMMON::ECell> field_expected;
  // Размер для EN и EU полей 7x7
  const int Size = 49;
};

//! Подаваемые значения для выбора режима
INSTANTIATE_TEST_SUITE_P(ModeL, FieldTest, ::testing::Values(0, 1));

TEST_P(FieldTest, CheckingTheCreationOfFields)
{
  // Получение возможнных параметров
  auto xmode = static_cast<COMMON::ETypeField>(GetParam());
  // Создание поля с возможнными параметрами
  bool flag_create = field.Create(COMMON::ETypeField::ENGLISH);
  // Получить это поле
  field_expected = field.GetField();
  ASSERT_EQ(1, flag_create);

  if (field_expected.size() == Size)
    flag_create = 1;
  else
    flag_create = 0;

  ASSERT_EQ(1, flag_create);
}