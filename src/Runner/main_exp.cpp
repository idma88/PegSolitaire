#if 0
#include "../Common/Common.h"
#include "../Field/Field.h"
#include "../Game/CoreGame.h"
#include "../Game/Player.h"

#include "../UI/Grid.h"

#include <SFML/Graphics.hpp>
// #include <glog/logging.h>
#include <iostream>

// Размер поля
const int SIZE = 7;

const int MIN_CELLS = 7;
const int MAX_CELLS = 16;

template<class T>
sf::Transform
MoveToOrigin(sf::Vector2<T> size)
{
  sf::Transform tr;
  tr.translate(-size.x / 2.f, -size.y / 2.f);
  return tr;
}

template<class T>
sf::Transform
ReturnFromOrigin(sf::Vector2<T> size)
{
  return MoveToOrigin(size).getInverse();
}

template<class T>
sf::Transform
MoveToScreenCenter(sf::Rect<T> obj, sf::Rect<T> screen)
{
  sf::Transform tr;

  sf::Vector2<T> screenCenter(screen.left + screen.width / 2.f,
                              screen.top + screen.height / 2.f);
  sf::Vector2<T> objCenter(obj.left + obj.width / 2.f,
                           obj.top + obj.height / 2.f);

  tr.translate(screenCenter.x - objCenter.x, screenCenter.y - objCenter.y);
  return tr;
}

int
main_exp(int argc, char* argv[])
{
  google::InitGoogleLogging(argv[0]);
  FLAGS_alsologtostderr = true;

  FLAGS_log_dir = "..\\..\\..\\..\\log";

  LOG(INFO) << "Start main!";

  setlocale(LC_ALL, "Russian");

  Field _field;
  bool trueCreate;
  _field.Create(COMMON::ETypeField::ENGLISH);

  trueCreate = _field.SetCell(SIZE, SIZE, COMMON::ECell::SET);

  /// Объект, который, собственно, является главным окном приложения
  sf::ContextSettings settings;
  settings.antialiasingLevel = 2;
  sf::RenderWindow window(
    sf::VideoMode(1920, 1080), "Back", sf::Style::Fullscreen, settings);

  sf::FloatRect ScreenRect(0, 0, window.getSize().x, window.getSize().y);

#pragma region "Расчёт преобразований"
  /// Матрицы для смещения центр поля в центр координат
  sf::Transform trBegin = MoveToOrigin(window.getSize());

  float angleH = -15.f * 3.1419f / 180.f;
  float angleV = 5.f * 3.1419f / 180.f;

  sf::Transform trSkew{ 1.f, sinf(angleH), 0.f, sinf(angleV), 1.f,
                        0.f, 0.f,          0.f, 1.f };

  sf::Transform trBack = ReturnFromOrigin(window.getSize());

  sf::FloatRect tmpRect = (trSkew * trBegin).transformRect(ScreenRect);

  float scale = std::min(ScreenRect.width / tmpRect.width,
                         ScreenRect.height / tmpRect.height);

  sf::Transform trScale = sf::Transform::Identity;
  trScale.scale(scale, scale);

  /// Главное преобразование
  sf::Transform tr = sf::Transform::Identity;
  tr = trBack * trScale * trSkew * trBegin;

  /// Обратное преобразования для расчёта размеров background
  sf::Transform trInv = tr.getInverse();
  /// Размер background
  sf::FloatRect greenRect = trInv.transformRect(ScreenRect);

  greenRect.left = 0;
  greenRect.top = 0;

#pragma endregion

  int CellSize = ScreenRect.height / MAX_CELLS;

#pragma region "Подготовка текстуры для рендеринга"
  sf::RenderTexture background;

  if (!background.create(greenRect.width, greenRect.height /*  , settings */)) {
    std::cout << "Error create background";
  }
  background.setSmooth(true);

  Grid grid(&background, CellSize);
#pragma endregion

  sf::Vector2f greenRectSize(greenRect.width, greenRect.height);

  tr = ReturnFromOrigin(greenRectSize) * trScale * trSkew *
       MoveToOrigin(greenRectSize) /*  * tr */;
  tmpRect = tr.transformRect(greenRect);

  grid.draw(tr);

  sf::RectangleShape _rect(sf::Vector2f(ScreenRect.width, ScreenRect.height));
  _rect.setFillColor(sf::Color::Transparent);
  _rect.setOutlineColor(sf::Color::Blue);
  _rect.setOutlineThickness(2.f);

  background.draw(_rect,
                  tr * MoveToScreenCenter(_rect.getLocalBounds(), greenRect));

  while (window.isOpen()) {
    // Зададим фон
    window.clear(sf::Color::Black);
    sf::Sprite sprite(background.getTexture());
    window.draw(sprite, MoveToScreenCenter(greenRect, ScreenRect));
    window.display();

    // check all the window's events that were triggered since the last
    // iteration of the loop
    sf::Event event;
    while (window.pollEvent(event)) {
      // "close requested" event: we close the window
      if (event.type == sf::Event::Closed)
        window.close();
    }
  }

  if (trueCreate)
    LOG(INFO) << "Success!";
  else
    LOG(ERROR) << "Error!";
  return 0;
}
#endif