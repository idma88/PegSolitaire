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
  std::vector<COMMON::ECell> GetField() const;
  // Получить ширину поля
  uint8_t GetWidth() const;
  // Получить высоту поля
  uint8_t GetHeight() const;
  // Проверка поставленной фишки
  COMMON::ECell GetCell(uint8_t x, uint8_t y) const;

public:
  // Максимальная ширина поля
  static const uint8_t MAX_WIDTH = 64;
  // Максимальная высота поля
  static const uint8_t MAX_HEIGHT = 64;
  // Максимальная ширина поля
  static const uint8_t MIN_WIDTH = 7;
  // Максимальная высота поля
  static const uint8_t MIN_HEIGHT = 7;

private:
  // Ширина поля
  uint8_t m_width = 7;
  // Высота поля
  uint8_t m_height = 7;
  // Вектор поля
  std::vector<COMMON::ECell> m_field;
};