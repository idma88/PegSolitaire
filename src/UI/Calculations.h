#pragma once

#include <iostream>

#include <SFML/Graphics.hpp>

/// Макрос пересчёта градусов в радианы
#define DEG2RAD(ang) ((ang)*3.14159f / 180.f)

class Calculations
{
public:
#pragma region "Трансформации"
  /**
   * @brief Получение размеров прямоугольника
   *
   * @tparam T Тип данных
   * @param [in] rect Прямоугольник
   * @return Возвращает вектор с размерами указанного прямоугольника
   */
  template<class T>
  sf::Vector2<T> RectSize(const sf::Rect<T>& rect);

  sf::Transform Skew(float angleH, float angleV);

  template<class T>
  sf::Transform ToOrigin(sf::Vector2<T> size);

  template<class T>
  sf::Transform FromOrigin(sf::Vector2<T> size);

  template<class T>
  sf::Transform AlignToCenter(sf::Rect<T> obj, sf::Rect<T> dest);
#pragma endregion

#pragma region "Интерфейс"
  /**
   * @brief Расчитывает все необходимые трансформации
   *
   */
  void Init();

  void CalcOffsetGame(uint8_t w, uint8_t h);
#pragma endregion
public:
  /// Максимальный размер игрового поля, ячеек
  const int MAX_CELLS = 16;

  /// Горизонтальный угол наклона, радианы
  const float SKEW_ANGLE_H = DEG2RAD(15.f);
  /// Вертикальный угол наклона, радианы
  const float SKEW_ANGLE_V = DEG2RAD(-5.f);

  /// Ширина активной области
  const int ACTIVE_RECT_WIDTH = 1440;
  /// Высота активной области
  const int ACTIVE_RECT_HEIGHT = 960;

  /// Видео режим, размеры которого совпадают с текущим разрешением
  sf::VideoMode screenMode = sf::VideoMode::getDesktopMode();
  sf::ContextSettings settings;
  sf::RenderWindow window;

  /// Прямоугольник размером с экран
  sf::FloatRect screenRect;
  /// Прямоугольник с активной областью
  sf::FloatRect activeRect;
  /// Размеры активно области
  sf::Vector2f activeRectSize;
  /// Прямоугольник активной области, после применения скоса
  sf::FloatRect activeRectAfterTransform;

  /// Матрица скоса
  sf::Transform trSkew;

  /// Рассчитываем коэффициент маштабирования так, чтобы активная область после
  /// применения скоса, была вписана в экран
  float scaleFactor;
  /// Матрица масштабирования
  sf::Transform trScale;
  /// Расчёт размеров области, покрывающей экран
  sf::FloatRect coverRect;

  /// Размер ячеек
  uint32_t cellSize = 0;

  /// Матрица для сетки
  sf::Transform gridTr;
  /// Матрица для активной области
  sf::Transform activeTr;

  sf::Vector2f coverSize;

  sf::Vector2i fieldSize;
  sf::Vector2i offsetActive;
  sf::Vector2i offsetGameField;
  sf::Vector2i countCell;
};