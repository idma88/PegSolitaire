#include "Test.h"

Test::Test(const sf::FloatRect& activeRect, uint32_t cellSize)
  : m_activeRect(activeRect)
{
  m_cellSize = cellSize < 2 ? 2 : cellSize;
}

void
Test::draw(sf::RenderTarget& target, sf::RenderStates states) const
{

  Field fld /* = IGame::GetField() */;

  for (uint8_t x = 0; x < fld.GetWidth(); ++x) {
    for (uint8_t y = 0; y < fld.GetHeight(); ++y) {
      // ....
    }
  }

  sf::RectangleShape rect(sf::Vector2f(m_cellSize, m_cellSize));

  int selectX = 3;
  int selectY = 2;

  rect.move(sf::Vector2f(selectX * m_cellSize, selectY * m_cellSize));
  rect.setFillColor(sf::Color::Red);

  target.draw(rect, states);
}
