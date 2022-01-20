#include "Calculations.h"

template<class T>
sf::Vector2<T>
Calculations::RectSize(const sf::Rect<T>& rect)
{
  return sf::Vector2<T>(rect.width, rect.height);
}

sf::Transform
Calculations::Skew(float angleH, float angleV)
{
  return sf::Transform{ 1.f,          sinf(angleH), 0.f, /**/
                        sinf(angleV), 1.f,          0.f, /**/
                        0.f,          0.f,          1.f };
}

template<class T>
sf::Transform
Calculations::ToOrigin(sf::Vector2<T> size)
{
  sf::Transform tr;
  tr.translate(-size.x / 2.f, -size.y / 2.f);
  return tr;
}

template<class T>
sf::Transform
Calculations::FromOrigin(sf::Vector2<T> size)
{
  return ToOrigin(size).getInverse();
}

template<class T>
sf::Transform
Calculations::AlignToCenter(sf::Rect<T> obj, sf::Rect<T> dest)
{
  sf::Transform tr;

  sf::Vector2<T> destCenter(dest.left + dest.width / 2.f, dest.top + dest.height / 2.f);
  sf::Vector2<T> objCenter(obj.left + obj.width / 2.f, obj.top + obj.height / 2.f);

  tr.translate(destCenter.x - objCenter.x, destCenter.y - objCenter.y);
  return tr;
}

void
Calculations::Init()
{
  settings.antialiasingLevel = 8;
  window.create(screenMode, "Back", sf::Style::Fullscreen, settings);

  /// Устанавливаем размеры активной области
  activeRect.width = ACTIVE_RECT_WIDTH;
  activeRect.height = ACTIVE_RECT_HEIGHT;

  /// Устанавливаем размеры экрана
  screenRect.width = screenMode.width;
  screenRect.height = screenMode.height;

  activeRectSize = RectSize(activeRect);
  trSkew = Skew(SKEW_ANGLE_H, SKEW_ANGLE_V);

  activeRectAfterTransform = (trSkew * ToOrigin(activeRectSize)).transformRect(activeRect);

  scaleFactor = std::min(screenRect.width / activeRectAfterTransform.width,
                         screenRect.height / activeRectAfterTransform.height);

  trScale = sf::Transform().scale(scaleFactor, scaleFactor);

  /***** Расчёт размеров области, покрывающей экран *****/
  coverRect = ToOrigin(RectSize(screenRect)).transformRect(screenRect);
  coverRect = (trScale * trSkew).getInverse().transformRect(coverRect);
  cellSize = std::min(ACTIVE_RECT_WIDTH, ACTIVE_RECT_HEIGHT) / MAX_CELLS;

  coverSize = RectSize(coverRect);

  gridTr = AlignToCenter(coverRect, screenRect) * trScale * trSkew * ToOrigin(coverSize);

  activeTr = AlignToCenter(activeRect, screenRect) * FromOrigin(activeRectSize) * trScale * trSkew *
             ToOrigin(activeRectSize);
}

void
Calculations::CalcOffsetGame(uint8_t w, uint8_t h)
{
  /// Расчёт кол-ва клеточек по x и y
  sf::Vector2i countCell(ACTIVE_RECT_WIDTH / cellSize, ACTIVE_RECT_HEIGHT / cellSize);

  fieldSize.x = w;
  fieldSize.y = h;

  offsetActive = (countCell - fieldSize) / 2;

  offsetGameField = offsetActive * (int)cellSize;
}