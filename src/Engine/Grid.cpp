#include "Grid.h"

Grid::Grid(sf::Vector2f coverSize, uint32_t cellSize)
  : m_size(coverSize)
  , m_points(sf::Lines)
{
  m_cellSize = cellSize < 2 ? 2 : cellSize;
  CalculatePoints();
}

void
Grid::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  target.draw(m_points, states);
}

void
Grid::CalculatePoints()
{
  size_t cnt = 2 * ((m_size.x + m_size.y) / m_cellSize + 2);

  // Кол-во точек для всех линий
  m_points.resize(cnt);

  uint32_t index = 0;

  // Смещение к центру по оси х
  int32_t offset = (int32_t)(m_size.x / 2.f) % m_cellSize;
  for (int32_t i = 0; i < m_size.x; i += m_cellSize, index += 2) {
    m_points[index].position = sf::Vector2f((float)(i + offset), 0);
    m_points[index + 1].position = sf::Vector2f((float)(i + offset), m_size.y);
  }
  // Смещение к центру по оси y
  offset = (int32_t)(m_size.y / 2.f) % m_cellSize;
  for (int32_t i = 0; i < m_size.y; i += m_cellSize, index += 2) {
    m_points[index].position = sf::Vector2f(0, (float)(i + offset));
    m_points[index + 1].position = sf::Vector2f(m_size.x, (float)(i + offset));
  }
}