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
  // Меняем длину вектора под размер поля
  m_field.resize(width * height);
  // Копируем данные из шаблона в поле
  memcpy(m_field.data(), pattern.data(), pattern.size());
  return true;
}

bool
Field::SetCell(uint8_t x_field, uint8_t y_field, COMMON::ECell value)
{
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