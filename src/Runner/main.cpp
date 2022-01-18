#include "../Common/Common.h"
#include "../Field/Field.h"
#include "../Game/CoreGame.h"
#include "../Game/Player.h"

#include "../UI/Grid.h"
#include "../UI/Test.h"

#include <SFML/Graphics.hpp>
// #include <glog/logging.h>
#include <iostream>

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

sf::Transform
Skew(float angleH, float angleV)
{
  return sf::Transform{ 1.f,          sinf(angleH), 0.f, /**/
                        sinf(angleV), 1.f,          0.f, /**/
                        0.f,          0.f,          1.f };
}

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

int
main(int argc, char* argv[])
{
#pragma region "Init"
  google::InitGoogleLogging(argv[0]);
  FLAGS_alsologtostderr = true;

  FLAGS_log_dir = "..\\..\\..\\..\\log";

  LOG(INFO) << "Start main!";

  setlocale(LC_ALL, "Russian");

  Field& fld = Singleton<Field>::GetInstance();
  fld.Create(COMMON::ETypeField::ENGLISH);

  // Размер поля
  const int SIZE = fld.GetWidth();

  // Field _field;
  // bool trueCreate;
  // _field.Create(COMMON::ETypeField::ENGLISH);
  // trueCreate = _field.SetCell(SIZE, SIZE, COMMON::ECell::SET);

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
  sf::Transform trSkew =
    /* sf::Transform::Identity; */ Skew(SKEW_ANGLE_H, SKEW_ANGLE_V);

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

  sf::RectangleShape rectField(
    sf::Vector2f((cellSize * SIZE) - 1, (cellSize * SIZE) - 1));

  /// Расчёт кол-ва клеточек по x и y
  int countCellX = (activeRectSize.x / cellSize);
  int countCellY = (activeRectSize.y / cellSize);

  /// Расчёт смещений клеточек для игрового поля
  int offsetActiveX = floor(countCellX / 2) - floor(SIZE / 2); // 8
  int offsetActiveY = floor(countCellY / 2) - floor(SIZE / 2); // 4

  int offsetGameFieldX = cellSize * offsetActiveX;
  int offsetGameFieldY = cellSize * offsetActiveY;

  rectField.move((cellSize * offsetActiveX), (cellSize * offsetActiveY));
  rectField.setFillColor(sf::Color::Transparent);
  rectField.setOutlineColor(sf::Color::White);
  rectField.setOutlineThickness(6.f);

  sf::RectangleShape oneCell(sf::Vector2f(cellSize - 1, cellSize - 1));
  int selectX = 3;
  int selectY = 2;
  oneCell.move(cellSize * selectX + offsetGameFieldX,
               cellSize * selectY + offsetGameFieldY);
  oneCell.setFillColor(sf::Color::Red);

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

#pragma region "Text"
  /// шрифт
  sf::Font font;
  /// передаем нашему шрифту файл шрифта
  font.loadFromFile("CyrilicOld.ttf");
  /// создаем объект текст. закидываем в объект текст строку, шрифт, размер
  sf::Text text("", font, 40);
  /// шрифта(в пикселях);//сам объект текст (не строка)
  /// покрасили текст в красный. если убрать эту
  /// строку, то по умолчанию он белый
  text.setColor(sf::Color::Red);
  /// sжирный и подчеркнутый текст. по умолчанию он
  /// "худой":)) и не подчеркнутый
  text.setStyle(sf::Text::Bold);
  text.setString("Start Game");
  text.setPosition(activeRectSize.x / 2, activeRectSize.y / 2);
#pragma endregion

  Test test(activeRect, cellSize);
  test.SetOffsetGame(offsetGameFieldX, offsetGameFieldY);

  while (window.isOpen()) {
    // window.clear(sf::Color::Black);
    window.clear(sf::Color(9, 133, 205));

    window.draw(grid, gridTr);
    // отрисовка рамки активной области
    // window.draw(activeRectShape, activeTr);

    window.draw(test, activeTr);

    // window.draw(oneCell, activeTr);
    /// Отрисовка синего прямоугольника, а именно самого игрового поля
    window.draw(rectField, activeTr);

    // крест по центру
    // window.draw(centerPnt);
    // пример текста
    // window.draw(text, activeTr);

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