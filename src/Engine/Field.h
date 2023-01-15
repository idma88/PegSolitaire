#pragma once

#include "../Utils/base64.h"
#include "Common.h"
#include "stdint.h"

#include <algorithm>
#include <fstream>
#include <glog/logging.h>
#include <iostream>
#include <memory>
#include <string>
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
  bool Create(const std::string& nameField);
  // DEPRECATED
  // Функция создания произвольного поля
  // bool Create(uint8_t width, uint8_t height, const std::vector<COMMON::ECell>& pattern);

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
  // Максимальное кол-во ячеек на поле
  static const uint16_t MAX_COUNT_CELL = 256;
  // Миниммальное кол-во ячеек на поле
  static const uint16_t MIN_COUNT_CELL = 49;

private:
  // Открываем чертёж для карты
  std::string GetBlueprint(std::string nameFile);

private:
  // TODO Необходимо закодировать размеры поля в блюпринты
  uint8_t m_width = 7;
  uint8_t m_height = 7;
  // Вектор поля
  std::vector<COMMON::ECell> m_field;
};