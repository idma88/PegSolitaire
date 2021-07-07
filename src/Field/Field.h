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
  bool Create(uint8_t width, uint8_t height, uint8_t* pattern);
  // Функция установки фишки
  bool SetChip(uint8_t x_field, uint8_t y_field);
  // Функция убирания фишки
  bool ClearChip(uint8_t x_field, uint8_t y_field);
  // Функция блокирования поля
  bool LockField(uint8_t x_field, uint8_t y_field);
  // Функция получения игрового поля
  std::vector<COMMON::ECell> GetField();

private:
  // Ширина поля
  uint8_t m_width = 7;
  // Высота поля
  uint8_t m_height = 7;
  // Тип поля
  COMMON::ETypeField m_type = COMMON::ETypeField::EN;
  // Вектор поля
  std::vector<COMMON::ECell> m_field;
};