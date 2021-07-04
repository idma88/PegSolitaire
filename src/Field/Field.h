#pragma once

#include "../Common/Common.h"
#include "stdint.h"

#include <memory>

class Field
{
public:
  // Конструктор
  Field();
  // Деструктор
  ~Field();

public:
  // Функция создания поля
  void CreateField(uint8_t _width , uint8_t _height);

private:
  // Ширина поля
  uint8_t width = 0;
  // Высота поля
  uint8_t height = 0;
  // Указатель на создаваемое поле
  std::shared_ptr<COMMON::ECell> field;
};