#pragma once

#include "../Common/Common.h"
#include "stdint.h"

#include <algorithm>
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
  bool Create(uint8_t width,
              uint8_t height,
              const std::vector<COMMON::ECell>& pattern);
  // Функция взаимодействия с ячейкой
  bool SetCell(uint8_t x_field, uint8_t y_field, const COMMON::ECell value);
  // Функция получения игрового поля
  std::vector<COMMON::ECell> GetField();

public:
  // Максимальная ширина поля
  const uint8_t max_width = 64;
  // Максимальная высота поля
  const uint8_t max_height = 64;
  // Максимальная ширина поля
  const uint8_t min_width = 7;
  // Максимальная высота поля
  const uint8_t min_height = 7;

private:
  // Ширина поля
  uint8_t m_width = 7;
  // Высота поля
  uint8_t m_height = 7;
  // Вектор поля
  std::vector<COMMON::ECell> m_field;
};