#include "Test.h"

Test::Test(const sf::FloatRect& activeRect, uint32_t cellSize)
  : m_activeRect(activeRect)
{
  m_cellSize = cellSize < 2 ? 2 : cellSize;
}

void
Test::SetOffsetGame(int x, int y)
{
  m_offsetGameFieldX = x;
  m_offsetGameFieldY = y;
}

void
Test::draw(sf::RenderTarget& target, sf::RenderStates states) const
{

  Field& fld = Singleton<Field>::GetInstance();
  std::vector<COMMON::ECell> fldVec = fld.GetField();

  const int margin = 5;

  for (int selectY = 0; selectY < fld.GetHeight(); ++selectY) {
    for (int selectX = 0; selectX < fld.GetWidth(); ++selectX) {
      COMMON::ECell cell = fld.GetCell(selectX, selectY);

      sf::RectangleShape rect;
      if (cell != COMMON::ECell::LOCK) {
        rect.setSize(sf::Vector2f(m_cellSize - 2 * margin - 1,
                                  m_cellSize - 2 * margin - 1));
        rect.move(
          sf::Vector2f(selectX * m_cellSize + margin + m_offsetGameFieldX,
                       selectY * m_cellSize + margin + m_offsetGameFieldY));
      } else {
        rect.setSize(sf::Vector2f(m_cellSize, m_cellSize));
        rect.move(sf::Vector2f(selectX * m_cellSize + m_offsetGameFieldX - 1,
                               selectY * m_cellSize + m_offsetGameFieldY));
      }

      switch (cell) {
        case COMMON::ECell::LOCK:
          rect.setFillColor(sf::Color(9, 133, 205));
          // rect.setFillColor(sf::Color::Transparent);
          break;
        case COMMON::ECell::FREE:
          rect.setFillColor(sf::Color::Transparent);
          break;
        case COMMON::ECell::SET:
          rect.setFillColor(sf::Color::White);
          break;
        default:
          break;
      }

      target.draw(rect, states);
    }
  }

  /*   for (int i(0); i < fldVec.size() - 1; i++) {
      if (selectX == fld.GetWidth() - 1) {
        selectX = 0;
        selectY++;
      }
      selectX++;

      rect.move(sf::Vector2f(selectX * m_cellSize, selectY * m_cellSize));
      rect.setFillColor(sf::Color::Yellow);
      target.draw(rect, states);
    } */

  // for (uint8_t x = 0; x < fld.GetWidth(); ++x) {
  //   for (uint8_t y = 0; y < fld.GetHeight(); ++y) {
  //     // ....
  //   }
  // }

  // sf::RectangleShape rect(sf::Vector2f(m_cellSize, m_cellSize));

  // rect.move(sf::Vector2f(selectX * m_cellSize, selectY * m_cellSize));
  // rect.setFillColor(sf::Color::Red);

  // target.draw(rect, states);
}
