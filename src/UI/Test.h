#pragma once

#include <SFML/Graphics.hpp>

#include "../Field/Field.h"
#include "../Game/IGame.h"
#include "../Game/SingleMode.h"
#include "../Utils/Singletone.h"

class Test : public sf::Drawable
{
public:
  Test();
  Test(const sf::FloatRect& activeRect, uint32_t cellSize);

  void SetOffsetGame(sf::Vector2i offset);

  void SetActiveRect(const sf::FloatRect& activeRect, uint32_t cellSize);

  void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
  std::vector<sf::Vector2f> m_vecPosCell;
  sf::Vector2f m_SizeSetCell;

  sf::FloatRect m_activeRect;

  /// Размер клетки в пикселях
  uint32_t m_cellSize;

  sf::Vector2i m_offsetGameField;

  sf::VertexArray m_points;
};