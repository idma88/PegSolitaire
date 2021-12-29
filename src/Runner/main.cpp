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

template<class T>
void
MoveToScreenCenter(sf::RectangleShape* obj, sf::Rect<T> screen)
{
  sf::Vector2<T> screenCenter(screen.left + screen.width / 2.f,
                              screen.top + screen.height / 2.f);

  sf::Vector2f positionObj = obj->getPosition();
  sf::Vector2f sizeObj = obj->getSize();

  sf::Vector2<T> objCenter(positionObj.x + sizeObj.x / 2.f,
                           positionObj.y + sizeObj.y / 2.f);

  float offset_x = screenCenter.x - objCenter.x;
  float offset_y = screenCenter.y - objCenter.y;

  obj->setPosition(offset_x, offset_y);
}

void
CalculatePoints(sf::VertexArray& m_points,
                sf::Vector2f m_size,
                sf::Vector2f position,
                uint32_t m_cellSize)
{
  /// Кол-во точек для всех линий
  m_points.resize(2 * ((m_size.x + m_size.y) / m_cellSize + 2));

  uint32_t index = 0;

  /// Смещение к центру по оси х
  uint32_t offset = uint32_t(m_size.x / 2) % m_cellSize;
  for (float i = position.x; i < (m_size.x + position.x);
       i += m_cellSize, index += 2) {
    m_points[index].position = sf::Vector2f(i + offset, 0);
    m_points[index + 1].position = sf::Vector2f(i + offset, m_size.y);
  }
  /// Смещение к центру по оси y
  offset = uint32_t(m_size.y / 2) % m_cellSize;
  for (float i = position.y; i < m_size.y + position.y;
       i += m_cellSize, index += 2) {
    m_points[index].position = sf::Vector2f(0, i + offset);
    m_points[index + 1].position = sf::Vector2f(m_size.x, i + offset);
  }
}

int
main(int argc, char* argv[])
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

  sf::ContextSettings settings;
  settings.antialiasingLevel = 2;
  sf::RenderWindow window(
    sf::VideoMode(1920, 1080), "Back", sf::Style::Fullscreen, settings);

  /// Прямоугольник размером с экран
  sf::FloatRect ScreenRect(0, 0, window.getSize().x, window.getSize().y);

  /// Трансформация перемещения в начало координат
  sf::Transform trBegin = MoveToOrigin(window.getSize());

  /// Пересчёт углов наклона в радианы
  float angleH = -15.f * 3.1419f / 180.f;
  float angleV = 5.f * 3.1419f / 180.f;

  /// Матрица преобразования (для скосов)
  sf::Transform trSkew{ 1.f, sinf(angleH), 0.f, sinf(angleV), 1.f,
                        0.f, 0.f,          0.f, 1.f };

  /// Трансформация перемещения обратно
  sf::Transform trBack = ReturnFromOrigin(window.getSize());

  /// Описывающий прямоугольник вокруг прямоугольник размера с экран к которому
  /// применён скос
  sf::FloatRect tmpRect = (trSkew * trBegin).transformRect(ScreenRect);

  /// Коэффициент маштабирования Размеры экран / Размер прямоугольника
  /// описывающего прямоугольник с преобразованием
  float scale = std::min(ScreenRect.width / tmpRect.width,
                         ScreenRect.height / tmpRect.height);

  /// Трансформация для маштабирования
  sf::Transform trScale = sf::Transform::Identity;
  trScale.scale(scale, scale);

  /// Главное преобразование
  sf::Transform tr = sf::Transform::Identity;
  /// Порядок действий записывается наоборот т.е от начала до конца
  tr = trBack * trScale * trSkew * trBegin;

  /// Трансформация для расчёта размеров всей области скоса для экрана
  sf::Transform trInv = tr.getInverse();
  /// Готовый прямоугольник для скоса и фона
  sf::FloatRect greenRect = trInv.transformRect(ScreenRect);
  /// Сбросим координаты
  greenRect.left = 0;
  greenRect.top = 0;

  int CellSize = ScreenRect.height / MAX_CELLS;

  sf::RectangleShape green_rect(
    sf::Vector2f(greenRect.width, greenRect.height));

  // green_rect.seCol(sf::Color::Transparent);
  green_rect.setFillColor(sf::Color::Green);
  green_rect.setOutlineColor(sf::Color::Blue);
  green_rect.setOutlineThickness(2.f);

  /// Сместим центры зелёного прямоугольника и экрана
  MoveToScreenCenter(&green_rect, ScreenRect);

  sf::Vector2f sizeGreenRect = green_rect.getSize();
  sf::Vector2f positionGreenRect = green_rect.getPosition();

  /// Середина зелёного прямоугольника в координатах экрана
  sf::Vertex point(sf::Vector2f(sizeGreenRect.x / 2 + positionGreenRect.x,
                                sizeGreenRect.y / 2 + positionGreenRect.y),
                   sf::Color::Red);

  sf::VertexArray pointArray(sf::Lines);

  CalculatePoints(pointArray, sizeGreenRect, positionGreenRect, CellSize);

  while (window.isOpen()) {
    window.clear(sf::Color::Black);
    // window.draw(green_rect);
    window.draw(pointArray);
    window.draw(&point, 1, sf::Points);
    window.display();

    sf::Event event;
    while (window.pollEvent(event)) {
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