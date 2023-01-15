#include "Engine/Common.h"
#include "Engine/Field.h"
#include "Engine/Grid.h"
#include "Engine/Math.h"
#include "Engine/Player.h"


#include <SFML/Graphics.hpp>
// #include <glog/logging.h>
#include <iostream>

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
  _field.Create("ENGLISH");
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
  float scaleFactor = std::min(screenRect.width / activeRectAfterTransform.width,
                               screenRect.height / activeRectAfterTransform.height);

  /**
   * @brief Матрица масштабирования
   */
  sf::Transform trScale = sf::Transform().scale(scaleFactor, scaleFactor);

  /***** Расчёт размеров области, покрывающей экран *****/
  sf::FloatRect coverRect = ToOrigin(RectSize(screenRect)).transformRect(screenRect);
  coverRect = (trScale * trSkew).getInverse().transformRect(coverRect);

  sf::Vector2f coverSize = RectSize(coverRect);

  uint32_t cellSize = std::min(ACTIVE_RECT_WIDTH, ACTIVE_RECT_HEIGHT) / MAX_CELLS;

#pragma endregion

#pragma region "Инициализация окна"
  sf::ContextSettings settings;
  settings.antialiasingLevel = 8;
  sf::RenderWindow window(screenMode, "Back", sf::Style::Fullscreen, settings);
#pragma endregion

  Grid grid(coverSize, cellSize);

  sf::Transform gridTr = AlignToCenter(coverRect, screenRect) *
                         /* FromOrigin(coverSize) * */ trScale * trSkew * ToOrigin(coverSize);
  sf::Transform activeTr = AlignToCenter(activeRect, screenRect) * FromOrigin(activeRectSize) *
                           trScale * trSkew * ToOrigin(activeRectSize);

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