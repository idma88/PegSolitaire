#include "Field.h"

Field::Field() {}

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
    case COMMON::ETypeField::EN:
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
    case COMMON::ETypeField::EU:
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
Create(uint8_t width, uint8_t height, uint8_t* pattern)
{
  /*
    code
  */
  return true;
}

bool
Field::SetChip(uint8_t x_field, uint8_t y_field)
{
  if ((m_width <= x_field) || (m_height <= y_field)) {
    LOG(ERROR) << "The entered coordinates are out of range!";
    return false;
  }
  // Устанавливаем фишку в выбранную ячейку
  m_field[y_field * m_width + x_field] = COMMON::ECell::SET;

  return true;
}

bool
Field::ClearChip(uint8_t x_field, uint8_t y_field)
{
  if ((m_width <= x_field) || (m_height <= y_field)) {
    LOG(ERROR) << "The entered coordinates are out of range!";
    return false;
  }
  // Убираем фишку из выбранной ячейки
  m_field[y_field * m_width + x_field] = COMMON::ECell::FREE;
  return true;
}

bool
Field::LockField(uint8_t x_field, uint8_t y_field)
{
  if ((m_width <= x_field) || (m_height <= y_field)) {
    LOG(ERROR) << "The entered coordinates are out of range!";
    return false;
  }
  // Блокируем выбранное поле
  m_field[y_field * m_width + x_field] = COMMON::ECell::LOCK;
  return true;
}

std::vector<COMMON::ECell>
Field::GetField()
{
  // Возвращаем поле
  return m_field;
}