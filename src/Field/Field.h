#pragma once

#include "../Common/Common.h"
#include "stdint.h"

#include <iostream>
#include <memory>
#include <vector>

class Field
{
public:
  // Конструктор
  Field();
  // Деструктор
  ~Field();

public:
  // Функция создания поля
  void CreateField(uint8_t _width, uint8_t _height);

private:
  // Ширина поля
  uint8_t m_width = 0;
  // Высота поля
  uint8_t m_height = 0;
  // Вектор поля
  std::vector<COMMON::ECell> m_field;
};