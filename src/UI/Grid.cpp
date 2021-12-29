#include "Grid.h"

Grid::Grid(sf::RenderTarget* pTarget, uint32_t cellSize)
  : m_pTarget(pTarget)
  , m_size(pTarget->getSize())
  , m_points(sf::Lines)
{
  m_cellSize = cellSize < 2 ? 2 : cellSize;
  CalculatePoints();
}

void
Grid::draw(const sf::RenderStates& states = sf::RenderStates::Default)
{
  if (m_size != m_pTarget->getSize()) {
    m_size = m_pTarget->getSize();
    CalculatePoints();
  }

  m_pTarget->draw(m_points, states);
}

void
Grid::CalculatePoints()
{
  /// Кол-во точек для всех линий
  m_points.resize(2 * ((m_size.x + m_size.y) / m_cellSize + 2));

  uint32_t index = 0;

  /// Смещение к центру по оси х
  uint32_t offset = (m_size.x / 2) % m_cellSize;
  for (size_t i = 0; i < m_size.x; i += m_cellSize, index += 2) {
    m_points[index].position = sf::Vector2f(i + offset, 0);
    m_points[index + 1].position = sf::Vector2f(i + offset, m_size.y);
  }
  /// Смещение к центру по оси y
  offset = (m_size.y / 2) % m_cellSize;
  for (size_t i = 0; i < m_size.y; i += m_cellSize, index += 2) {
    m_points[index].position = sf::Vector2f(0, i + offset);
    m_points[index + 1].position = sf::Vector2f(m_size.x, i + offset);
  }
}