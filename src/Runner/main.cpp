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

/// Минимальный размер игрового поля, ячеек
const int MIN_CELLS = 7;
/// Максимальный размер игрового поля, ячеек
const int MAX_CELLS = 16;

/// Макрос пересчёта градусов в радианы
#define DEG2RAD(ang) ((ang)*3.14159f / 180.f)

/// Горизонтальный угол наклона, радианы
const float SKEW_ANGLE_H = DEG2RAD(15.f);
/// Вертикальный угол наклона, радианы
const float SKEW_ANGLE_V = DEG2RAD(-5.f);

#pragma region "Размеры активной области"
/**
 * Размеры активной области подобраны так, чтобы получить целое количество точек
 * для размера ячеек. Иниыми словами размеры активной области должны нацело
 * делиться на { @see MAX_CELLS }
 */
/// Ширина активной области
const int ACTIVE_RECT_WIDTH = 1440;
/// Высота активной области
const int ACTIVE_RECT_HEIGHT = 960;
#pragma endregion

#pragma region "Трансформации"
template<class T>
sf::Transform
ToOrigin(sf::Vector2<T> size)
{
  sf::Transform tr;
  tr.translate(-size.x / 2.f, -size.y / 2.f);
  return tr;
}

template<class T>
sf::Transform
FromOrigin(sf::Vector2<T> size)
{
  return ToOrigin(size).getInverse();
}

template<class T>
sf::Transform
AlignToCenter(sf::Rect<T> obj, sf::Rect<T> dest)
{
  sf::Transform tr;

  sf::Vector2<T> destCenter(dest.left + dest.width / 2.f,
                            dest.top + dest.height / 2.f);
  sf::Vector2<T> objCenter(obj.left + obj.width / 2.f,
                           obj.top + obj.height / 2.f);

  tr.translate(destCenter.x - objCenter.x, destCenter.y - objCenter.y);
  return tr;
}

// DEPRECATED, DUMMY
template<class T>
sf::Transform
MoveToScreenCenter(sf::Rect<T> obj,
                   sf::Rect<T> screen){ return AlignToCenter(obj, screen) }

sf::Transform Skew(float angleH, float angleV)
{
  return sf::Transform{ 1.f,          sinf(angleH), 0.f, /**/
                        sinf(angleV), 1.f,          0.f, /**/
                        0.f,          0.f,          1.f };
}
#pragma endregion

/**
 * @brief Получение размеров прямоугольника
 *
 * @tparam T Тип данных
 * @param [in] rect Прямоугольник
 * @return Возвращает вектор с размерами указанного прямоугольника
 */
template<class T>
sf::Vector2<T>
RectSize(const sf::Rect<T>& rect)
{
  return sf::Vector2<T>(rect.width, rect.height);
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
#pragma region "Init"
  google::InitGoogleLogging(argv[0]);
  FLAGS_alsologtostderr = true;

  FLAGS_log_dir = "..\\..\\..\\..\\log";

  LOG(INFO) << "Start main!";

  setlocale(LC_ALL, "Russian");

  Field _field;
  bool trueCreate;
  _field.Create(COMMON::ETypeField::ENGLISH);
  trueCreate = _field.SetCell(SIZE, SIZE, COMMON::ECell::SET);
#pragma endregion

#pragma region "Размеры, прямоугольники, области и т.д."
  /// Видео режим, размеры которого совпадают с текущим разрешением
  sf::VideoMode screenMode = sf::VideoMode::getDesktopMode();

  /// Прямоугольник размером с экран
  sf::FloatRect screenRect(0, 0, screenMode.width, screenMode.height);

  /**
   * @brief Активная область
   * @note Координаты фиксированы и условны, т.е. не зависят от разрешения
   * экрана. Все положения и размеры элементов (меню, игровое поле)
   * расчитываются в этих координатах
   */
  sf::FloatRect activeRect(0, 0, ACTIVE_RECT_WIDTH, ACTIVE_RECT_HEIGHT);
  sf::Vector2f activeRectSize = RectSize(activeRect);

  /**
   * @brief Матрица скоса
   * @note Применение этого преобразования не зависит от размеров объекта и
   * потому может быть рассчитано лишь раз
   */
  sf::Transform trSkew = Skew(SKEW_ANGLE_H, SKEW_ANGLE_V);

  /***** Расчёт главной трансформации *****/

  /// Прямоугольник активной области, после применения скоса
  sf::FloatRect activeRectAfterTransform =
    (trSkew * ToOrigin(activeRectSize)).transformRect(activeRect);

  /// Рассчитываем коэффициент маштабирования так, чтобы активная область после
  /// применения скоса, была вписана в экран
  float scaleFactor =
    std::min(screenRect.width / activeRectAfterTransform.width,
             screenRect.height / activeRectAfterTransform.height);

  /**
   * @brief Матрица масштабирования
   */
  sf::Transform trScale = sf::Transform().scale(scaleFactor, scaleFactor);

  /***** Расчёт размеров области, покрывающей экран *****/
  sf::FloatRect coverRect =
    ToOrigin(RectSize(screenRect)).transformRect(screenRect);
  coverRect = (trScale * trSkew).getInverse().transformRect(coverRect);

  sf::Vector2f coverSize = RectSize(coverRect);

  uint32_t cellSize =
    std::min(ACTIVE_RECT_WIDTH, ACTIVE_RECT_HEIGHT) / MAX_CELLS;

#pragma endregion

#pragma region "Инициализация окна"
  sf::ContextSettings settings;
  settings.antialiasingLevel = 8;
  sf::RenderWindow window(screenMode, "Back", sf::Style::Fullscreen, settings);
#pragma endregion

#if 0
  /// Трансформация перемещения в начало координат
  sf::Transform trBegin = ToOrigin(window.getSize());

  /// Матрица преобразования (для скосов)
  sf::Transform trSkew = Skew(SKEW_ANGLE_H, SKEW_ANGLE_V);

  /// Трансформация перемещения обратно
  sf::Transform trBack = FromOrigin(window.getSize());

  /// Описывающий прямоугольник вокруг прямоугольник размера с экран к которому
  /// применён скос
  sf::FloatRect tmpRect = (trSkew * trBegin).transformRect(screenRect);

  /// Коэффициент маштабирования Размеры экран / Размер прямоугольника
  /// описывающего прямоугольник с преобразованием
  float scale = std::min(screenRect.width / tmpRect.width,
                         screenRect.height / tmpRect.height);

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
  sf::FloatRect greenRect = trInv.transformRect(screenRect);
  /// Сбросим координаты
  greenRect.left = 0;
  greenRect.top = 0;

  int CellSize = screenRect.height / MAX_CELLS;

  sf::RectangleShape green_rect(
    sf::Vector2f(greenRect.width, greenRect.height));

  // green_rect.seCol(sf::Color::Transparent);
  green_rect.setFillColor(sf::Color::Green);
  green_rect.setOutlineColor(sf::Color::Blue);
  green_rect.setOutlineThickness(2.f);

  /// Сместим центры зелёного прямоугольника и экрана
  MoveToScreenCenter(&green_rect, screenRect);

  sf::Vector2f sizeGreenRect = green_rect.getSize();
  sf::Vector2f positionGreenRect = green_rect.getPosition();

  /// Середина зелёного прямоугольника в координатах экрана
  sf::Vertex point(sf::Vector2f(sizeGreenRect.x / 2 + positionGreenRect.x,
                                sizeGreenRect.y / 2 + positionGreenRect.y),
                   sf::Color::Red);

  sf::VertexArray pointArray(sf::Lines);

  CalculatePoints(pointArray, sizeGreenRect, positionGreenRect, CellSize);
#endif // 0

  Grid grid(coverSize, cellSize);

  sf::Transform gridTr = AlignToCenter(coverRect, screenRect) *
                         /* FromOrigin(coverSize) * */ trScale * trSkew *
                         ToOrigin(coverSize);
  sf::Transform activeTr = AlignToCenter(activeRect, screenRect) *
                           FromOrigin(activeRectSize) * trScale * trSkew *
                           ToOrigin(activeRectSize);

  sf::RectangleShape activeRectShape(activeRectSize);
  activeRectShape.setFillColor(sf::Color::Transparent);
  activeRectShape.setOutlineColor(sf::Color::Green);
  activeRectShape.setOutlineThickness(4.f);

  sf::RectangleShape oneCell(sf::Vector2f(cellSize, cellSize));

  int selectX = 3;
  int selectY = 2;
  oneCell.move(cellSize * selectX, cellSize * selectY);

#pragma region "[DEBUG] Центр экрана"
  sf::VertexArray centerPnt(sf::Lines, 4);

  centerPnt[0].position = sf::Vector2f(0, screenRect.height / 2);
  centerPnt[1].position = sf::Vector2f(screenRect.width, screenRect.height / 2);
  centerPnt[2].position = sf::Vector2f(screenRect.width / 2, 0);
  centerPnt[3].position = sf::Vector2f(screenRect.width / 2, screenRect.height);

  centerPnt[0].color = sf::Color::Magenta;
  centerPnt[1].color = sf::Color::Magenta;
  centerPnt[2].color = sf::Color::Magenta;
  centerPnt[3].color = sf::Color::Magenta;
#pragma endregion

  while (window.isOpen()) {
    window.clear(sf::Color::Black);

    window.draw(grid, gridTr);
    window.draw(activeRectShape, activeTr);
    window.draw(oneCell, activeTr);

    window.draw(centerPnt);

    window.display();

    sf::Event event;
    while (window.pollEvent(event)) {
      switch (event.type) {
        case sf::Event::Closed:
          window.close();
          break;
        case sf::Event::KeyPressed:
          if (event.key.code == sf::Keyboard::Escape)
            window.close();
          break;
        default:
          break;
      }
    }
  }

#if 0
  if (trueCreate)
    LOG(INFO) << "Success!";
  else
    LOG(ERROR) << "Error!";
  return 0;
#endif // 0
}