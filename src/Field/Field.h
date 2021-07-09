#pragma once

#include "../Common/Common.h"
#include "stdint.h"

#include <glog/logging.h>
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
  // Функция создания поля для EN и EU
  bool Create(COMMON::ETypeField type);
  // Функция создания произвольного поля
  bool Create(uint8_t width, uint8_t height, std::vector<COMMON::ECell>& pattern);
  // Функция взаимодействия с ячейкой
  bool SetCell(uint8_t x_field, uint8_t y_field, COMMON::ECell value);
  // Функция получения игрового поля
  std::vector<COMMON::ECell> GetField();

private:
  // Ширина поля
  uint8_t m_width = 7;
  // Высота поля
  uint8_t m_height = 7;
  // Вектор поля
  std::vector<COMMON::ECell> m_field;
};