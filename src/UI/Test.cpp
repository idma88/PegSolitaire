#include "Test.h"

Test::Test() {}

Test::Test(const sf::FloatRect& activeRect, uint32_t cellSize)
  : m_activeRect(activeRect)
{
  m_cellSize = cellSize < 2 ? 2 : cellSize;

  Field fld = Singleton<SingleMode>::GetInstance().GetField();
  std::vector<COMMON::ECell> fldVec = fld.GetField();

  const int margin = 5;
  sf::Vector2f marginVec(margin, margin);

  m_SizeSetCell = sf::Vector2f(m_cellSize - 2 * margin - 1, m_cellSize - 2 * margin - 1);

  for (int selectY = 0; selectY < fld.GetHeight(); ++selectY) {
    for (int selectX = 0; selectX < fld.GetWidth(); ++selectX) {
      COMMON::ECell cell = fld.GetCell(selectX, selectY);

      sf::RectangleShape rect;
      if (cell == COMMON::ECell::SET) {
        m_vecPosCell.push_back(sf::Vector2f(selectX, selectY) * (float)m_cellSize + marginVec +
                               sf::Vector2f(m_offsetGameField));
      }
    }
  }
}

void
Test::SetActiveRect(const sf::FloatRect& activeRect, uint32_t cellSize)
{
  m_activeRect = activeRect;

  m_cellSize = cellSize < 2 ? 2 : cellSize;

  Field fld = Singleton<SingleMode>::GetInstance().GetField();
  std::vector<COMMON::ECell> fldVec = fld.GetField();

  const int margin = 5;
  sf::Vector2f marginVec(margin, margin);

  m_SizeSetCell = sf::Vector2f(m_cellSize - 2 * margin - 1, m_cellSize - 2 * margin - 1);

  for (int selectY = 0; selectY < fld.GetHeight(); ++selectY) {
    for (int selectX = 0; selectX < fld.GetWidth(); ++selectX) {
      COMMON::ECell cell = fld.GetCell(selectX, selectY);

      sf::RectangleShape rect;
      if (cell == COMMON::ECell::SET) {
        m_vecPosCell.push_back(sf::Vector2f(selectX, selectY) * (float)m_cellSize + marginVec +
                               sf::Vector2f(m_offsetGameField));
      }
    }
  }
}

void
Test::SetOffsetGame(sf::Vector2i offset)
{
  m_offsetGameField = offset;
}

void
Test::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  Field& fld = Singleton<SingleMode>::GetInstance().GetField();
  std::vector<COMMON::ECell> fldVec = fld.GetField();

  const int margin = 5;
  sf::Vector2f marginVec(margin, margin);

  for (int selectY = 0; selectY < fld.GetHeight(); ++selectY) {
    for (int selectX = 0; selectX < fld.GetWidth(); ++selectX) {
      COMMON::ECell cell = fld.GetCell(selectX, selectY);

      sf::RectangleShape rect;
      if (cell != COMMON::ECell::LOCK) {
        rect.setSize(m_SizeSetCell);
        rect.move(sf::Vector2f(selectX, selectY) * (float)m_cellSize + marginVec +
                  sf::Vector2f(m_offsetGameField));
      } else {
        rect.setSize(sf::Vector2f(m_cellSize, m_cellSize));
        rect.move(sf::Vector2f(selectX, selectY) * (float)m_cellSize +
                  sf::Vector2f(m_offsetGameField) - sf::Vector2f(1, 0));
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
}
