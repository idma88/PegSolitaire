#pragma once

#include <iostream>
#include <memory>
#include <vector>

#include <SFML/Graphics.hpp>
#include <glog/logging.h>

#include "../Common/Common.h"
#include "../UI/Calculations.h"
#include "../UI/Grid.h"
#include "../UI/Scene/BaseScene.h"
#include "../UI/Scene/GameScene.h"
#include "../UI/Scene/MenuScene.h"
#include "../UI/Scene/StateScene.h"
#include "../UI/Test.h"
#include "stdint.h"

class CoreGame
{
public:
  // Конструктор
  CoreGame();

public:
  // Запуск основного цикла игры
  void Lounch();

private:
  sf::Font m_font;
  sf::Color m_colorFont;
  std::string m_fontName;
  sf::Text m_text;

  // Сетка
  Grid m_grid;
  // Поле
  Test m_test;

  // Прямоугольник поля
  sf::RectangleShape m_rectField;

  // Создадим поле
  Field& fld = Singleton<Field>::GetInstance();

  // Создадим одного игрока
  Player& playerOne = Singleton<Player>::GetInstance();

  // Выбираем одиночные режимм
  SingleMode& singleMode = Singleton<SingleMode>::GetInstance();

  // Получаем расчёты
  Calculations& calculations = Singleton<Calculations>::GetInstance();

  StateScene& currentScene = Singleton<StateScene>::GetInstance();

  // Размер поля
  sf::Vector2i SIZE;

  sf::RectangleShape rectField;

  // std::shared_ptr<BaseScene> currentScene;
};