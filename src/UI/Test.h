#pragma once

#include "../Field/Field.h"
#include "../Game/IGame.h"
#include "../Utils/Singletone.h"
#include <SFML/Graphics.hpp>

class Test : public sf::Drawable
{
public:
  Test(const sf::FloatRect& activeRect, uint32_t cellSize);

  void SetOffsetGame(int x, int y);

  void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
  sf::FloatRect m_activeRect;

  /// Размер клетки в пикселях
  uint32_t m_cellSize;

  uint32_t m_offsetGameFieldX = 0;
  uint32_t m_offsetGameFieldY = 0;

  sf::VertexArray m_points;
};