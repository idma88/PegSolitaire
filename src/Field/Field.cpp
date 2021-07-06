#include "Field.h"

Field::Field() {}

Field::~Field() {}

void
Field::Create(COMMON::ETypeField type)
{
  // Меняем длину вектора под размер поля
  m_field.resize(m_width * m_height);
  std::cout << m_field.size() << std::endl;

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
}

bool
Field::SetChip(uint8_t x_field, uint8_t y_field)
{
  if ((m_width - x_field <= 0) || (m_height - y_field <= 0)) {
    LOG(ERROR) << "The entered coordinates are out of range!";
    return false;
  }
  // Устанавливаем фишку в выбранную ячейку
  m_field[y_field * m_width + x_field] = COMMON::ECell::SET;
  std::cout << "m_field [" << y_field * m_width + x_field
            << "] = " << m_field[y_field * m_width + x_field] << std::endl;

  for (auto i : m_field) {
    std::cout << i << ' ';
  }

  return true;
}

bool
Field::ClearChip(uint8_t x_field, uint8_t y_field)
{
  if ((m_width - x_field <= 0) || (m_height - y_field <= 0)) {
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
  if ((m_width - x_field <= 0) || (m_height - y_field <= 0)) {
    LOG(ERROR) << "The entered coordinates are out of range!";
    return false;
  }
  // Блокируем выбранное поле
  m_field[y_field * m_width + x_field] = COMMON::ECell::LOCK;
  return true;
}

#pragma region InterfaceField
void
Field::SetScope(uint8_t width, uint8_t height)
{
  // Обновить приватные переменные
  m_width = width;
  m_height = height;
}

void
Field::SetType(COMMON::ETypeField type)
{
  // Обновить тип игры
  m_type = type;
}
#pragma endregion