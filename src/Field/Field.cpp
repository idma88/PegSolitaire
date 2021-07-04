#include "Field.h"

Field::Field() {}

Field::~Field() {}

void
Field::CreateField(uint8_t width, uint8_t height)
{
  // Меняем длину вектора под размер поля
  m_field.resize(width * height);
  std::cout << m_field.size();
}
