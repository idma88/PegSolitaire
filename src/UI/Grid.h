#pragma once

#include <SFML/Graphics.hpp>

class Grid
{
public:
  /**
   * @brief Конструктор
   *
   * @param [in] pTarget Указатель на цель рендеринга
   * @param [in] cellSize Размер клетки в пикселях
   */
  Grid(sf::RenderTarget* pTarget, uint32_t cellSize);

  void draw(const sf::RenderStates& states);

private:
  /**
   * @brief Рассчитывает координаты точек сетки
   */
  void CalculatePoints();

private:
  /// Цель рендеринга
  sf::RenderTarget* m_pTarget = nullptr;

  /// Размер цели рендеринга
  sf::Vector2u m_size;

  /// Размер клетки в пикселях
  uint32_t m_cellSize;

  sf::VertexArray m_points;
};