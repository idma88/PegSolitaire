#include "Field.h"

Field::Field()
  : m_width(0)
  , m_height(0)
{}

Field::~Field() {}

bool
Field::Create(COMMON::ETypeField type)
{
  // Устанавливаем значения по умолчанию
  m_width = 7;
  m_height = 7;
  // Меняем длину вектора под размер поля
  m_field.resize(m_width * m_height);

  switch (type) {
    // Отрисовка поля для Английской версии
    case COMMON::ETypeField::ENGLISH:
      m_field = {
        COMMON::LOCK, COMMON::LOCK, COMMON::SET,  COMMON::SET,  COMMON::SET,
        COMMON::LOCK, COMMON::LOCK, COMMON::LOCK, COMMON::LOCK, COMMON::SET,
        COMMON::SET,  COMMON::SET,  COMMON::LOCK, COMMON::LOCK, COMMON::SET,
        COMMON::SET,  COMMON::SET,  COMMON::SET,  COMMON::SET,  COMMON::SET,
        COMMON::SET,  COMMON::SET,  COMMON::SET,  COMMON::SET,  COMMON::FREE,
        COMMON::SET,  COMMON::SET,  COMMON::SET,  COMMON::SET,  COMMON::SET,
        COMMON::SET,  COMMON::SET,  COMMON::SET,  COMMON::SET,  COMMON::SET,
        COMMON::LOCK, COMMON::LOCK, COMMON::SET,  COMMON::SET,  COMMON::SET,
        COMMON::LOCK, COMMON::LOCK, COMMON::LOCK, COMMON::LOCK, COMMON::SET,
        COMMON::SET,  COMMON::SET,  COMMON::LOCK, COMMON::LOCK
      };
      break;
    // Отрисовка поля для Европейской версии
    case COMMON::ETypeField::EUROPEAN:
      m_field = {
        COMMON::LOCK, COMMON::LOCK, COMMON::SET,  COMMON::SET,  COMMON::SET,
        COMMON::LOCK, COMMON::LOCK, COMMON::LOCK, COMMON::SET,  COMMON::SET,
        COMMON::SET,  COMMON::SET,  COMMON::SET,  COMMON::LOCK, COMMON::SET,
        COMMON::SET,  COMMON::SET,  COMMON::SET,  COMMON::SET,  COMMON::SET,
        COMMON::SET,  COMMON::SET,  COMMON::SET,  COMMON::SET,  COMMON::FREE,
        COMMON::SET,  COMMON::SET,  COMMON::SET,  COMMON::SET,  COMMON::SET,
        COMMON::SET,  COMMON::SET,  COMMON::SET,  COMMON::SET,  COMMON::SET,
        COMMON::LOCK, COMMON::SET,  COMMON::SET,  COMMON::SET,  COMMON::SET,
        COMMON::SET,  COMMON::LOCK, COMMON::LOCK, COMMON::LOCK, COMMON::SET,
        COMMON::SET,  COMMON::SET,  COMMON::LOCK, COMMON::LOCK
      };
      break;
  }

  return true;
}

bool
Field::Create(uint8_t width,
              uint8_t height,
              std::vector<COMMON::ECell>& pattern)
{
  // Проверяем размеры от 7x7 до 64x64
  if (((max_width < width) && (width < min_width)) ||
      ((max_height < height) && (height < min_height))) {
    LOG(ERROR) << "The entered coordinates are out of range!";
    return false;
  }

  // Проверяем вектор на наличие данных
  if (pattern.size() == 0) {
    LOG(ERROR) << "There is no data!";
    return false;
  }

  // Проверяем вектор на соответствие размера
  if (pattern.size() != (width * height)) {
    LOG(ERROR) << "Vector size does not fit the generated field!";
    return false;
  }

  if (!std::all_of(pattern.begin(), pattern.end(), [](COMMON::ECell item) {
        return (item == COMMON::ECell::FREE) || (item == COMMON::ECell::LOCK) ||
               (item == COMMON::ECell::SET);
      })) {
    LOG(ERROR) << "Invalid data type in pattern!";
    return false;
  }

  // Меняем длину вектора под размер поля
  m_field.resize(width * height);
  // Копируем данные из шаблона в поле
  memcpy(
    m_field.data(), pattern.data(), std::min(m_field.size(), pattern.size()));
  return true;
}

bool
Field::SetCell(uint8_t x_field, uint8_t y_field, COMMON::ECell value)
{
  // Проверяем диапазон
  if ((m_width <= x_field) || (m_height <= y_field)) {
    LOG(ERROR) << "The entered coordinates are out of range!";
    return false;
  }
  // Устанавливаем значение в выбранную ячейку
  m_field[y_field * m_width + x_field] = value;
  return true;
}

std::vector<COMMON::ECell>
Field::GetField()
{
  // Возвращаем поле
  return m_field;
}