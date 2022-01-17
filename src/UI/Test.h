#pragma once

#include "../Field/Field.h"
#include "../Game/IGame.h"
#include "../Utils/Singletone.h"
#include <SFML/Graphics.hpp>

class Test : public sf::Drawable
{
public:
  Test(const sf::FloatRect& activeRect, uint32_t cellSize);

  void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
  sf::FloatRect m_activeRect;

  /// Размер клетки в пикселях
  uint32_t m_cellSize;

  sf::VertexArray m_points;
};