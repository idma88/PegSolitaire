#include "Field.h"

Field::Field()
  : m_width(0)
  , m_height(0)
{}

Field::~Field() {}

bool
Field::Create(COMMON::ETypeField type)
{
  // Проверка типа поля
  if ((type != COMMON::ETypeField::ENGLISH) &&
      (type != COMMON::ETypeField::EUROPEAN)) {
    LOG(ERROR) << "Field::Create : Invalid field type value in Create()!";
    return false;
  }

  // Устанавливаем значения по умолчанию
  m_width = MIN_WIDTH;
  m_height = MIN_HEIGHT;

  // Меняем длину вектора под размер поля
  m_field.resize(m_width * m_height);

  switch (type) {
    // Отрисовка поля для Английской версии
    case COMMON::ETypeField::ENGLISH:
      m_field = { COMMON::ECell::LOCK, COMMON::ECell::LOCK, COMMON::ECell::SET,
                  COMMON::ECell::SET,  COMMON::ECell::SET,  COMMON::ECell::LOCK,
                  COMMON::ECell::LOCK, COMMON::ECell::LOCK, COMMON::ECell::LOCK,
                  COMMON::ECell::SET,  COMMON::ECell::SET,  COMMON::ECell::SET,
                  COMMON::ECell::LOCK, COMMON::ECell::LOCK, COMMON::ECell::SET,
                  COMMON::ECell::SET,  COMMON::ECell::SET,  COMMON::ECell::SET,
                  COMMON::ECell::SET,  COMMON::ECell::SET,  COMMON::ECell::SET,
                  COMMON::ECell::SET,  COMMON::ECell::SET,  COMMON::ECell::SET,
                  COMMON::ECell::FREE, COMMON::ECell::SET,  COMMON::ECell::SET,
                  COMMON::ECell::SET,  COMMON::ECell::SET,  COMMON::ECell::SET,
                  COMMON::ECell::SET,  COMMON::ECell::SET,  COMMON::ECell::SET,
                  COMMON::ECell::SET,  COMMON::ECell::SET,  COMMON::ECell::LOCK,
                  COMMON::ECell::LOCK, COMMON::ECell::SET,  COMMON::ECell::SET,
                  COMMON::ECell::SET,  COMMON::ECell::LOCK, COMMON::ECell::LOCK,
                  COMMON::ECell::LOCK, COMMON::ECell::LOCK, COMMON::ECell::SET,
                  COMMON::ECell::SET,  COMMON::ECell::SET,  COMMON::ECell::LOCK,
                  COMMON::ECell::LOCK };
      break;
    // Отрисовка поля для Европейской версии
    case COMMON::ETypeField::EUROPEAN:
      m_field = { COMMON::ECell::LOCK, COMMON::ECell::LOCK, COMMON::ECell::SET,
                  COMMON::ECell::SET,  COMMON::ECell::SET,  COMMON::ECell::LOCK,
                  COMMON::ECell::LOCK, COMMON::ECell::LOCK, COMMON::ECell::SET,
                  COMMON::ECell::SET,  COMMON::ECell::SET,  COMMON::ECell::SET,
                  COMMON::ECell::SET,  COMMON::ECell::LOCK, COMMON::ECell::SET,
                  COMMON::ECell::SET,  COMMON::ECell::SET,  COMMON::ECell::SET,
                  COMMON::ECell::SET,  COMMON::ECell::SET,  COMMON::ECell::SET,
                  COMMON::ECell::SET,  COMMON::ECell::SET,  COMMON::ECell::SET,
                  COMMON::ECell::FREE, COMMON::ECell::SET,  COMMON::ECell::SET,
                  COMMON::ECell::SET,  COMMON::ECell::SET,  COMMON::ECell::SET,
                  COMMON::ECell::SET,  COMMON::ECell::SET,  COMMON::ECell::SET,
                  COMMON::ECell::SET,  COMMON::ECell::SET,  COMMON::ECell::LOCK,
                  COMMON::ECell::SET,  COMMON::ECell::SET,  COMMON::ECell::SET,
                  COMMON::ECell::SET,  COMMON::ECell::SET,  COMMON::ECell::LOCK,
                  COMMON::ECell::LOCK, COMMON::ECell::LOCK, COMMON::ECell::SET,
                  COMMON::ECell::SET,  COMMON::ECell::SET,  COMMON::ECell::LOCK,
                  COMMON::ECell::LOCK };
      break;
  }

  return true;
}

bool
Field::Create(uint8_t width,
              uint8_t height,
              const std::vector<COMMON::ECell>& pattern)
{
  if ((width > MAX_WIDTH) || (height > MAX_HEIGHT)) {
    LOG(ERROR)
      << "Field::Create : Сustom field is larger than maximum constants!";
    return false;
  }

  // Проверяем вектор на наличие данных
  if (pattern.size() == 0) {
    LOG(ERROR) << "Field::Create : There is no data!";
    return false;
  }

  // Проверяем вектор на соответствие размера
  if (pattern.size() != (width * height)) {
    LOG(ERROR)
      << "Field::Create : Vector size does not fit the generated field!";
    return false;
  }

  if (!std::all_of(pattern.begin(), pattern.end(), [](COMMON::ECell item) {
        return (item == COMMON::ECell::FREE) || (item == COMMON::ECell::LOCK) ||
               (item == COMMON::ECell::SET);
      })) {
    LOG(ERROR) << "Field::Create : Invalid data type in pattern!";
    return false;
  }

  // Перепишем размеры поля
  m_width = width;
  m_height = height;
  // Меняем длину вектора под размер поля
  m_field.resize(width * height);
  // Копируем данные из шаблона в поле
  std::copy(pattern.begin(), pattern.end(), m_field.begin());
  return true;
}

bool
Field::SetCell(uint8_t x_field, uint8_t y_field, const COMMON::ECell value)
{
  // Проверка типа ячейки
  if ((value != COMMON::ECell::FREE) && (value != COMMON::ECell::LOCK) &&
      (value != COMMON::ECell::SET)) {
    LOG(ERROR) << "Field::SetCell : Invalid field type value!";
    return false;
  }

  // Проверяем диапазон
  if ((m_width <= x_field) || (m_height <= y_field)) {
    LOG(ERROR) << "Field::SetCell : The entered coordinates are out of range!";
    return false;
  }

  // Устанавливаем значение в выбранную ячейку
  m_field[y_field * m_width + x_field] = value;

  return true;
}

std::vector<COMMON::ECell>
Field::GetField() const
{
  // Возвращаем поле
  return m_field;
}

uint8_t
Field::GetWidth() const
{
  // Возвращаем ширину поля
  return m_width;
}

uint8_t
Field::GetHeight() const
{
  // Возвращаем высоту поля
  return m_height;
}

COMMON::ECell
Field::GetCell(uint8_t x, uint8_t y) const
{
  // Проверяем диапазон
  if ((m_width <= x) || (m_height <= y)) {
    LOG(ERROR) << "Field::GetCell : The entered coordinates are out of range!";
    return COMMON::ECell::LOCK;
  }

  return m_field[y * m_width + x];
}